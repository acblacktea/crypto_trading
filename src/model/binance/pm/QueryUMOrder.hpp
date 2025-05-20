#pragma once
#include <optional>
#include <rapidjson/document.h>
#include <util/jsonBase.h>
namespace Binance
{
namespace PM
{

DEFINE_CLASS(
    QueryUMOrderRequest,
    ((std::string, symbol, symbol))((long long, timestamp, timestamp))((std::optional<long long>, orderId, orderId))(
        (std::optional<std::string>, origClientOrderId, origClientOrderId))((std::optional<long long>, recvWindow, recvWindow)))

DEFINE_CLASS(
    QueryUMOrderResponse,
    ((std::string, avgPrice, avgPrice))((std::string, clientOrderId, clientOrderId))((std::string, cumQuote, cumQuote))(
        (std::string, executedQty, executedQty))((long long, orderId, orderId))((std::string, origQty, origQty))(
        (std::string, origType, origType))((std::string, price, price))((bool, reduceOnly, reduceOnly))((std::string, side, side))(
        (std::string, positionSide, positionSide))((std::string, status, status))((std::string, symbol, symbol))((long long, time, time))(
        (std::string, timeInForce, timeInForce))((std::string, type, type))((long long, updateTime, updateTime))(
        (std::string, selfTradePreventionMode, selfTradePreventionMode))((long long, goodTillDate, goodTillDate))(
        (std::string, priceMatch, priceMatch)))
}
}
