#pragma once
#include <rapidjson/document.h>
#include <util/jsonBase.h>

namespace Binance {
    class AggregateTradeEvent : public JsonObject {
    public:
        bool deserialize(const rapidjson::Value &obj) override;

        std::string eventType;
        long long eventTime = 0;
        std::string symbol;
        long long aggTradeID = 0;
        double price = 0.0;
        std::string quantity;
        long long firstTradeID = 0;
        long long lastTradeID = 0;
        long long tradeTime = 0;
        bool isMarketMaker;
    private:
        void setEventType(std::string &&_eventType) { eventType = std::move(_eventType); }

        void setEventTime(long long _eventTime) { eventTime = _eventTime; }

        void setSymbol(std::string &&_symbol) { symbol = std::move(_symbol); }

        void setAggTradeID(long long _tradeID) { aggTradeID = _tradeID; }

        void setPrice(std::string &&_price) { price = stod(_price); }

        void setQuantity(std::string &&_quantity) { quantity = std::move(_quantity); }

        void setFirstTradeID(long long _firstTradeID) { firstTradeID = _firstTradeID; }

        void setLastTradeID(long long _lastTradeID) { lastTradeID = _lastTradeID; }

        void setTradeTime(long long _time) { tradeTime = _time; }

        void setIsMarketMaker(bool _isMarketMaker) { isMarketMaker = _isMarketMaker; }
    };


    bool AggregateTradeEvent::deserialize(const rapidjson::Value &obj) {
        setEventType(obj["e"].GetString());
        setEventTime(obj["E"].GetInt64());
        setSymbol(obj["s"].GetString());
        setAggTradeID(obj["a"].GetInt64());
        setPrice(obj["p"].GetString());
        setQuantity(obj["q"].GetString());
        setFirstTradeID(obj["f"].GetInt64());
        setLastTradeID(obj["l"].GetInt64());
        setTradeTime(obj["T"].GetInt64());
        setIsMarketMaker(obj["m"].GetBool());
        return true;
    }
}
