#pragma once
#include <rapidjson/document.h>
#include <util/jsonBase.h>

namespace Binance {
    class Trade : public JsonObject {
    public:
        bool deserialize(const rapidjson::Value &obj) override;

        std::string stream;
        std::string eventType;
        long long eventTime = 0;
        std::string symbol;
        long long tradeID = 0;
        std::string price;
        std::string quantity;
        long long tradeTime = 0;
        bool isMarketMaker;
    private:
        void setStream(std::string &&_stream) { stream = std::move(_stream); }

        void setEventType(std::string &&_eventType) { eventType = std::move(_eventType); }

        void setEventTime(long long _eventTime) { eventTime = _eventTime; }

        void setSymbol(std::string &&_symbol) { symbol = std::move(_symbol); }

        void setTradeID(long long _tradeID) { tradeID = _tradeID; }

        void setPrice(std::string &&_price) { price = std::move(_price); }

        void setQuantity(std::string &&_quantity) { quantity = std::move(_quantity); }

        void setTradeTime(long long _time) { tradeTime = _time; }

        void setIsMarketMaker(bool _isMarketMaker) { isMarketMaker = _isMarketMaker; }
    };


    bool Trade::deserialize(const rapidjson::Value &obj) {
        setStream(obj["stream"].GetString());
        setEventType(obj["data"]["e"].GetString());
        setEventTime(obj["data"]["E"].GetInt64());
        setSymbol(obj["data"]["s"].GetString());
        setTradeID(obj["data"]["t"].GetInt64());
        setPrice(obj["data"]["p"].GetString());
        setQuantity(obj["data"]["q"].GetString());
        setTradeTime(obj["data"]["T"].GetInt64());
        setIsMarketMaker(obj["data"]["m"].GetBool());
        return true;
    }
}
