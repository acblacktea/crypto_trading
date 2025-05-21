#pragma once
#include <atomic>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <vector>
#include <unistd.h>
#include <exchanges/binance/http/Client.hpp>
#include <exchanges/binance/websocket/Client.hpp>
#include <model/binance/AggregateTrade.h>
#include <rapidjson/document.h>
#include <sys/wait.h>
#include <util/MMapQueue.hpp>

class BinanceProperty
{
public:
    std::vector<std::string> spotEventTypes;
    std::string spotEventMMapQueueName;
    size_t spotEventMMapQueueSize;

    std::vector<std::string> USDMEventTypes;
    std::string USDMEventMMapQueueName;
    size_t USDMEventMMapQueueSize;
};

class GatewayProperty
{
public:
    BinanceProperty binanceProperty;
};

class Gateway
{
public:
    Gateway(GatewayProperty & properties)
        : properties_(properties)
    {
    }

    void listen()
    {
        std::vector<std::thread> threads;
        if (!properties_.binanceProperty.spotEventTypes.empty())
        {
            threads.emplace_back(
                std::thread(
                    [this]
                    {
                        std::cout << "spot: " << std::endl;
                        Binance::Spot::SpotClient client;
                        auto mpQueue = MMapQueueV2(
                            properties_.binanceProperty.spotEventMMapQueueName, properties_.binanceProperty.spotEventMMapQueueSize);
                        client.subscrible(
                            properties_.binanceProperty.spotEventTypes, [this, &mpQueue](std::string & s) { mpQueue.push(s); });
                        client.listen();
                    }));
        };

        if (!properties_.binanceProperty.USDMEventTypes.empty())
        {
            threads.emplace_back(
                std::thread(
                    [this]
                    {
                        std::cout << "future: " << std::endl;
                        Binance::USDM::MarketDataClient client;
                        auto mpQueue = MMapQueueV2(
                            properties_.binanceProperty.USDMEventMMapQueueName, properties_.binanceProperty.USDMEventMMapQueueSize);
                        client.subscrible(
                            properties_.binanceProperty.USDMEventTypes, [this, &mpQueue](std::string & s) { mpQueue.push(s); });
                        client.listen();
                    }));
        };

        for (auto & thread : threads)
        {
            thread.join();
        }
    }

private:
    GatewayProperty properties_;
};