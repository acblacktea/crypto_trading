#pragma once
#include <model/binance/Event.hpp>
#include <rapidjson/document.h>
#include <util/jsonBase.h>

//const char* json = R"({"stream":"btcusdt@bookTicker","data":{"u":56052199039,"s":"BTCUSDT","b":"99566.42000000","B":"3.12604000","a":"99566.43000000","A":"2.90961000"}})";
namespace Binance
{

[[deprecated]] DEFINE_CLASS(
    BookTicker,
    ((std::string, symbol, s))((std::string, bestBidPrice, b))((std::string, bestBidQuantity, B))((std::string, bestAskPrice, a))(
        (std::string, bestAskQuantity, A))((long long, updateTime, u)))

    [[deprecated]] DEFINE_CLASS(BookTickerEvent, ((std::string, stream, stream))((BookTicker, data, data)))
}
