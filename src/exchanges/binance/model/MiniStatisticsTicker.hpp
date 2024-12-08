#pragma once
#include <rapidjson/document.h>
#include <util/jsonBase.h>
#include <vector>
#include <exchanges/binance/model/Event.hpp>

namespace Binance {
    class MiniStatisticsTicker : public JsonObject {
    public:
        bool deserialize(const rapidjson::Value &obj) override;
        std::string eventType;
        long long eventTime = 0;
        std::string symbol;
        std::string closePrice;
        std::string openPrice;
        std::string highPrice;
        std::string lowPrice;
        std::string baseAssetVolume;
        std::string quoteAssetVolume;
    private:
        void setEventType(std::string &&_eventType) { eventType = std::move(_eventType); }

        void setEventTime(long long _eventTime) { eventTime = _eventTime; }

        void setSymbol(std::string &&_symbol) { symbol = std::move(_symbol); }

        void setClosePrice(std::string &&_price) { closePrice = std::move(_price); }

        void setOpenPrice(std::string &&_price) { openPrice = std::move(_price); }

        void setHighPrice(std::string &&_price) { highPrice = std::move(_price); }

        void setLowPrice(std::string &&_price) { lowPrice = std::move(_price); }

        void setBaseAssetVolume(std::string &&_baseAssetVolume) { baseAssetVolume = std::move(_baseAssetVolume); }

        void setQuoteAssetVolume(std::string &&_quoteAssetVolume) { quoteAssetVolume = std::move(_quoteAssetVolume); }
    };

    bool MiniStatisticsTicker::deserialize(const rapidjson::Value &obj) {
        setEventType(obj["e"].GetString());
        setEventTime(obj["E"].GetInt64());
        setSymbol(obj["s"].GetString());
        setClosePrice(obj["c"].GetString());
        setOpenPrice(obj["o"].GetString());
        setHighPrice(obj["h"].GetString());
        setLowPrice(obj["l"].GetString());
        setBaseAssetVolume(obj["v"].GetString());
        setQuoteAssetVolume(obj["q"].GetString());
        return true;
    }

    class MiniStatisticsTickerEvent : public JsonObject, public Event {
    public:
        bool deserialize(const rapidjson::Value &obj) override;
        MiniStatisticsTicker miniTicker;
    private:
        void setMiniStatisticsTicker(const rapidjson::Value &obj) { miniTicker.deserialize(obj);}
    };

    bool MiniStatisticsTickerEvent::deserialize(const rapidjson::Value &obj) {
        setStream(obj["stream"].GetString());
        setMiniStatisticsTicker(obj["data"]);
        return true;
    }


    class AllMiniStatisticsTickersEvent : public JsonObject, public Event {
    public:
        bool deserialize(const rapidjson::Value &obj) override;
        std::vector<MiniStatisticsTicker> tickers;
    private:
        void setMiniStatisticsTickers(const rapidjson::Value::ConstArray& array) {
            for (auto &item: array) {
                MiniStatisticsTicker ticker;
                ticker.deserialize(item);
                tickers.emplace_back(ticker);
            }
        }
    };


    bool AllMiniStatisticsTickersEvent::deserialize(const rapidjson::Value &obj) {
        setStream(obj["stream"].GetString());
        setMiniStatisticsTickers(obj["data"].GetArray());
        return true;
    }
}
