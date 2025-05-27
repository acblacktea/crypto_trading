#include <iostream>
#include <unistd.h>
#include <rapidjson/document.h>
#include <tradingComponent/core/core.hpp>
#include <tradingComponent/gateway/gateway.hpp>


// TODO refactor
int main()
{
    /*
    std::string cppMMapQueueName = "./data/mmap/event_queue_cpp";
    constexpr size_t cppMMapQueueSize = 1024 * 1024 * 1024;

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
*/
    return 0;
}