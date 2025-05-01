// mmap_queue.hpp
#pragma once
#include <atomic>
#include <cstring>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

template <typename T, size_t N>
class MMapQueue
{
public:
    MMapQueue(std::string && path)
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
            head = new std::atomic<int>();
            head->store(0);
            tail = new std::atomic<int>();
            tail->store(0);
        }
    }

    ~MMapQueue()
    {
        munmap(data, fileTotalSize);
        close(fd_);
    }

    bool push(const T & item)
    {
        auto headValue = head->load(std::memory_order_relaxed);
        auto tailValue = tail->load(std::memory_order_acquire);

        if ((headValue + 1) % N == tailValue)
            return false; // Queue full

        data[headValue] = item;
        head->store((headValue + 1) % N, std::memory_order_release);
        return true;
    }

    bool pop(T & item)
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