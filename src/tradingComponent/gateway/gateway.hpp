#pragma once
#include <atomic>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <unistd.h>
#include <exchanges/binance/http/Client.h>
#include <exchanges/binance/model/AggregateTrade.h>
#include <exchanges/binance/websocket/Client.h>
#include <rapidjson/document.h>
#include <sys/wait.h>
#include <util/MMapQueue.hpp>

class Gateway
{
public:
    Gateway(std::string & mmapFile, size_t mmapSize)
    {
        _mmapFile = mmapFile;
        _mmapSize = mmapSize;
    }

    void listen()
    {
        // c++ mmap queue
        auto mpQueue = MMapQueueV2(_mmapFile, _mmapSize);

        BinanceStreamClient.subscrible({"btcusdt@depth@100ms"}, [this, &mpQueue](std::string & s) { mpQueue.push(s); });

        BinanceStreamClient.listen();
    }

private:
    Binance::Websocket::Client BinanceStreamClient;
    Binance::Http::Client BinanceHttpClient;
    std::string _mmapFile;
    size_t _mmapSize;
};