#pragma once
#include <optional>
#include <exchanges/binance/model/Event.hpp>
#include <rapidjson/document.h>
#include <util/jsonBase.h>


namespace Binance
{
class QueryOrderResponse : public JsonObject
{
public:
    bool deserialize(const rapidjson::Value & obj) override;

    std::string symbol;
    long long orderID;
    std::string clientOrderId;
    std::optional<std::string> price;
    std::optional<std::string> origQty;
    std::optional<std::string> executedQty;
    std::optional<std::string> cummulativeQuoteQty;
    std::optional<std::string> status;
    std::optional<std::string> timeInForce;
    std::optional<std::string> type;
    std::optional<std::string> side;
    std::optional<std::string> stopPrice;
    long long time;
    long long updateTime;


    void setSymbol(std::string && _symbol) { symbol = std::move(_symbol); }

    void setOrderID(long long _orderID) { orderID = _orderID; }

    void setPrice(std::string && _price) { price.emplace(_price); }

    void setOrigQty(std::string && _origQty) { origQty.emplace(_origQty); }

    void setExecutedQty(std::string && _executedQty) { executedQty.emplace(_executedQty); }

    void setCummulativeQuoteQty(std::string && _cummulativeQuoteQty) { cummulativeQuoteQty.emplace(_cummulativeQuoteQty); }

    void setStatus(std::string && _status) { origQty.emplace(_status); }

    void setTimeInForce(std::string && _timeInForce) { origQty.emplace(_timeInForce); }

    void setType(std::string && _type) { origQty.emplace(_type); }

    void setSide(std::string && _side) { origQty.emplace(_side); }

    void setStopPrice(std::string && _stopPrice) { origQty.emplace(_stopPrice); }

    void setTime(long long _time) { time = _time; }

    void setUpdateTime(long long _updateTime) { updateTime = _updateTime; }
};

inline bool QueryOrderResponse::deserialize(const rapidjson::Value & obj)
{
    setSymbol(obj["symbol"].GetString());
    setOrderID(obj["orderID"].GetInt64());

    if (obj.HasMember("price"))
    {
        setPrice(obj["price"].GetString());
    }

    if (obj.HasMember("origQty"))
    {
        setOrigQty(obj["origQty"].GetString());
    }

    if (obj.HasMember("executedQty"))
    {
        setExecutedQty(obj["executedQty"].GetString());
    }

    if (obj.HasMember("cummulativeQuoteQty"))
    {
        setCummulativeQuoteQty(obj["cummulativeQuoteQty"].GetString());
    }

    if (obj.HasMember("status"))
    {
        setStatus(obj["status"].GetString());
    }

    if (obj.HasMember("timeInForce"))
    {
        setTimeInForce(obj["timeInForce"].GetString());
    }

    if (obj.HasMember("type"))
    {
        setType(obj["type"].GetString());
    }

    if (obj.HasMember("side"))
    {
        setSide(obj["side"].GetString());
    }

    if (obj.HasMember("stopPrice"))
    {
        setStopPrice(obj["stopPrice"].GetString());
    }

    setTime(obj["time"].GetInt64());
    setUpdateTime(obj["updateTime"].GetInt64());

    return true;
}
}