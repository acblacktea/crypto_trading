#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unistd.h>
#include <rapidjson/document.h>
#include <tradingComponent/core/core.hpp>
#include <tradingComponent/gateway/gateway.hpp>

std::string get_current_date()
{
    std::time_t now = std::time(nullptr); // Get current time
    std::tm * local_time = std::localtime(&now); // Convert to local time

    // Format the date into a string (e.g., "2023-10-05")
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", local_time);
    return std::string(buffer);
}


int main()
{
    auto process1PID = fork();
    if (process1PID == 0)
    {
        GatewayProperty properties;
        properties.binanceProperty.spotEventMMapQueueName = "./data/mmap/binance_spot_ticker";
        properties.binanceProperty.spotEventMMapQueueSize = 1024 * 1024 * 1024;
        properties.binanceProperty.spotEventTypes = {
            "btcusdt@kline_1m",
            "btcusdt@bookTicker",
            "ethusdt@kline_1m",
            "ethusdt@bookTicker",
            "bnbusdt@kline_1m",
            "bnbusdt@bookTicker",
            "solusdt@kline_1m",
            "solusdt@bookTicker",
        };

        properties.binanceProperty.USDMEventMMapQueueName = "./data/mmap/binance_usdm_ticker";
        properties.binanceProperty.USDMEventMMapQueueSize = 1024 * 1024 * 1024;
        properties.binanceProperty.USDMEventTypes = {
            "btcusdt@kline_1m",
            "btcusdt@bookTicker",
            "ethusdt@kline_1m",
            "ethusdt@bookTicker",
            "bnbusdt@kline_1m",
            "bnbusdt@bookTicker",
            "solusdt@kline_1m",
            "solusdt@bookTicker",
        };

        Gateway gateway(properties);
        gateway.listen();
    }

    auto process2PID = fork();
    if (process2PID == 0)
    {
        std::string dateStr = get_current_date();
        std::string queueName = "./data/mmap/binance_spot_ticker";
        size_t queueSize = 1024 * 1024 * 1024;
        auto mpQueue = MMapQueueV2(queueName, queueSize);

        std::unordered_map<std::string, long long> streamLatestTimeMap;
        std::unordered_map<std::string, std::string> streamEventMap;
        std::ofstream klineFile("./data/backtest/binance_spot_kline_" + dateStr + ".txt", std::ios::app);
        std::ofstream booktickerFile("./data/backtest/binance_spot_bookticker_" + dateStr + ".txt", std::ios::app);

        while (true)
        {
            std::string currentDateStr = get_current_date();
            if (currentDateStr != dateStr)
            {
                klineFile.close();
                booktickerFile.close();
                dateStr = currentDateStr;
                klineFile = std::ofstream("./data/backtest/binance_spot_kline_" + dateStr + ".txt", std::ios::app);
                booktickerFile = std::ofstream("./data/backtest/binance_spot_bookticker_" + dateStr + ".txt", std::ios::app);
            }

            std::string s = mpQueue.pop();
            if (s.contains("@kline"))
            {
                rapidjson::Document d;
                d.Parse(s.c_str());

                std::string stream = d["stream"].GetString();
                long long startTime = d["data"]["k"]["t"].GetInt64() / 60000;
                if (streamLatestTimeMap.contains(stream) && streamLatestTimeMap[stream] != startTime)
                {
                    klineFile << streamEventMap[stream] << std::endl;
                }

                streamLatestTimeMap[stream] = startTime;
                streamEventMap[stream] = s;
            }
            else if (s.contains("@bookTicker"))
            {
                booktickerFile << s << std::endl;
            }
        }
    }

    auto process3PID = fork();
    if (process3PID == 0)
    {
        std::string dateStr = get_current_date();
        std::string queueName = "./data/mmap/binance_usdm_ticker";
        size_t queueSize = 1024 * 1024 * 1024;
        auto mpQueue = MMapQueueV2(queueName, queueSize);


        std::unordered_map<std::string, long long> streamLatestTimeMap;
        std::unordered_map<std::string, std::string> streamEventMap;
        std::ofstream klineFile("./data/backtest/binance_usdm_kline_" + dateStr + ".txt", std::ios::app);
        std::ofstream booktickerFile("./data/backtest/binance_usdm_bookticker_" + dateStr + ".txt", std::ios::app);

        while (true)
        {
            std::string currentDateStr = get_current_date();
            if (currentDateStr != dateStr)
            {
                klineFile.close();
                booktickerFile.close();
                dateStr = currentDateStr;
                klineFile = std::ofstream("./data/backtest/binance_usdm_kline_" + dateStr + ".txt", std::ios::app);
                booktickerFile = std::ofstream("./data/backtest/binance_usdm_bookticker_" + dateStr + ".txt", std::ios::app);
            }

            std::string s = mpQueue.pop();
            if (s.contains("@kline"))
            {
                rapidjson::Document d;
                d.Parse(s.c_str());

                std::string stream = d["stream"].GetString();
                long long startTime = d["data"]["k"]["t"].GetInt64() / 60000;
                if (streamLatestTimeMap.contains(stream) && streamLatestTimeMap[stream] != startTime)
                {
                    klineFile << streamEventMap[stream] << std::endl;
                }

                streamLatestTimeMap[stream] = startTime;
                streamEventMap[stream] = s;
            }
            else if (s.contains("@bookTicker"))
            {
                booktickerFile << s << std::endl;
            }
        }
    }

    waitpid(process1PID, nullptr, 0);
    waitpid(process2PID, nullptr, 0);
    waitpid(process3PID, nullptr, 0);
    return 0;
}