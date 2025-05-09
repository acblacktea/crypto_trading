#pragma once
#include <exchanges/binance/model/Event.hpp>
#include <rapidjson/document.h>
#include <util/jsonBase.h>

//const char* json = R"({"stream":"btcusdt@bookTicker","data":{"u":56052199039,"s":"BTCUSDT","b":"99566.42000000","B":"3.12604000","a":"99566.43000000","A":"2.90961000"}})";
namespace Binance
{

class BookTickerEvent : public JsonObject, public Event
{
public:
    bool deserialize(const rapidjson::Value & obj) override;
    long long updateID;
    std::string symbol;
    std::string bestBidPrice;
    std::string bestBidQuantity;
    std::string bestAskPrice;
    std::string bestAskQuantity;

private:
    void setUpdateID(long long _updateID) { updateID = _updateID; }

    void setSymbol(std::string && _symbol) { symbol = std::move(_symbol); }

    void setBestBidPrice(std::string && _bestBidPrice) { bestBidPrice = std::move(_bestBidPrice); }

    void setBestBidQuantity(std::string && _bestBidQuantity) { bestBidQuantity = std::move(_bestBidQuantity); }

    void setBestAskPrice(std::string && _bestAskPrice) { bestAskPrice = std::move(_bestAskPrice); }

    void setBestAskQuantity(std::string && _bestAskQuantity) { bestAskQuantity = std::move(_bestAskQuantity); }
};


bool BookTickerEvent::deserialize(const rapidjson::Value & obj)
{
    setStream(obj["stream"].GetString());
    setUpdateID(obj["data"]["u"].GetInt64());
    setSymbol(obj["data"]["s"].GetString());
    setBestBidPrice(obj["data"]["b"].GetString());
    setBestBidQuantity(obj["data"]["B"].GetString());
    setBestAskPrice(obj["data"]["a"].GetString());
    setBestAskQuantity(obj["data"]["A"].GetString());
    return true;
}
}
