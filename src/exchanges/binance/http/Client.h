#pragma once
#include <util/HTTPClient.h>
#include <exchanges/binance/model/NewOrderRequest.h>
#include <exchanges/binance/model/NewOrderResponse.h>
#include <exchanges/binance/model/TestNewOrderRequest.h>
#include <exchanges/binance/model/TestNewOrderResponse.h>
#include <exchanges/binance/model/CancelOrderRequest.h>
#include <exchanges/binance/model/CancelOrderResponse.h>
#include <exchanges/binance/model/QueryOrderRequest.h>
#include <exchanges/binance/model/QueryOrderResponse.h>

#include <utility>

//-------------------------------------------------------------------------------------
//is.set_option(urdl::http::request_content_type("application/json"));
//is.set_option(urdl::http::request_content("{\"username\":\"user@name.co\", \"password\":\"test\"}"));



namespace Binance::Http {
    class Client : public util::Http::Client {
    public:
        explicit Client(std::string _apiKey): apiKey(std::move(_apiKey)) {
            host = "api.binance.com";
            headers = {
                    {"User-Agent",   "Mozilla/4.0 (compatible; Node binance API)"},
                    {"Accept",       "application/json"},
                    {"Content-Type", "application/x-www-form-urlencoded"},
                    { "X-MBX-APIKEY", this->apiKey }
            };
        }

        std::tuple<NewOrderResponse, beast::error_code> newOrder(const NewOrderRequest &req);
        std::tuple<TestNewOrderResponse, beast::error_code> testNewOrder(const TestNewOrderRequest &req);
        std::tuple<CancelOrderResponse, beast::error_code> cancelOrder(const CancelOrderRequest &req);
        std::tuple<QueryOrderResponse, beast::error_code>  queryOrder(const QueryOrderRequest &req);
    private:
        std::string apiKey;
        std::string secretKey;
    };
}