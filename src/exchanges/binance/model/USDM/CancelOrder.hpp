#pragma once
#include <optional>
#include <exchanges/binance/model/Event.hpp>
#include <rapidjson/document.h>
#include <util/jsonBase.h>
namespace Binance
{
namespace USDM
{
DEFINE_CLASS(
    CancelOrderRequestParams,
    ((std::string, apiKey, apiKey))((std::string, signature, signature))((std::string, symbol, symbol))((long long, timestamp, timestamp))(
        (std::optional<long long>, orderId, orderId))((std::optional<long long>, recvWindow, recvWindow)))

DEFINE_CLASS(CancelOrderRequest, ((std::string, method, method))((CancelOrderRequestParams, params, params)))


DEFINE_CLASS(
    CancelOrderResponseResult,
    ((long long, orderId, orderId))((std::string, symbol, symbol))((std::string, status, status))(
        (std::string, clientOrderId, clientOrderId))((std::string, price, price))((std::string, avgPrice, avgPrice))(
        (std::string, origQty, origQty))((std::string, executedQty, executedQty))((std::string, cumQty, cumQty))(
        (std::string, cumQuote, cumQuote))((std::string, timeInForce, timeInForce))((std::string, type, type))(
        (bool, reduceOnly, reduceOnly))((bool, closePosition, closePosition))((std::string, side, side))(
        (std::string, positionSide, positionSide))((std::string, stopPrice, stopPrice))((std::string, workingType, workingType))(
        (bool, priceProtect, priceProtect))((std::string, origType, origType))((std::string, priceMatch, priceMatch))(
        (std::string, selfTradePreventionMode, selfTradePreventionMode))((long long, goodTillDate, goodTillDate))(
        (long long, updateTime, updateTime)))

DEFINE_CLASS(CancelOrderResponse, ((long long, status, status))((CancelOrderResponseResult, result, result)))
}
}
