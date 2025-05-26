#pragma once
#include <charconv>
#include <string>
#include <flatbuffers/flatbuffers.h>
#include <model/gen/binance/binance_bookticker_generated.h>
#include <model/gen/binance/binance_kline_generated.h>
#include <model/gen/binance/binance_orderbook_generated.h>
#include <rapidjson/document.h>

namespace Gateway
{

inline double getDoubleValue(rapidjson::Document & document, const char * fieldName)
{
    const char * str = document[fieldName].GetString();
    auto len = strlen(str);
    double value;
    std::from_chars(str, str + len, value);
    return value;
}

inline long long getLongValue(rapidjson::Document & document, const char * fieldName)
{
    const char * str = document[fieldName].GetString();
    auto len = strlen(str);
    long long value;
    std::from_chars(str, str + len, value);
    return value;
}

inline flatbuffers::Offset<binance::BookTicker> jsonToBinaceBookTickerBuilder(rapidjson::Document & document, std::string_view asset)
{
    flatbuffers::FlatBufferBuilder builder;

    auto eventType = builder.CreateString(document["e"].GetString());
    auto assetType = builder.CreateString(asset.data());
    auto symbol = builder.CreateString(document["s"].GetString());

    auto bookticker = binance::CreateBookTicker(
        builder,
        eventType,
        assetType,
        symbol,
        getDoubleValue(document, "b"),
        getDoubleValue(document, "B"),
        getDoubleValue(document, "a"),
        getDoubleValue(document, "A"));

    builder.Finish(bookticker);
    return bookticker;
}

inline flatbuffers::Offset<binance::Kline> jsonToBinaceKline(rapidjson::Document & document, std::string_view asset)
{
    flatbuffers::FlatBufferBuilder builder;

    auto eventType = builder.CreateString(document["e"].GetString());
    auto assetType = builder.CreateString(asset.data());
    auto symbol = builder.CreateString(document["s"].GetString());

    auto klineTicker = binance::CreateKline(
        builder,
        eventType,
        assetType,
        symbol,
        getDoubleValue(document, "o"),
        getDoubleValue(document, "c"),
        getDoubleValue(document, "h"),
        getDoubleValue(document, "l"),
        getDoubleValue(document, "v"),
        getDoubleValue(document, "q"));

    builder.Finish(klineTicker);
    return klineTicker;
}

inline flatbuffers::Offset<binance::OrderBook> jsonToBinanceOrderbook(rapidjson::Document & document, std::string_view asset)
{
    flatbuffers::FlatBufferBuilder builder;

    auto eventType = builder.CreateString(document["e"].GetString());
    auto assetType = builder.CreateString(asset.data());
    auto symbol = builder.CreateString(document["s"].GetString());

    std::vector<binance::PriceLevel> bidVe;
    std::vector<binance::PriceLevel> askVe;

    auto & bidsNode = document["b"];
    for (int i = 0; i < bidsNode.Size(); ++i)
    {
        bidVe.emplace_back(bidsNode[i][0].GetDouble(), bidsNode[i][1].GetDouble());
    }

    auto & asksNode = document["a"];
    for (int i = 0; i < asksNode.Size(); ++i)
    {
        askVe.emplace_back(asksNode[i][0].GetDouble(), asksNode[i][1].GetDouble());
    }

    auto bids = builder.CreateVectorOfStructs(bidVe.data(), bidVe.size());
    auto asks = builder.CreateVectorOfStructs(askVe.data(), askVe.size());

    auto orderbookTicker = binance::CreateOrderBook(builder, eventType, assetType, symbol, getLongValue(document, "u"), bids, asks);

    builder.Finish(orderbookTicker);
    return orderbookTicker;
}

}