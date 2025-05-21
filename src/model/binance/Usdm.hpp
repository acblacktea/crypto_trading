#pragma once
#include <optional>
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

DEFINE_CLASS(CancelOrderResponse, ((long long, status, status))((std::optional<CancelOrderResponseResult>, result, result)))

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

DEFINE_CLASS(ModifyOrderResponse, ((long long, status, status))((std::optional<ModifyOrderResponseResult>, result, result)))

DEFINE_CLASS(
    NewOrderRequestParams,
    ((std::string, apiKey, apiKey))((std::string, signature, signature))((std::string, symbol, symbol))((std::string, side, side))(
        (std::string, type, type))((long long, timestamp, timestamp))((std::optional<std::string>, positionSide, positionSide))(
        (std::optional<std::string>, timeInForce, timeInForce))((std::optional<std::string>, quantity, quantity))(
        (std::optional<std::string>, reduceOnly, reduceOnly))((std::optional<std::string>, price, price))(
        (std::optional<std::string>, stopPrice, stopPrice))((std::optional<std::string>, closePosition, closePosition))(
        (std::optional<std::string>, activationPrice, activationPrice))((std::optional<std::string>, callbackRate, callbackRate))(
        (std::optional<std::string>, workingType, workingType))((std::optional<std::string>, priceProtect, priceProtect))(
        (std::optional<std::string>, newOrderRespType, newOrderRespType))((std::optional<std::string>, priceMatch, priceMatch))(
        (std::optional<std::string>, selfTradePreventionMode, selfTradePreventionMode))(
        (std::optional<long long>, goodTillDate, goodTillDate))((std::optional<long long>, recvWindow, recvWindow)))

DEFINE_CLASS(NewOrderRequest, ((std::string, method, method))((NewOrderRequestParams, params, params)))


DEFINE_CLASS(
    NewOrderResponseResult,
    ((long long, orderId, orderId))((std::string, symbol, symbol))((std::string, status, status))(
        (std::string, clientOrderId, clientOrderId))((std::string, price, price))((std::string, avgPrice, avgPrice))(
        (std::string, origQty, origQty))((std::string, executedQty, executedQty))((std::string, cumQty, cumQty))(
        (std::string, cumQuote, cumQuote))((std::string, timeInForce, timeInForce))((std::string, type, type))(
        (bool, reduceOnly, reduceOnly))((bool, closePosition, closePosition))((std::string, side, side))(
        (std::string, positionSide, positionSide))((std::string, stopPrice, stopPrice))((std::string, workingType, workingType))(
        (bool, priceProtect, priceProtect))((std::string, origType, origType))((std::string, priceMatch, priceMatch))(
        (std::string, selfTradePreventionMode, selfTradePreventionMode))((long long, goodTillDate, goodTillDate))(
        (long long, updateTime, updateTime)))

DEFINE_CLASS(NewOrderResponse, ((long long, status, status))((std::optional<NewOrderResponseResult>, result, result)))

DEFINE_CLASS(
    QueryOrderRequestParams,
    ((std::string, apiKey, apiKey))((std::string, signature, signature))((std::string, symbol, symbol))((long long, timestamp, timestamp))(
        (std::optional<long long>, orderId, orderId))((std::optional<long long>, recvWindow, recvWindow)))

DEFINE_CLASS(QueryOrderRequest, ((std::string, method, method))((QueryOrderRequestParams, params, params)))

DEFINE_CLASS(
    QueryOrderResponseResult,
    ((long long, orderId, orderId))((std::string, symbol, symbol))((std::string, status, status))(
        (std::string, clientOrderId, clientOrderId))((std::string, price, price))((std::string, avgPrice, avgPrice))(
        (std::string, origQty, origQty))((std::string, executedQty, executedQty))((std::optional<std::string>, cumQty, cumQty))(
        (std::string, cumQuote, cumQuote))((std::string, timeInForce, timeInForce))((std::string, type, type))(
        (bool, reduceOnly, reduceOnly))((bool, closePosition, closePosition))((std::string, side, side))(
        (std::string, positionSide, positionSide))((std::string, stopPrice, stopPrice))((std::string, workingType, workingType))(
        (bool, priceProtect, priceProtect))((std::string, origType, origType))((std::string, priceMatch, priceMatch))(
        (std::string, selfTradePreventionMode, selfTradePreventionMode))((long long, goodTillDate, goodTillDate))(
        (long long, updateTime, updateTime))((std::optional<std::string>, activatePrice, activatePrice))(
        (std::optional<std::string>, priceRate, priceRate)))

DEFINE_CLASS(QueryOrderResponse, ((long long, status, status))((std::optional<QueryOrderResponseResult>, result, result)))

}
}
