#pragma once
#include <model/binance/Event.hpp>
#include <rapidjson/document.h>
#include <util/jsonBase.h>

namespace Binance
{
[[deprecated]] DEFINE_CLASS(
    KLine,
    ((long long, startTime, t))((long long, closeTime, T))((std::string, symbol, s))((std::string, interval, i))(
        (long long, firstTradeID, f))((long long, lastTradeID, L))((std::string, openPrice, o))((std::string, closePrice, c))(
        (std::string, highPrice, h))((std::string, lowPrice, l))((std::string, baseAssetVolume, v))((int, numberTrades, n))(
        (bool, isKLineClosed, x))((std::string, quoteAssetVolume, q))((std::string, takerBuyAssetVolume, V))(
        (std::string, takerBuyQuoteVolume, Q)))

    [[deprecated]] DEFINE_CLASS(
        KLineData, ((std::string, eventType, e))((long long, eventTime, E))((std::string, symbol, s))((KLine, kLine, k)))
        [[deprecated]] DEFINE_CLASS(KLineEvent, ((std::string, stream, stream))((KLineData, data, data)))
}
