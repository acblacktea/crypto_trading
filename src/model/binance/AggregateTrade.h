#pragma once
#include <model/binance/Event.hpp>
#include <rapidjson/document.h>
#include <util/jsonBase.h>

namespace Binance
{
class AggregateTradeEvent : public JsonObject, public Event
{
public:
    bool deserialize(const rapidjson::Value & obj) override;
    std::string eventType;
    long long eventTime = 0;
    std::string symbol;
    long long aggTradeID = 0;
    std::string price;
    std::string quantity;
    long long firstTradeID = 0;
    long long lastTradeID = 0;
    long long tradeTime = 0;
    bool isMarketMaker;

private:
    void setEventType(std::string && _eventType) { eventType = std::move(_eventType); }

    void setEventTime(long long _eventTime) { eventTime = _eventTime; }

    void setSymbol(std::string && _symbol) { symbol = std::move(_symbol); }

    void setAggTradeID(long long _tradeID) { aggTradeID = _tradeID; }

    void setPrice(std::string && _price) { price = std::move(_price); }

    void setQuantity(std::string && _quantity) { quantity = std::move(_quantity); }

    void setFirstTradeID(long long _firstTradeID) { firstTradeID = _firstTradeID; }

    void setLastTradeID(long long _lastTradeID) { lastTradeID = _lastTradeID; }

    void setTradeTime(long long _time) { tradeTime = _time; }

    void setIsMarketMaker(bool _isMarketMaker) { isMarketMaker = _isMarketMaker; }
};


bool AggregateTradeEvent::deserialize(const rapidjson::Value & obj)
{
    setStream(obj["stream"].GetString());
    setEventType(obj["data"]["e"].GetString());
    setEventTime(obj["data"]["E"].GetInt64());
    setSymbol(obj["data"]["s"].GetString());
    setAggTradeID(obj["data"]["a"].GetInt64());
    setPrice(obj["data"]["p"].GetString());
    setQuantity(obj["data"]["q"].GetString());
    setFirstTradeID(obj["data"]["f"].GetInt64());
    setLastTradeID(obj["data"]["l"].GetInt64());
    setTradeTime(obj["data"]["T"].GetInt64());
    setIsMarketMaker(obj["data"]["m"].GetBool());
    return true;
}
}
