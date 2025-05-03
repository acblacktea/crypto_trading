// mmap_queue.hpp
#pragma once
#include <atomic>
#include <cstring>
#include <filesystem>
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

/*
RingMmapQueue::RingMmapQueue(const char* path, size_t size) 
    : mfile_(boost::interprocess::open_or_create, path, size),
      buffer_(static_cast<char*>(mfile_.get_address())),
      capacity_(mfile_.get_size()) {}

size_t RingMmapQueue::next_pos(size_t pos) const {
    return (pos + 1) % capacity_;
}

bool RingMmapQueue::push(const Tick& tick) {
    std::string serialized;
    serialize(tick, serialized);
    uint32_t data_size = serialized.size();
    size_t total_size = sizeof(data_size) + data_size;

    // Check space (with ring wrap)
    size_t curr_head = head_.load(std::memory_order_relaxed);
    size_t curr_tail = tail_.load(std::memory_order_acquire);

    if (next_pos(curr_head) == curr_tail || 
        (curr_head < curr_tail && curr_head + total_size >= curr_tail)) {
        return false; // Queue full
    }

    // Handle wrap-around
    if (curr_head + total_size > capacity_) {
        // Write partial at end, remainder at start
        size_t first_chunk = capacity_ - curr_head;
        if (first_chunk >= sizeof(data_size)) {
            std::memcpy(buffer_ + curr_head, &data_size, sizeof(data_size));
            std::memcpy(buffer_, serialized.data(), data_size);
        } else {
            // Split serialized data across boundary
            std::memcpy(buffer_ + curr_head, &data_size, first_chunk);
            std::memcpy(buffer_, reinterpret_cast<char*>(&data_size) + first_chunk, 
                       sizeof(data_size) - first_chunk);
            std::memcpy(buffer_ + (sizeof(data_size) - first_chunk), 
                       serialized.data(), data_size);
        }
    } else {
        // Contiguous write
        std::memcpy(buffer_ + curr_head, &data_size, sizeof(data_size));
        std::memcpy(buffer_ + curr_head + sizeof(data_size), 
                   serialized.data(), data_size);
    }

    // Update head
    head_.store((curr_head + total_size) % capacity_, std::memory_order_release);
    return true;
}

bool RingMmapQueue::pop(Tick& tick) {
    size_t curr_tail = tail_.load(std::memory_order_relaxed);
    if (curr_tail == head_.load(std::memory_order_acquire)) 
        return false; // Queue empty

    // Read size (handle wrap-around)
    uint32_t data_size;
    if (curr_tail + sizeof(data_size) > capacity_) {
        size_t first_chunk = capacity_ - curr_tail;
        std::memcpy(&data_size, buffer_ + curr_tail, first_chunk);
        std::memcpy(reinterpret_cast<char*>(&data_size) + first_chunk,
                   buffer_, sizeof(data_size) - first_chunk);
    } else {
        std::memcpy(&data_size, buffer_ + curr_tail, sizeof(data_size));
    }

    // Calculate read positions
    size_t data_start = (curr_tail + sizeof(data_size)) % capacity_;
    size_t total_size = sizeof(data_size) + data_size;

    // Read data (handle wrap-around)
    std::vector<char> buf(data_size);
    if (data_start + data_size > capacity_) {
        size_t first_chunk = capacity_ - data_start;
        std::memcpy(buf.data(), buffer_ + data_start, first_chunk);
        std::memcpy(buf.data() + first_chunk, buffer_, data_size - first_chunk);
    } else {
        std::memcpy(buf.data(), buffer_ + data_start, data_size);
    }

    // Deserialize
    deserialize(buf.data(), tick);

    // Update tail
    tail_.store((curr_tail + total_size) % capacity_, std::memory_order_release);
    return true;
}
*/


// consume raw data
class MMapQueueV2
{
public:
    MMapQueueV2(std::string && path, size_t size)
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
            head = new std::atomic<size_t>();
            head->store(0);
            tail = new std::atomic<size_t>();
            tail->store(0);
        }
    }

    ~MMapQueueV2()
    {
        munmap(data, fileTotalSize);
        close(fd_);
    }

    bool push(const std::string & rawTicker)
    {
        int dataSize = rawTicker.size();
        auto totalSize = sizeof(dataSize) + dataSize;
        auto headValue = head->load(std::memory_order_relaxed);
        auto tailValue = tail->load(std::memory_order_acquire);

        if ((headValue + totalSize) % capacity >= tailValue)
            return false; // Queue full


        if (headValue + totalSize > capacity) [[unlikely]]
        {
            // Write partial at end, remainder at start
            size_t firstChunkSize = capacity - headValue;
            if (firstChunkSize >= sizeof(dataSize)) [[likely]]
            {
                std::memcpy(data + headValue, &dataSize, sizeof(dataSize));

                firstChunkSize = firstChunkSize - sizeof(dataSize);
                std::memcpy(data + headValue + sizeof(dataSize), rawTicker.data(), firstChunkSize);
                std::memcpy(data, rawTicker.data() + firstChunkSize, dataSize - firstChunkSize);
            }
            else [[unlikely]]
            {
                // Split serialized data across boundary
                std::memcpy(data + headValue, &dataSize, firstChunkSize);
                std::memcpy(data, reinterpret_cast<char *>(&dataSize) + firstChunkSize, sizeof(dataSize) - firstChunkSize);
                std::memcpy(data + (sizeof(dataSize) - firstChunkSize), rawTicker.data(), dataSize);
            }
        }
        else [[likely]]
        {
            // Contiguous write
            std::memcpy(data + headValue, &dataSize, sizeof(dataSize));
            std::memcpy(data + headValue + sizeof(dataSize), rawTicker.data(), dataSize);
        }


        head->store((headValue + totalSize) % capacity, std::memory_order_release);
        return true;
    }

    bool pop(std::string & rawTicker)
    {
        auto tailValue = tail->load(std::memory_order_relaxed);
        auto headValue = head->load(std::memory_order_acquire);

        //std::cout << tailValue << " " << headValue << std::endl;
        if (tailValue == headValue)
            return false; // Queue empty

        size_t dataSize;
        if (tailValue + sizeof(dataSize) > capacity) [[unlikely]]
        {
            size_t firstChunkSize = capacity - tailValue;
            std::memcpy(&dataSize, data + tailValue, firstChunkSize);
            std::memcpy(reinterpret_cast<char *>(&dataSize) + firstChunkSize, data, sizeof(dataSize) - firstChunkSize);
        }
        else [[likely]]
        {
            std::memcpy(&dataSize, data + tailValue, sizeof(dataSize));
        }

        // Calculate read positions
        size_t dataStart = (tailValue + sizeof(dataSize)) % capacity;
        size_t totalSize = sizeof(dataSize) + dataSize;

        // Read data (handle wrap-around)
        rawTicker = std::string(dataSize, 0);
        if (dataStart + dataSize > capacity)
        {
            size_t firstChunkSize = capacity - dataStart;
            std::memcpy(rawTicker.data(), data + dataStart, firstChunkSize);
            std::memcpy(rawTicker.data() + firstChunkSize, data, dataSize - firstChunkSize);
        }
        else [[likely]]
        {
            std::memcpy(rawTicker.data(), data + dataStart, dataSize);
        }

        tail->store((tailValue + totalSize) % capacity, std::memory_order_release);
        return true;
    }

private:
    bool pathExists(const std::string & path) { return std::filesystem::exists(path); }

    int fd_;
    size_t fileTotalSize;
    std::atomic<size_t> * head; // read position
    std::atomic<size_t> * tail; // write position
    char * data;
    size_t capacity;
};
