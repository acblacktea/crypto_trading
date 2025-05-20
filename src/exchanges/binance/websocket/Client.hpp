#pragma once
#include <model/binance/usdm/CancelOrder.hpp>
#include <model/binance/usdm/ModifyOrder.hpp>
#include <model/binance/usdm/NewOrder.hpp>
#include <model/binance/usdm/QueryOrder.hpp>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <util/SignatureGenerator.hpp>
#include <util/TimestampGenerator.hpp>
#include <util/WebsocketClient.h>
namespace Binance::Websocket
{
class SpotClient : public util::Websocket::Client
{
public:
    SpotClient()
    {
        host = "stream.binance.com";
        path = "/stream?streams=";
    }
};

class USDMClient : public util::Websocket::Client
{
public:
    USDMClient()
    {
        host = "fstream.binance.com";
        path = "/stream?streams=";
    }
};

class OrderUSDMClient : public util::Websocket::OrderClient
{
public:
    OrderUSDMClient(std::string apiKey, std::string secretKey)
        : OrderClient("ws-fapi.binance.com", "/ws-fapi/v1", "443")
        , apiKey_(apiKey)
        , secretKey_(secretKey)
    {
    }


    Binance::USDM::NewOrderResponse newOrder(Binance::USDM::NewOrderRequest & request)
    {
        request.method = "order.place";
        auto messageDocument = request.toJsonDocument();
        return Binance::USDM::NewOrderResponse::fromString(getResponseStr(messageDocument));
    }

    Binance::USDM::ModifyOrderResponse modifyOrder(Binance::USDM::ModifyOrderRequest & request)
    {
        request.method = "order.modify";
        auto messageDocument = request.toJsonDocument();
        return Binance::USDM::ModifyOrderResponse::fromString(getResponseStr(messageDocument));
    }

    Binance::USDM::CancelOrderResponse cancelOrder(Binance::USDM::CancelOrderRequest & request)
    {
        request.method = "order.cancel";
        auto messageDocument = request.toJsonDocument();
        return Binance::USDM::CancelOrderResponse::fromString(getResponseStr(messageDocument));
    }

    Binance::USDM::QueryOrderResponse queryOrder(Binance::USDM::QueryOrderRequest & request)
    {
        request.method = "order.status";
        auto messageDocument = request.toJsonDocument();
        return Binance::USDM::QueryOrderResponse::fromString(getResponseStr(messageDocument));
    }

    std::string getResponseStr(rapidjson::Document & messageDocument)
    {
        auto timestamp = generateMillisecond();
        rapidjson::Value IDkey("id");
        rapidjson::Value IDvalue;
        IDvalue.SetInt64(timestamp);
        messageDocument.AddMember(IDkey, IDvalue, messageDocument.GetAllocator());
        messageDocument["params"]["timestamp"].SetInt64(timestamp);

        auto signature = generateBinanceSignatureString(secretKey_, messageDocument["params"].GetObject());
        messageDocument["params"]["signature"].SetString(signature.data(), signature.size());


        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        messageDocument.Accept(writer);
        std::string message = buffer.GetString();
        return sendOrder(message);
    }

private:
    std::string apiKey_;
    std::string secretKey_;
};

class COINMClient : public util::Websocket::Client
{
public:
    COINMClient()
    {
        host = "wss://ws-dapi.binance.com/ws-dapi/v1";
        path = "/stream?streams=";
    }
};
}