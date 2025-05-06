#include <iostream>
#include <unistd.h>
#include <rapidjson/document.h>
#include <tradingComponent/core/core.hpp>
#include <tradingComponent/gateway/gateway.hpp>

int main()
{
    std::string cppMMapQueueName = "event_queue_cpp";
    std::size_t cppMMapQueueSize = 100000;

    // receive ticker data
    auto process1PID = fork();
    if (process1PID == 0)
    {
        Gateway gateway(cppMMapQueueName, cppMMapQueueSize);
        gateway.listen();
        exit(0);
    }

    // execute strategies
    auto process2PID = fork();
    if (process2PID == 0)
    {
        Core core(cppMMapQueueName, cppMMapQueueSize);
        core.execute();
        exit(0);
    }

    waitpid(process1PID, nullptr, 0);
    waitpid(process2PID, nullptr, 0);
    return 0;
}