#pragma once
#include <rapidjson/document.h>
#include <util/jsonBase.h>

namespace Binance {
    class KLine: public JsonObject {
    public:
        bool deserialize(const rapidjson::Value &obj) override;
        long long startTime;
        long long closeTime;
        std::string symbol;
        std::string interval;
        long long firstTradeID;
        long long lastTradeID;
        std::string openPrice;
        std::string closePrice;
        std::string highPrice;
        std::string lowPrice;
        std::string baseAssetVolume;
        int numberTrades;
        bool isKLineClosed;
        std::string quoteAssetVolume;
        std::string takerBuyAssetVolume;
        std::string takerBuyQuoteVolume;

        void setStartTime(long long _startTime) { startTime = _startTime; }
        void setCloseTime(long long _closeTime) { closeTime = _closeTime; }
        void setSymbol(std::string &&_symbol) { symbol = std::move(_symbol); }
        void setInterval(std::string &&_interval) { interval = std::move(_interval); }
        void setFirstTradeID(long long _firstTradeID) { firstTradeID = _firstTradeID; }
        void setLastTradeID(long long _lastTradeID) { lastTradeID = _lastTradeID; }
        void setOpenPrice(std::string &&_openPrice) { openPrice = std::move(_openPrice); }
        void setClosePrice(std::string &&_closePrice) { closePrice = std::move(_closePrice); }
        void setHighPrice(std::string &&_highPrice) { highPrice = std::move(_highPrice); }
        void setLowPrice(std::string &&_lowPrice) { lowPrice = std::move(_lowPrice); }
        void setBaseAssetVolume(std::string &&_baseAssetVolume) { baseAssetVolume = std::move(_baseAssetVolume); }
        void senNumberTrades(int _numberTrades) { numberTrades = _numberTrades;}
        void setIsKLineClosed(bool _isKLineClosed) { isKLineClosed = _isKLineClosed; }
        void setQuoteAssetVolume(std::string &&_quoteAssetVolume) { quoteAssetVolume = std::move(_quoteAssetVolume); }
        void setTakerBuyAssetVolume(std::string &&_takerBuyAssetVolume) { takerBuyAssetVolume = std::move(_takerBuyAssetVolume); }
        void setTakerBuyQuoteVolume(std::string &&_takerBuyQuoteVolume) { takerBuyQuoteVolume = std::move(_takerBuyQuoteVolume); }
    };

    bool KLine::deserialize(const rapidjson::Value &obj) {
        setStartTime(obj["t"].GetInt64());
        setCloseTime(obj["T"].GetInt64());
        setSymbol(obj["s"].GetString());
        setInterval(obj["i"].GetString());
        setFirstTradeID(obj["f"].GetInt64());
        setLastTradeID(obj["L"].GetInt64());
        setOpenPrice(obj["o"].GetString());
        setClosePrice(obj["c"].GetString());
        setHighPrice(obj["h"].GetString());
        setLowPrice(obj["l"].GetString());
        setBaseAssetVolume(obj["v"].GetString());
        senNumberTrades(obj["n"].GetInt());
        setIsKLineClosed(obj["x"].GetBool());
        setQuoteAssetVolume(obj["q"].GetString());
        setTakerBuyAssetVolume(obj["V"].GetString());
        setTakerBuyQuoteVolume(obj["Q"].GetString());

        return true;
    }


    class KLineEvent : public JsonObject {
    public:
        bool deserialize(const rapidjson::Value &obj) override;

        std::string stream;
        std::string eventType;
        long long eventTime = 0;
        std::string symbol;
        KLine kLine;
    private:
        void setStream(std::string &&_stream) { stream = std::move(_stream); }

        void setEventType(std::string &&_eventType) { eventType = std::move(_eventType); }

        void setEventTime(long long _eventTime) { eventTime = _eventTime; }

        void setSymbol(std::string &&_symbol) { symbol = std::move(_symbol); }

        void setKLine(const rapidjson::Value &obj) {
            kLine.deserialize(obj);
        }
    };


    bool KLineEvent::deserialize(const rapidjson::Value &obj) {
        setStream(obj["stream"].GetString());
        setEventType(obj["data"]["e"].GetString());
        setEventTime(obj["data"]["E"].GetInt64());
        setSymbol(obj["data"]["s"].GetString());
        setKLine(obj["data"]["k"]);
        return true;
    }
}
