#pragma once
#include <optional>
#include <rapidjson/document.h>
#include <util/jsonBase.h>
namespace Binance
{
namespace USDM
{
DEFINE_CLASS(
    ModifyOrderRequestParams,
    ((std::string, apiKey, apiKey))((std::string, signature, signature))((long long, orderId, orderId))((std::string, symbol, symbol))(
        (long long, timestamp, timestamp))((std::string, quantity, quantity))((std::string, price, price))((std::string, side, side))(
        (std::optional<std::string>, priceMatch, priceMatch))((std::optional<long long>, recvWindow, recvWindow)))

DEFINE_CLASS(ModifyOrderRequest, ((std::string, method, method))((ModifyOrderRequestParams, params, params)))


DEFINE_CLASS(
    ModifyOrderResponseResult,
    ((long long, orderId, orderId))((std::string, symbol, symbol))((std::string, status, status))(
        (std::string, clientOrderId, clientOrderId))((std::string, price, price))((std::string, avgPrice, avgPrice))(
        (std::string, origQty, origQty))((std::string, executedQty, executedQty))((std::string, cumQty, cumQty))(
        (std::string, cumQuote, cumQuote))((std::string, timeInForce, timeInForce))((std::string, type, type))(
        (bool, reduceOnly, reduceOnly))((bool, closePosition, closePosition))((std::string, side, side))(
        (std::string, positionSide, positionSide))((std::string, stopPrice, stopPrice))((std::string, workingType, workingType))(
        (bool, priceProtect, priceProtect))((std::string, origType, origType))((std::string, priceMatch, priceMatch))(
        (std::string, selfTradePreventionMode, selfTradePreventionMode))((long long, goodTillDate, goodTillDate))(
        (long long, updateTime, updateTime)))

DEFINE_CLASS(ModifyOrderResponse, ((long long, status, status))((ModifyOrderResponseResult, result, result)))
}
}
