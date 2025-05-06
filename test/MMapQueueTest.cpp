#include <atomic>
#include <random>
#include <vector>
#include <unistd.h>
#include <gtest/gtest.h>
#include <sys/wait.h>
#include <util/MMapQueue.hpp>
struct testBlock
{
    int a;
    char b;
    double c;
    int value;
};


TEST(mmapQueue, test1)
{
    auto dataSize = 100000000;
    constexpr size_t mmapSize = 1000000;
    // create mmap;
    MMapQueue<testBlock, mmapSize> mpQueue("./mmapQueue.txt");
    auto process1PID = fork();
    if (process1PID == 0)
    {
        MMapQueue<testBlock, mmapSize> mpQueue("./mmapQueue.txt");
        for (int i = 0; i < dataSize; ++i)
        {
            testBlock data;
            data.value = i;
            while (!mpQueue.push(data))
            {
            }
        }
        return;
    }

    auto process2PID = fork();
    if (process2PID == 0)
    {
        std::vector<int> ans;
        MMapQueue<testBlock, mmapSize> mpQueue("./mmapQueue.txt");
        for (int i = 0; i < dataSize; ++i)
        {
            testBlock data;
            while (!mpQueue.pop(data))
            {
            }

            ans.emplace_back(data.value);
        }

        //std::cout << "size  " << ans.size() << std::endl;
        for (int i = 0; i < dataSize; ++i)
        {
            //std::cout << ans[i] << std::endl;
            GTEST_ASSERT_EQ(ans[i], i);
        }

        return;
    }

    waitpid(process1PID, nullptr, 0);
    waitpid(process2PID, nullptr, 0);
}

int random_int(int n)
{
    static std::random_device rd; // Seed
    static std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_int_distribution<> distrib(0, n);
    return distrib(gen);
}

std::string generateRandomString()
{
    return std::string(random_int(100) + 1, 'a' + random_int(25));
}

TEST(mmapQueue, test2)
{
    std::string fileName = "./mmapQueue2.txt";
    MMapQueueV2 mpQueue(fileName, 1024 * 1024 * 10);

    auto ve = std::vector<std::string>();
    for (int i = 0; i < 100; ++i)
    {
        ve.emplace_back(generateRandomString());
    }


    for (int i = 0; i < 100; ++i)
    {
        std::cout << ve[i] << std::endl;
        while (!mpQueue.push(ve[i]))
        {
        }
    }

    for (int i = 0; i < 100; ++i)
    {
        std::string str;
        while (!mpQueue.pop(str))
        {
        }

        GTEST_ASSERT_EQ(str, ve[i]);
    }
}


TEST(mmapQueue, test3)
{
    auto dataSize = 10000000;
    constexpr size_t mmapSize = 1024 * 1024;
    std::string fileName = "./mmapQueue3.txt";
    auto ve = std::vector<std::string>();
    for (int i = 0; i < dataSize; ++i)
    {
        ve.emplace_back(generateRandomString());
    }

    auto process1PID = fork();
    if (process1PID == 0)
    {
        MMapQueueV2 mpQueue(fileName, mmapSize);
        for (int i = 0; i < dataSize; ++i)
        {
            while (!mpQueue.push(ve[i]))
            {
            }
        }
        return;
    }

    auto process2PID = fork();
    if (process2PID == 0)
    {
        MMapQueueV2 mpQueue(fileName, mmapSize);
        for (int i = 0; i < dataSize; ++i)
        {
            std::string data;
            while (!mpQueue.pop(data))
            {
            }

            GTEST_ASSERT_EQ(data, ve[i]);
        }

        return;
    }

    waitpid(process1PID, nullptr, 0);
    waitpid(process2PID, nullptr, 0);
}
