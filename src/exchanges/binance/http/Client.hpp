#pragma once
#include <util/HTTPClient.h>

#include <utility>
#include <model/binance/PM.hpp>
#include <util/SignatureGenerator.hpp>
#include <util/TimestampGenerator.hpp>
//-------------------------------------------------------------------------------------
//is.set_option(urdl::http::request_content_type("application/json"));
//is.set_option(urdl::http::request_content("{\"username\":\"user@name.co\", \"password\":\"test\"}"));


namespace Binance
{
namespace Http
{
class Client : public util::Http::Client
{
public:
    Client() = default;
    explicit Client(std::string & apiKey, std::string & secretKey, std::string && host)
        : apiKey_(apiKey)
        , secretKey_(secretKey)
        , util::Http::Client(std::forward<std::string>(host))
    {
    }


protected:
    std::string apiKey_;
    std::string secretKey_;
};
}

namespace PM
{

const std::string UM_ORDER_PATH = "/papi/v1/um/order";
const std::string UM_CONDITIONAL_ORDER_PATH = "/papi/v1/um/conditional/order";

class Client : public Binance::Http::Client
{
public:
    Client(std::string & apiKey, std::string & secretKey)
        : Binance::Http::Client(apiKey, secretKey, "papi.binance.com")
    {
    }

    std::tuple<Binance::PM::NewUMOrderResponse, std::string> newUMOrder(Binance::PM::NewUMOrderRequest & request)
    {
        auto messageDocument = request.toJsonDocument();
        auto timestamp = generateMillisecond();
        messageDocument["timestamp"].SetInt64(timestamp);

        auto paramsStr = generateParamsString(messageDocument.GetObject(), false);
        auto signature = generateBinanceSignature(secretKey_, paramsStr);
        paramsStr += "&signature=" + signature;
        return post<Binance::PM::NewUMOrderResponse>(UM_ORDER_PATH, paramsStr, "", {{"X-MBX-APIKEY", apiKey_}});
    }

    std::tuple<Binance::PM::NewUMConditionalOrderResponse, std::string>
    newUMConditionalOrder(Binance::PM::NewUMConditionalOrderRequest & request)
    {
        auto messageDocument = request.toJsonDocument();
        auto timestamp = generateMillisecond();
        messageDocument["timestamp"].SetInt64(timestamp);

        auto paramsStr = generateParamsString(messageDocument.GetObject(), false);
        auto signature = generateBinanceSignature(secretKey_, paramsStr);
        paramsStr += "&signature=" + signature;
        return post<Binance::PM::NewUMConditionalOrderResponse>(UM_CONDITIONAL_ORDER_PATH, paramsStr, "", {{"X-MBX-APIKEY", apiKey_}});
    }

    std::tuple<Binance::PM::ModifyUMOrderResponse, std::string> modifyUMOrder(Binance::PM::ModifyUMOrderRequest & request)
    {
        auto messageDocument = request.toJsonDocument();
        auto timestamp = generateMillisecond();
        messageDocument["timestamp"].SetInt64(timestamp);

        auto paramsStr = generateParamsString(messageDocument.GetObject(), false);
        auto signature = generateBinanceSignature(secretKey_, paramsStr);
        paramsStr += "&signature=" + signature;
        return put<Binance::PM::ModifyUMOrderResponse>(UM_ORDER_PATH, paramsStr, "", {{"X-MBX-APIKEY", apiKey_}});
    }

    std::tuple<Binance::PM::CancelUMOrderResponse, std::string> cancelUMOrder(Binance::PM::CancelUMOrderRequest & request)
    {
        auto messageDocument = request.toJsonDocument();
        auto timestamp = generateMillisecond();
        messageDocument["timestamp"].SetInt64(timestamp);

        auto paramsStr = generateParamsString(messageDocument.GetObject(), false);
        auto signature = generateBinanceSignature(secretKey_, paramsStr);
        paramsStr += "&signature=" + signature;
        return delete_<Binance::PM::CancelUMOrderResponse>(UM_ORDER_PATH, paramsStr, "", {{"X-MBX-APIKEY", apiKey_}});
    }

    std::tuple<Binance::PM::QueryUMOrderResponse, std::string> queryUMOrder(Binance::PM::QueryUMOrderRequest & request)
    {
        auto messageDocument = request.toJsonDocument();
        auto timestamp = generateMillisecond();
        messageDocument["timestamp"].SetInt64(timestamp);

        auto paramsStr = generateParamsString(messageDocument.GetObject(), false);
        auto signature = generateBinanceSignature(secretKey_, paramsStr);
        paramsStr += "&signature=" + signature;
        return get<Binance::PM::QueryUMOrderResponse>(UM_ORDER_PATH, paramsStr, "", {{"X-MBX-APIKEY", apiKey_}});
    }

private:
};
}

namespace CoinM
{
class CoinmClient : public Binance::Http::Client
{
};
}
}
