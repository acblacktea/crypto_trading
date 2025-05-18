#pragma once
#include <optional>
#include <rapidjson/document.h>
#include <util/jsonBase.h>
namespace Binance
{
namespace USDM
{
DEFINE_CLASS(
    QueryOrderRequestParams,
    ((std::string, apiKey, apiKey))((std::string, signature, signature))((std::string, symbol, symbol))((long long, timestamp, timestamp))(
        (std::optional<long long>, orderId, orderId))((std::optional<long long>, recvWindow, recvWindow)))

DEFINE_CLASS(QueryOrderRequest, ((std::string, method, method))((QueryOrderRequestParams, params, params)))

/*
{"id":1747568884961,"status":200,"result":{"orderId":685989929304,"symbol":"BTCUSDT","status":"NEW","clientOrderId":"93Mbegwes6NHYIiwcodq68","price":"50000.00","avgPrice":"0.00","origQty":"0.002","executedQty":"0.000","cumQuote":"0.00000","timeInForce":"GTC","type":"LIMIT","reduceOnly":false,"closePosition":false,"side":"BUY","positionSide":"BOTH","stopPrice":"0.00","workingType":"CONTRACT_PRICE","priceProtect":false,"origType":"LIMIT","priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0,"time":1747568334548,"updateTime":1747568334548},"rateLimits":[{"rateLimitType":"REQUEST_WEIGHT","interval":"MINUTE","intervalNum":1,"limit":2400,"count":30}]}
*/

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

DEFINE_CLASS(QueryOrderResponse, ((long long, status, status))((QueryOrderResponseResult, result, result)))
}
}
