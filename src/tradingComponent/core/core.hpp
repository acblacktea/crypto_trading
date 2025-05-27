#pragma once
#include <atomic>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>
#include <unistd.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <sys/wait.h>
#include <util/MMapQueue.hpp>


// todo change to ankerl::unordered_dense::map;
class EventRegisterTable
{
public:
    EventRegisterTable(std::string_view configStr)
    {
        rapidjson::Document jsonObj;
        jsonObj.Parse(configStr.data());

        for (int i = 0; i < jsonObj.Size(); ++i)
        {
            std::string strategyName = jsonObj[i]["name"].GetString();
            for (int j = 0; j < jsonObj[i]["ticker"].Size(); ++j)
            {
                std::string value = jsonObj[i]["ticker"][j]["assetType"].GetString() + "_" + jsonObj[i]["ticker"][j]["type"].GetString();
                eventToStrategies[value].emplace_back(strategyName);
            }
        }
    }

    std::unordered_map<std::string, std::vector<std::string>> eventToStrategies;
};

/*
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

*/

class Core
{
public:
    Core(std::string & mmapFile, size_t mmapSize, std::string_view configStr)
    {
        _mmapFile = mmapFile;
        _mmapSize = mmapSize;
    }

    void execute()
    {
        auto mpQueue = MMapQueueV2(_mmapFile, _mmapSize);
        std::string s;
        while (true)
        {
            std::string s = mpQueue.pop();

            rapidjson::Document document;
            document.Parse(s.c_str());

            rapidjson::StringBuffer buffer;

            buffer.Clear();
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            document.Accept(writer);
            std::string value = buffer.GetString();
        }
    }

private:
    std::string _mmapFile;
    size_t _mmapSize;
    EventRegisterTable eventRegisterTable;
};