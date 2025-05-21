#pragma once
#include <optional>
#include <rapidjson/document.h>
#include <util/jsonBase.h>
namespace Binance
{
namespace PM
{

DEFINE_CLASS(
    CancelUMOrderRequest,
    ((std::string, symbol, symbol))((long long, timestamp, timestamp))((std::optional<long long>, orderId, orderId))(
        (std::optional<std::string>, origClientOrderId, origClientOrderId))((std::optional<long long>, recvWindow, recvWindow)))

DEFINE_CLASS(
    CancelUMOrderResponse,
    ((std::optional<std::string>, avgPrice, avgPrice))((std::optional<std::string>, clientOrderId, clientOrderId))(
        (std::optional<std::string>, cumQty, cumQty))((std::optional<std::string>, cumQuote, cumQuote))(
        (std::optional<std::string>, executedQty, executedQty))((std::optional<long long>, orderId, orderId))(
        (std::optional<std::string>, origQty, origQty))((std::optional<std::string>, price, price))(
        (std::optional<bool>, reduceOnly, reduceOnly))((std::optional<std::string>, side, side))(
        (std::optional<std::string>, positionSide, positionSide))((std::optional<std::string>, status, status))(
        (std::optional<std::string>, symbol, symbol))((std::optional<std::string>, timeInForce, timeInForce))(
        (std::optional<std::string>, type, type))((std::optional<long long>, updateTime, updateTime))(
        (std::optional<std::string>, selfTradePreventionMode, selfTradePreventionMode))(
        (std::optional<long long>, goodTillDate, goodTillDate))((std::optional<std::string>, priceMatch, priceMatch))(
        (std::optional<int>, code, code))((std::optional<std::string>, msg, msg)))

DEFINE_CLASS(
    ModifyUMOrderRequest,
    ((std::string, symbol, symbol))((std::string, side, side))((std::string, quantity, quantity))((std::string, price, price))(
        (long long, timestamp, timestamp))((std::optional<long long>, orderId, orderId))(
        (std::optional<std::string>, origClientOrderId, origClientOrderId))((std::optional<std::string>, priceMatch, priceMatch))(
        (std::optional<long long>, recvWindow, recvWindow)))

DEFINE_CLASS(
    ModifyUMOrderResponse,
    ((std::optional<std::string>, clientOrderId, clientOrderId))((std::optional<std::string>, cumQty, cumQty))(
        (std::optional<std::string>, cumQuote, cumQuote))((std::optional<std::string>, executedQty, executedQty))(
        (std::optional<long long>, orderId, orderId))((std::optional<std::string>, avgPrice, avgPrice))(
        (std::optional<std::string>, origQty, origQty))((std::optional<std::string>, price, price))(
        (std::optional<bool>, reduceOnly, reduceOnly))((std::optional<std::string>, side, side))(
        (std::optional<std::string>, positionSide, positionSide))((std::optional<std::string>, status, status))(
        (std::optional<std::string>, symbol, symbol))((std::optional<std::string>, timeInForce, timeInForce))(
        (std::optional<std::string>, type, type))((std::optional<std::string>, selfTradePreventionMode, selfTradePreventionMode))(
        (std::optional<long long>, goodTillDate, goodTillDate))((std::optional<long long>, updateTime, updateTime))(
        (std::optional<std::string>, priceMatch, priceMatch))((std::optional<int>, code, code))((std::optional<std::string>, msg, msg)))


DEFINE_CLASS(
    NewUMConditionalOrderRequest,
    ((std::string, symbol, symbol))((std::string, side, side))((std::string, strategyType, strategyType))(
        (std::string, timestamp, timestamp))((std::optional<std::string>, positionSide, positionSide))(
        (std::optional<std::string>, timeInForce, timeInForce))((std::optional<std::string>, quantity, quantity))(
        (std::optional<std::string>, reduceOnly, reduceOnly))((std::optional<std::string>, price, price))(
        (std::optional<std::string>, workingType, workingType))((std::optional<std::string>, priceProtect, priceProtect))(
        (std::optional<std::string>, stopPrice, stopPrice))((std::optional<std::string>, activationPrice, activationPrice))(
        (std::optional<std::string>, callbackRate, callbackRate))((std::optional<std::string>, priceMatch, priceMatch))(
        (std::optional<std::string>, selfTradePreventionMode, selfTradePreventionMode))(
        (std::optional<long long>, goodTillDate, goodTillDate))((std::optional<long long>, recvWindow, recvWindow)))

DEFINE_CLASS(
    NewUMConditionalOrderResponse,
    ((std::optional<std::string>, newClientStrategyId, newClientStrategyId))((std::optional<long long>, strategyId, strategyId))(
        (std::optional<std::string>, strategyStatus, strategyStatus))((std::optional<std::string>, strategyType, strategyType))(
        (std::optional<std::string>, origQty, origQty))((std::optional<std::string>, price, price))(
        (std::optional<bool>, reduceOnly, reduceOnly))((std::optional<std::string>, side, side))(
        (std::optional<std::string>, positionSide, positionSide))((std::optional<std::string>, stopPrice, stopPrice))(
        (std::optional<std::string>, symbol, symbol))((std::optional<std::string>, timeInForce, timeInForce))(
        (std::optional<std::string>, activatePrice, activatePrice))((std::optional<std::string>, priceRate, priceRate))(
        (std::optional<long long>, bookTime, bookTime))((std::optional<long long>, updateTime, updateTime))(
        (std::optional<std::string>, workingType, workingType))((std::optional<bool>, priceProtect, priceProtect))(
        (std::optional<std::string>, selfTradePreventionMode, selfTradePreventionMode))(
        (std::optional<long long>, goodTillDate, goodTillDate))((std::optional<std::string>, priceMatch, priceMatch))(
        (std::optional<int>, code, code))((std::optional<std::string>, msg, msg)))

DEFINE_CLASS(
    NewUMOrderRequest,
    ((std::string, symbol, symbol))((std::string, side, side))((std::string, type, type))((std::string, timestamp, timestamp))(
        (std::optional<std::string>, positionSide, positionSide))((std::optional<std::string>, timeInForce, timeInForce))(
        (std::optional<std::string>, quantity, quantity))((std::optional<std::string>, reduceOnly, reduceOnly))(
        (std::optional<std::string>, price, price))((std::optional<std::string>, priceMatch, priceMatch))(
        (std::optional<std::string>, selfTradePreventionMode, selfTradePreventionMode))(
        (std::optional<long long>, goodTillDate, goodTillDate))((std::optional<long long>, recvWindow, recvWindow)))

DEFINE_CLASS(
    NewUMOrderResponse,
    ((std::optional<std::string>, clientOrderId, clientOrderId))((std::optional<std::string>, cumQty, cumQty))(
        (std::optional<std::string>, cumQuote, cumQuote))((std::optional<std::string>, executedQty, executedQty))(
        (std::optional<long long>, orderId, orderId))((std::optional<std::string>, avgPrice, avgPrice))(
        (std::optional<std::string>, origQty, origQty))((std::optional<std::string>, price, price))(
        (std::optional<bool>, reduceOnly, reduceOnly))((std::optional<std::string>, side, side))(
        (std::optional<std::string>, positionSide, positionSide))((std::optional<std::string>, status, status))(
        (std::optional<std::string>, symbol, symbol))((std::optional<std::string>, timeInForce, timeInForce))(
        (std::optional<std::string>, type, type))((std::optional<std::string>, selfTradePreventionMode, selfTradePreventionMode))(
        (std::optional<long long>, goodTillDate, goodTillDate))((std::optional<long long>, updateTime, updateTime))(
        (std::optional<std::string>, priceMatch, priceMatch))((std::optional<int>, code, code))((std::optional<std::string>, msg, msg)))

DEFINE_CLASS(
    QueryUMOrderRequest,
    ((std::string, symbol, symbol))((long long, timestamp, timestamp))((std::optional<long long>, orderId, orderId))(
        (std::optional<std::string>, origClientOrderId, origClientOrderId))((std::optional<long long>, recvWindow, recvWindow)))

DEFINE_CLASS(
    QueryUMOrderResponse,
    ((std::optional<std::string>, avgPrice, avgPrice))((std::optional<std::string>, clientOrderId, clientOrderId))(
        (std::optional<std::string>, cumQuote, cumQuote))((std::optional<std::string>, executedQty, executedQty))(
        (std::optional<long long>, orderId, orderId))((std::optional<std::string>, origQty, origQty))(
        (std::optional<std::string>, origType, origType))((std::optional<std::string>, price, price))(
        (std::optional<bool>, reduceOnly, reduceOnly))((std::optional<std::string>, side, side))(
        (std::optional<std::string>, positionSide, positionSide))((std::optional<std::string>, status, status))(
        (std::optional<std::string>, symbol, symbol))((std::optional<long long>, time, time))(
        (std::optional<std::string>, timeInForce, timeInForce))((std::optional<std::string>, type, type))(
        (std::optional<long long>, updateTime, updateTime))((std::optional<std::string>, selfTradePreventionMode, selfTradePreventionMode))(
        (std::optional<long long>, goodTillDate, goodTillDate))((std::optional<std::string>, priceMatch, priceMatch))(
        (std::optional<int>, code, code))((std::optional<std::string>, msg, msg)))
}
}
