#pragma once
#include <string>
class BaseStrategy
{
public:
    explicit BaseStrategy(std::string strategyName)
        : stragtegyName_(strategyName)
    {
        listen();
    }

    void onTick() {

    };
    void onKline();

private:
    void listen() { }

    std::string stragtegyName_
}