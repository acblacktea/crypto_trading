#pragma once
#include <exchanges/binance/model/Event.hpp>
#include <rapidjson/document.h>
#include <util/jsonBase.h>

namespace Binance
{
class AveragePriceEvent : public JsonObject, public Event
{
public:
    bool deserialize(const rapidjson::Value & obj) override;
    std::string eventType;
    long long eventTime;
    std::string symbol;
    std::string interval;
    std::string averagePrice;
    long long lastTradeTime;

private:
    void setEventType(std::string && _eventType) { eventType = std::move(_eventType); }

    void setEventTime(long long _eventTime) { eventTime = _eventTime; }

    void setSymbol(std::string && _symbol) { symbol = std::move(_symbol); }

    void setInterval(std::string && _interval) { interval = std::move(_interval); }

    void setAveragePrice(std::string && _averagePrice) { averagePrice = std::move(_averagePrice); }

    void setLastTradeTime(long long _lastTradeTime) { lastTradeTime = _lastTradeTime; }
};


bool AveragePriceEvent::deserialize(const rapidjson::Value & obj)
{
    setStream(obj["stream"].GetString());
    setEventType(obj["data"]["e"].GetString());
    setEventTime(obj["data"]["E"].GetInt64());
    setSymbol(obj["data"]["s"].GetString());
    setInterval(obj["data"]["i"].GetString());
    setAveragePrice(obj["data"]["w"].GetString());
    setLastTradeTime(obj["data"]["T"].GetInt64());
    return true;
}
}
