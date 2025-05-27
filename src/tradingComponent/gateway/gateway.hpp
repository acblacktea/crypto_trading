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
#include <tradingComponent/gateway/convertTicker.hpp>
#include <util/MMapQueue.hpp>


/*
 rapidjson::Document jsonObj;
jsonObj.Parse(str.data());
*/

namespace Gateway
{

/*
       {
        "name": "strategy_demo1",
        "file_name": "strategy/strategy_demo1.cpp",
        "ticker": [
            {
                "assetType": "USDM",
                "type": "klink@BTCUSDT"
            }
        ]
    },
*/

class BinanceProperty
{
public:
    BinanceProperty(std::string_view configStr)
    {
        spotEventMMapQueueName = "spot_event_queue";
        spotEventMMapQueueSize = 1024 * 1024 * 1024;

        USDMEventMMapQueueName = "usdm_event_queue";
        USDMEventMMapQueueSize = 1024 * 1024 * 1024;

        rapidjson::Document jsonObj;
        jsonObj.Parse(configStr.data());
        for (int i = 0; i < jsonObj.Size(); ++i)
        {
            for (int j = 0; j < jsonObj[i]["ticker"].Size(); ++j)
            {
                auto & value = jsonObj[i]["ticker"][j];
                if (value["assetType"] == "spot")
                {
                    spotEventTypes.emplace_back(value["type"].GetString());
                }
                else if (value["assetType"] == "USDM")
                {
                    USDMEventTypes.emplace_back(value["type"].GetString());
                }
            }
        }
    }

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
    Gateway(std::string_view configStr)
        : properties_(configStr)
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
                            properties_.binanceProperty.spotEventTypes,
                            [this, &mpQueue](std::string & s)
                            {
                                rapidjson::Document jsonObj;
                                jsonObj.Parse(s.data());
                                auto buffer = convertBinanceTicker(jsonObj, "Spot");
                                mpQueue.push(reinterpret_cast<char *>(buffer.GetBufferPointer()), buffer.GetSize());
                            });
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
                            properties_.binanceProperty.USDMEventTypes,
                            [this, &mpQueue](std::string & s)
                            {
                                rapidjson::Document jsonObj;
                                jsonObj.Parse(s.data());
                                auto buffer = convertBinanceTicker(jsonObj, "Future");
                                mpQueue.push(reinterpret_cast<char *>(buffer.GetBufferPointer()), buffer.GetSize());
                            });
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
}