// mmap_queue.hpp
#pragma once
#include <atomic>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
// ring queue
template <typename T, size_t N>
class MMapQueue
{
public:
    explicit MMapQueue(std::string && path)
        : fileTotalSize(N * sizeof(T) + 2 * sizeof(std::atomic<int>))
    {
        auto fileExisted = pathExists(path);
        if (!fileExisted)
        {
            fd_ = open(path.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0666);
            ftruncate(fd_, fileTotalSize);
        }
        else
        {
            fd_ = open(path.c_str(), O_RDWR);
        }

        // Memory map the file
        void * addr = mmap(nullptr, fileTotalSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0);
        if (addr == MAP_FAILED)
        {
            throw std::runtime_error("mmap failed");
        }


        data = reinterpret_cast<T *>(addr);
        head = reinterpret_cast<std::atomic<int> *>(data + N);
        tail = head + 1;

        if (!fileExisted)
        {
            // Initialize header
            head->store(0);
            tail->store(0);
        }
    }

    ~MMapQueue()
    {
        munmap(data, fileTotalSize);
        close(fd_);
    }

    [[nodiscard]] bool push(const T & item)
    {
        auto headValue = head->load(std::memory_order_relaxed);
        auto tailValue = tail->load(std::memory_order_acquire);

        if ((headValue + 1) % N == tailValue)
            return false; // Queue full

        data[headValue] = item;
        head->store((headValue + 1) % N, std::memory_order_release);
        return true;
    }

    [[nodiscard]] bool pop(T & item)
    {
        auto tailValue = tail->load(std::memory_order_relaxed);
        auto headValue = head->load(std::memory_order_acquire);

        //std::cout << tailValue << " " << headValue << std::endl;
        if (tailValue == headValue)
            return false; // Queue empty

        item = data[tailValue];
        tail->store((tailValue + 1) % N, std::memory_order_release);
        return true;
    }

private:
    bool pathExists(const std::string & path) { return std::filesystem::exists(path); }

    int fd_;
    size_t fileTotalSize;
    std::atomic<int> * head; // read position
    std::atomic<int> * tail; // write position
    T * data;
};

// consume raw data
class MMapQueueV2
{
public:
    MMapQueueV2() = default;
    MMapQueueV2(std::string & path, size_t size)
        : fileTotalSize(size + 2 * 64)
        , capacity(size)
    {
        auto fileExisted = pathExists(path);
        if (!fileExisted)
        {
            fd_ = open(path.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0666);
            ftruncate(fd_, fileTotalSize);
        }
        else
        {
            fd_ = open(path.c_str(), O_RDWR);
        }

        // Memory map the file
        void * addr = mmap(nullptr, fileTotalSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0);
        if (addr == MAP_FAILED)
        {
            throw std::runtime_error("mmap failed");
        }


        data = reinterpret_cast<char *>(addr);

        // align memory,aovid false sharing
        head = reinterpret_cast<std::atomic<size_t> *>(data + capacity);
        tail = reinterpret_cast<std::atomic<size_t> *>(data + capacity + 64);

        if (!fileExisted)
        {
            // Initialize header
            head->store(0);
            // Initialize tail
            tail->store(0);
        }

        std::cout << "create mmap" << head->load() << " " << tail->load() << std::endl;
    }

    ~MMapQueueV2()
    {
        std::cout << "release mmap" << head->load() << " " << tail->load() << std::endl;
        munmap(data, fileTotalSize);
        close(fd_);
    }

    bool tryPush(const char * rawTicker, size_t dataSize)
    {
        size_t totalSize = sizeof(dataSize) + dataSize;
        size_t headValue = head->load(std::memory_order_relaxed);
        size_t tailValue = tail->load(std::memory_order_acquire);
        //std::cout << "push:" << tailValue << " " << headValue << " " << rawTicker << " " << rawTicker.size() << std::endl;
        if ((headValue < tailValue && headValue + totalSize >= tailValue)
            || (headValue > tailValue && headValue + totalSize >= capacity + tailValue))
            return false; // Queue full


        if (headValue + totalSize > capacity) [[unlikely]]
        {
            // Write partial at end, remainder at start
            size_t firstChunkSize = capacity - headValue;
            if (firstChunkSize >= sizeof(dataSize)) [[likely]]
            {
                //std::cout << "path 1" << std::endl;
                std::memcpy(data + headValue, &dataSize, sizeof(dataSize));

                firstChunkSize = firstChunkSize - sizeof(dataSize);

                std::memcpy(data + headValue + sizeof(dataSize), rawTicker, firstChunkSize);
                std::memcpy(data, rawTicker + firstChunkSize, dataSize - firstChunkSize);
            }
            else [[unlikely]]
            {
                //std::cout << "path 2" << std::endl;
                // Split serialized data across boundary
                std::memcpy(data + headValue, &dataSize, firstChunkSize);
                std::memcpy(data, reinterpret_cast<char *>(&dataSize) + firstChunkSize, sizeof(dataSize) - firstChunkSize);
                std::memcpy(data + (sizeof(dataSize) - firstChunkSize), rawTicker, dataSize);
            }
        }
        else [[likely]]
        {
            // Contiguous write
            //std::cout << "path 3" << std::endl;
            std::memcpy(data + headValue, &dataSize, sizeof(dataSize));
            std::memcpy(data + headValue + sizeof(dataSize), rawTicker, dataSize);
        }


        head->store((headValue + totalSize) % capacity, std::memory_order_release);
        return true;
    }

    bool tryPop(std::string & rawTicker)
    {
        size_t tailValue = tail->load(std::memory_order_relaxed);
        size_t headValue = head->load(std::memory_order_acquire);
        //std::cout << "pop start: " << tailValue << " " << headValue << " " << std::endl;
        if (tailValue == headValue)
            return false; // Queue empty

        size_t dataSize;
        if (tailValue + sizeof(dataSize) > capacity) [[unlikely]]
        {
            //std::cout << "path 4" << std::endl;
            size_t firstChunkSize = capacity - tailValue;
            std::memcpy(&dataSize, data + tailValue, firstChunkSize);
            std::memcpy(reinterpret_cast<char *>(&dataSize) + firstChunkSize, data, sizeof(dataSize) - firstChunkSize);
        }
        else [[likely]]
        {
            //std::cout << "path 5" << std::endl;
            std::memcpy(&dataSize, data + tailValue, sizeof(dataSize));
        }

        // Calculate read positions
        size_t dataStart = (tailValue + sizeof(dataSize)) % capacity;
        size_t totalSize = sizeof(dataSize) + dataSize;

        // Read data (handle wrap-around)
        rawTicker = std::string(dataSize, 0);
        if (dataStart + dataSize > capacity)
        {
            //std::cout << "path 6" << std::endl;
            size_t firstChunkSize = capacity - dataStart;
            std::memcpy(rawTicker.data(), data + dataStart, firstChunkSize);
            std::memcpy(rawTicker.data() + firstChunkSize, data, dataSize - firstChunkSize);
        }
        else [[likely]]
        {
            //std::cout << "path 7" << std::endl;
            std::memcpy(rawTicker.data(), data + dataStart, dataSize);
        }

        //std::cout << "pop: " << tailValue << " " << headValue << " " << rawTicker << " " << rawTicker.size() << std::endl;
        tail->store((tailValue + totalSize) % capacity, std::memory_order_release);
        return true;
    }

    void push(const char * rawTicker, size_t dataSize)
    {
        while (!tryPush(rawTicker, dataSize))
        {
        }
    }

    std::string pop()
    {
        std::string value;
        while (!tryPop(value))
        {
        }

        return value;
    }

private:
    bool pathExists(const std::string & path) { return std::filesystem::exists(path); }

    int fd_;
    size_t fileTotalSize;
    std::atomic<size_t> * head = nullptr; // read position
    std::atomic<size_t> * tail = nullptr; // write position
    char * data;
    size_t capacity;
};
