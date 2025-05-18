#pragma once
#include <chrono>
#include <ctime>
#include <iostream>

long long generateMillisecond()
{
    auto utc_time = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(utc_time.time_since_epoch()).count();
}
