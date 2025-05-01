#pragma once
#include <exchanges/binance/model/Event.hpp>
#include <rapidjson/document.h>
#include <util/jsonBase.h>


namespace Binance
{
class TestNewOrderResponse : public JsonObject
{
public:
    bool deserialize(const rapidjson::Value & obj) override;

    std::string symbol;
    long long orderID;
    long long clientOrderID;
    long long transactionTime;

    void setSymbol(std::string && _symbol) { symbol = std::move(_symbol); }

    void setOrderID(long long _orderID) { orderID = _orderID; }

    void setClientOrderID(long long && _clientOrderID) { clientOrderID = _clientOrderID; }

    void setTransactionTime(long long && _transactionTime) { transactionTime = _transactionTime; }
};

inline bool TestNewOrderResponse::deserialize(const rapidjson::Value & obj)
{
    setSymbol(obj["symbol"].GetString());
    setOrderID(obj["orderID"].GetInt64());
    setClientOrderID(obj["setClientOrderID"].GetInt64());
    setTransactionTime(obj["setTransactionTime"].GetInt64());
    return true;
}
}