#pragma once
#include <optional>
#include <exchanges/binance/model/Event.hpp>
#include <rapidjson/document.h>
#include <util/jsonBase.h>
namespace Binance
{
namespace USDM
{

DEFINE_CLASS(NewOrderRequestParams((std::string, apiKey, apiKey))((std::string, signature, signature))((std::string, symbol, symbol))(
    (std::string, type, type))((long long, timestamp, timestamp))((std::optional<std::string>, positionSide, positionSide))(
    (std::optional<std::string>, timeInForce, timeInForce))((std::optional<double>, quantity, quantity))(
    (std::optional<std::string>, reduceOnly, reduceOnly))((std::optional<std::string>, positionSide, positionSide))(
    (std::optional<std::string>, price, price))((std::optional<std::string>, stopPrice, stopPrice))(
    (std::optional<std::string>, closePosition, closePosition))((std::optional<std::string>, activationPrice, activationPrice))(
    (std::optional<std::string>, callbackRate, callbackRate))((std::optional<std::string>, workingType, workingType))(
    (std::optional<std::string>, priceProtect, priceProtect))((std::optional<std::string>, newOrderRespType, newOrderRespType))(
    (std::optional<std::string>, priceMatch, priceMatch))((std::optional<std::string>, selfTradePreventionMode, selfTradePreventionMode))(
    (std::optional<long long>, goodTillDate, goodTillDate))((std::optional<long long>, recvWindow, recvWindow)))

DEFINE_CLASS(NewOrderRequest((std::string, method, method))((NewOrderRequestParams, params, params)))


DEFINE_CLASS(NewOrderResponseResult(((long long, orderId, orderId))((std::string, symbol, symbol))((std::string, status, status))(
    (std::string, clientOrderId, clientOrderId))((std::string, price, price))((std::string, avgPrice, avgPrice))(
    (std::string, origQty, origQty))((std::string, executedQty, executedQty))((std::string, cumQty, cumQty))(
    (std::string, cumQuote, cumQuote))((std::string, timeInForce, timeInForce))((std::string, type, type))((bool, reduceOnly, reduceOnly))(
    (bool, closePosition, closePosition))((std::string, side, side))((std::string, positionSide, positionSide))(
    (std::string, stopPrice, stopPrice))((std::string, workingType, workingType))((bool, priceProtect, priceProtect))(
    (std::string, origType, origType))((std::string, priceMatch, priceMatch))(
    (std::string, selfTradePreventionMode, selfTradePreventionMode))((long long, goodTillDate, goodTillDate))(
    (long long, updateTime, updateTime))))

DEFINE_CLASS(NewOrderResponse((long long, status, status))((NewOrderResponseResult, result, result)))
}
}
