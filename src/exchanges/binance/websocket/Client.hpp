#pragma once
#include <model/binance/Usdm.hpp>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <util/SignatureGenerator.hpp>
#include <util/TimestampGenerator.hpp>
#include <util/WebsocketClient.h>

namespace Binance
{
namespace Spot
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
}

namespace USDM
{
class MarketDataClient : public util::Websocket::Client
{
public:
    MarketDataClient()
    {
        host = "fstream.binance.com";
        path = "/stream?streams=";
    }
};

class OrderClient : public util::Websocket::RequestClient
{
public:
    OrderClient(std::string apiKey, std::string secretKey)
        : RequestClient("ws-fapi.binance.com", "/ws-fapi/v1", "443")
        , apiKey_(apiKey)
        , secretKey_(secretKey)
    {
    }


    Binance::USDM::NewOrderResponse newOrder(Binance::USDM::NewOrderRequest & request)
    {
        request.method = "order.place";
        auto messageDocument = request.toJsonDocument();
        return Binance::USDM::NewOrderResponse::fromString(getRequestStr(messageDocument));
    }

    Binance::USDM::ModifyOrderResponse modifyOrder(Binance::USDM::ModifyOrderRequest & request)
    {
        request.method = "order.modify";
        auto messageDocument = request.toJsonDocument();
        return Binance::USDM::ModifyOrderResponse::fromString(getRequestStr(messageDocument));
    }

    Binance::USDM::CancelOrderResponse cancelOrder(Binance::USDM::CancelOrderRequest & request)
    {
        request.method = "order.cancel";
        auto messageDocument = request.toJsonDocument();
        return Binance::USDM::CancelOrderResponse::fromString(getRequestStr(messageDocument));
    }

    Binance::USDM::QueryOrderResponse queryOrder(Binance::USDM::QueryOrderRequest & request)
    {
        request.method = "order.status";
        auto messageDocument = request.toJsonDocument();
        return Binance::USDM::QueryOrderResponse::fromString(getRequestStr(messageDocument));
    }

    std::string getRequestStr(rapidjson::Document & messageDocument)
    {
        auto timestamp = generateMillisecond();
        rapidjson::Value IDkey("id");
        rapidjson::Value IDvalue;
        IDvalue.SetInt64(timestamp);
        messageDocument.AddMember(IDkey, IDvalue, messageDocument.GetAllocator());
        messageDocument["params"]["timestamp"].SetInt64(timestamp);

        auto signature = generateBinanceSignatureString(secretKey_, messageDocument["params"].GetObject(), true);
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
}

namespace CoinM
{
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
}