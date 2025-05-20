#pragma once
#include <optional>
#include <rapidjson/document.h>
#include <util/jsonBase.h>
namespace Binance
{
namespace PM
{

DEFINE_CLASS(
    NewUMConditionalOrderRequest,
    ((std::string, symbol, symbol))((std::string, side, side))((std::string, strategyType, strategyType))(
        (std::string, timestamp, timestamp))((std::optional<std::string>, positionSide, positionSide))(
        (std::optional<std::string>, timeInForce, timeInForce))((std::optional<std::string>, quantity, quantity))(
        (std::optional<std::string>, reduceOnly, reduceOnly))((std::optional<std::string>, price, price))(
        (std::optional<std::string>, workingType, workingType))((std::optional<std::string>, priceProtect, priceProtect))(
        (std::optional<std::string>, stopPrice, stopPrice))((std::optional<std::string>, activationPrice, activationPrice))(
        (std::optional<std::string>, callbackRate, callbackRate))((std::optional<std::string>, priceMatch, priceMatch))(
        (std::optional<std::string>, selfTradePreventionMode, selfTradePreventionMode))((long long, goodTillDate, goodTillDate))(
        (long long, recvWindow, recvWindow)))

DEFINE_CLASS(
    NewUMConditionalOrderResponse,
    ((std::string, newClientStrategyId, newClientStrategyId))((long long, strategyId, strategyId))(
        (std::string, strategyStatus, strategyStatus))((std::string, strategyType, strategyType))((std::string, origQty, origQty))(
        (std::string, price, price))((bool, reduceOnly, reduceOnly))((std::string, side, side))((std::string, positionSide, positionSide))(
        (std::string, stopPrice, stopPrice))((std::string, symbol, symbol))((std::string, timeInForce, timeInForce))(
        (std::string, activatePrice, activatePrice))((std::string, priceRate, priceRate))((long long, bookTime, bookTime))(
        (long long, updateTime, updateTime))((std::string, workingType, workingType))((bool, priceProtect, priceProtect))(
        (std::string, selfTradePreventionMode, selfTradePreventionMode))((long long, goodTillDate, goodTillDate))(
        (std::string, priceMatch, priceMatch)))
}
}
