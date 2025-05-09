#include <iostream>
#include <unistd.h>
#include <rapidjson/document.h>
#include <tradingComponent/core/core.hpp>
#include <tradingComponent/gateway/gateway.hpp>

int main()
{
    std::string pythonMMapQueueName = "./data/mmap/event_queue_python";
    constexpr std::size_t pythonMMapQueueSize = 1024 * 1024 * 1024;

    /*
    Gateway gateway(pythonMMapQueueName, pythonMMapQueueSize);
    gateway.listen();
    */
    return 0;
}