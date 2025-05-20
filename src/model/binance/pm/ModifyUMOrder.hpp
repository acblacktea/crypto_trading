#pragma once
#include <optional>
#include <rapidjson/document.h>
#include <util/jsonBase.h>
namespace Binance
{
namespace PM
{

DEFINE_CLASS(
    ModifyUMOrderRequest,
    ((std::string, symbol, symbol))((std::string, side, side))((std::string, quantity, quantity))((std::string, price, price))(
        (long long, timestamp, timestamp))((std::optional<long long>, orderId, orderId))(
        (std::optional<std::string>, origClientOrderId, origClientOrderId))((std::optional<std::string>, priceMatch, priceMatch))(
        (std::optional<long long>, recvWindow, recvWindow)))

DEFINE_CLASS(
    ModifyUMOrderResponse,
    ((std::string, clientOrderId, clientOrderId))((std::string, cumQty, cumQty))((std::string, cumQuote, cumQuote))(
        (std::string, executedQty, executedQty))((long long, orderId, orderId))((std::string, avgPrice, avgPrice))(
        (std::string, origQty, origQty))((std::string, price, price))((bool, reduceOnly, reduceOnly))((std::string, side, side))(
        (std::string, positionSide, positionSide))((std::string, status, status))((std::string, symbol, symbol))((
        std::string, timeInForce, timeInForce))((std::string, type, type))((std::string, selfTradePreventionMode, selfTradePreventionMode))(
        (long long, goodTillDate, goodTillDate))((long long, updateTime, updateTime))((std::string, priceMatch, priceMatch)))
}
}
