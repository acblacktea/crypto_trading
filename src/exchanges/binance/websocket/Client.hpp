#pragma once
#include <model/binance/USDM/CancelOrder.hpp>
#include <model/binance/USDM/ModifyOrder.hpp>
#include <model/binance/USDM/NewOrder.hpp>
#include <model/binance/USDM/QueryOrder.hpp>
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
    OrderUSDMClient()
        : OrderClient("ws-fapi.binance.com", "/ws-fapi/v1", "443")
    {
    }


    Binance::USDM::NewOrderResponse newOrder(Binance::USDM::NewOrderRequest & request, std::string & secretKey)
    {
        request.method = "order.place";
        auto messageDocument = request.toJsonDocument();
        return Binance::USDM::NewOrderResponse::fromString(getResponseStr(messageDocument, secretKey));
    }

    Binance::USDM::ModifyOrderResponse modifyOrder(Binance::USDM::ModifyOrderRequest & request, std::string & secretKey)
    {
        request.method = "order.modify";
        auto messageDocument = request.toJsonDocument();
        return Binance::USDM::ModifyOrderResponse::fromString(getResponseStr(messageDocument, secretKey));
    }

    Binance::USDM::CancelOrderResponse cancelOrder(Binance::USDM::CancelOrderRequest & request, std::string & secretKey)
    {
        request.method = "order.cancel";
        auto messageDocument = request.toJsonDocument();
        return Binance::USDM::CancelOrderResponse::fromString(getResponseStr(messageDocument, secretKey));
    }

    Binance::USDM::QueryOrderResponse queryOrder(Binance::USDM::QueryOrderRequest & request, std::string & secretKey)
    {
        request.method = "order.status";
        auto messageDocument = request.toJsonDocument();
        return Binance::USDM::QueryOrderResponse::fromString(getResponseStr(messageDocument, secretKey));
    }

    std::string getResponseStr(rapidjson::Document & messageDocument, std::string & secretKey)
    {
        auto timestamp = generateMillisecond();
        std::cout << timestamp << std::endl;
        rapidjson::Value IDkey("id");
        rapidjson::Value IDvalue;
        IDvalue.SetInt64(timestamp);
        messageDocument.AddMember(IDkey, IDvalue, messageDocument.GetAllocator());
        messageDocument["params"]["timestamp"].SetInt64(timestamp);

        auto signature = generateBinanceSignatureString(secretKey, messageDocument["params"].GetObject());
        messageDocument["params"]["signature"].SetString(signature.data(), signature.size());


        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        messageDocument.Accept(writer);
        std::string message = buffer.GetString();
        return sendOrder(message);
    }
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