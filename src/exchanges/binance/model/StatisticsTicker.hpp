#pragma once
#include <vector>
#include <exchanges/binance/model/Event.hpp>
#include <rapidjson/document.h>
#include <util/jsonBase.h>

namespace Binance
{
class StatisticsTicker : public JsonObject
{
public:
    bool deserialize(const rapidjson::Value & obj) override;
    std::string eventType;
    long long eventTime = 0;
    std::string symbol;
    std::string priceChange;
    std::string priceChangePercent;
    std::string weightedAveragePrice;
    std::string firstTradePriceBefore24H;
    std::string lastPrice;
    std::string lastQuantity;
    std::string bestBidPrice;
    std::string bestBidQuantity;
    std::string bestAskPrice;
    std::string bestAskQuantity;
    std::string openPrice;
    std::string highPrice;
    std::string lowPrice;
    std::string baseAssetVolume;
    std::string quoteAssetVolume;
    long long statisticsOpenTime{};
    long long statisticsCloseTime{};
    long long firstTradeID{};
    long long lastTradeID{};
    int totalTradeNumbers{};

private:
    void setEventType(std::string && _eventType) { eventType = std::move(_eventType); }

    void setEventTime(long long _eventTime) { eventTime = _eventTime; }

    void setSymbol(std::string && _symbol) { symbol = std::move(_symbol); }

    void setPriceChange(std::string && _priceChange) { priceChange = std::move(_priceChange); }

    void setPriceChangePercent(std::string && _priceChangePercent) { priceChangePercent = std::move(_priceChangePercent); }

    void setWeightedAveragePrice(std::string && _weightedAveragePrice) { weightedAveragePrice = std::move(_weightedAveragePrice); }

    void setFirstTradePriceBefore24H(std::string && _firstTradePriceBefore24H)
    {
        firstTradePriceBefore24H = std::move(_firstTradePriceBefore24H);
    }

    void setLastPrice(std::string && _lastPrice) { lastPrice = std::move(_lastPrice); }

    void setLastQuantity(std::string && _lastQuantity) { lastQuantity = std::move(_lastQuantity); }

    void setBestBidPrice(std::string && _bestBidPrice) { bestBidPrice = std::move(_bestBidPrice); }

    void setBestBidQuantity(std::string && _bestBidQuantity) { bestBidQuantity = std::move(_bestBidQuantity); }

    void setBestAskPrice(std::string && _bestAskPrice) { bestAskPrice = std::move(_bestAskPrice); }

    void setBestAskQuantity(std::string && _bestAskQuantity) { bestAskQuantity = std::move(_bestAskQuantity); }

    void setOpenPrice(std::string && _price) { openPrice = std::move(_price); }

    void setHighPrice(std::string && _price) { highPrice = std::move(_price); }

    void setLowPrice(std::string && _price) { lowPrice = std::move(_price); }

    void setBaseAssetVolume(std::string && _baseAssetVolume) { baseAssetVolume = std::move(_baseAssetVolume); }

    void setQuoteAssetVolume(std::string && _quoteAssetVolume) { quoteAssetVolume = std::move(_quoteAssetVolume); }

    void setStatisticsOpenTime(long long _statisticsOpenTime) { statisticsOpenTime = _statisticsOpenTime; }

    void setStatisticsCloseTime(long long _statisticsCloseTime) { statisticsCloseTime = _statisticsCloseTime; }

    void setFirstTradeID(long long _firstTradeID) { firstTradeID = _firstTradeID; }

    void setLastTradeID(long long _lastTradeID) { lastTradeID = _lastTradeID; }

    void setTotalTradeNumbers(int _totalTradeNumbers) { totalTradeNumbers = _totalTradeNumbers; }
};

bool StatisticsTicker::deserialize(const rapidjson::Value & obj)
{
    setEventType(obj["e"].GetString());
    setEventTime(obj["E"].GetInt64());
    setSymbol(obj["s"].GetString());

    setPriceChange(obj["p"].GetString());
    setPriceChangePercent(obj["P"].GetString());
    setWeightedAveragePrice(obj["w"].GetString());
    setFirstTradePriceBefore24H(obj["x"].GetString());
    setLastPrice(obj["c"].GetString());
    setLastQuantity(obj["Q"].GetString());
    setBestBidPrice(obj["b"].GetString());
    setBestBidQuantity(obj["B"].GetString());
    setBestAskPrice(obj["a"].GetString());
    setBestAskQuantity(obj["A"].GetString());
    setOpenPrice(obj["o"].GetString());
    setHighPrice(obj["h"].GetString());
    setLowPrice(obj["l"].GetString());
    setBaseAssetVolume(obj["v"].GetString());
    setQuoteAssetVolume(obj["q"].GetString());

    setStatisticsOpenTime(obj["O"].GetInt64());
    setStatisticsCloseTime(obj["C"].GetInt64());
    setFirstTradeID(obj["F"].GetInt64());
    setLastTradeID(obj["L"].GetInt64());
    setTotalTradeNumbers(obj["n"].GetInt());
    return true;
}

class StatisticsTickerEvent : public JsonObject, public Event
{
public:
    bool deserialize(const rapidjson::Value & obj) override;
    StatisticsTicker ticker;

private:
    void setStatisticsTicker(const rapidjson::Value & obj) { ticker.deserialize(obj); }
};

bool StatisticsTickerEvent::deserialize(const rapidjson::Value & obj)
{
    setStream(obj["stream"].GetString());
    setStatisticsTicker(obj["data"]);
    return true;
}


class AllStatisticsTickersEvent : public JsonObject, public Event
{
public:
    bool deserialize(const rapidjson::Value & obj) override;
    std::vector<StatisticsTicker> tickers;

private:
    void setStatisticsTickers(const rapidjson::Value::ConstArray & array)
    {
        for (auto & item : array)
        {
            StatisticsTicker ticker;
            ticker.deserialize(item);
            tickers.emplace_back(ticker);
        }
    }
};


bool AllStatisticsTickersEvent::deserialize(const rapidjson::Value & obj)
{
    setStream(obj["stream"].GetString());
    setStatisticsTickers(obj["data"].GetArray());
    return true;
}
}
