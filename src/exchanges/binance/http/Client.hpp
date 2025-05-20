#pragma once
#include <util/HTTPClient.h>

#include <utility>
#include <model/binance/pm/CancelUMOrder.hpp>
#include <model/binance/pm/ModifyUMOrder.hpp>
#include <model/binance/pm/NewUMConditionalOrder.hpp>
#include <model/binance/pm/NewUMOrder.hpp>
#include <model/binance/pm/QueryUMOrder.hpp>

//-------------------------------------------------------------------------------------
//is.set_option(urdl::http::request_content_type("application/json"));
//is.set_option(urdl::http::request_content("{\"username\":\"user@name.co\", \"password\":\"test\"}"));


namespace Binance::Http
{
class Client : public util::Http::Client
{
public:
    Client() = default;
    explicit Client(std::string & apiKey, std::string & secretKey, std::string & host)
        : apiKey_(apiKey)
        , secretKey_(secretKey)
        , util::Http::Client(host)
    {
    }


protected:
private:
    std::string apiKey_;
    std::string secretKey_;
};

class UsdmClient : public Client
{
public:
    UsdmClient(std::string & apiKey, std::string & secretKey, std::string & host)
        : Client(apiKey, secretKey, host)
    {
    }

    Binance::PM::NewUMOrderResponse newOrder(Binance::PM::NewUMOrderRequest & request) { }
    Binance::PM::NewUMConditionalOrderResponse newConditionalOrder(Binance::PM::NewUMConditionalOrderRequest & request) { }
    Binance::PM::ModifyUMOrderResponse modifyOrder(Binance::PM::ModifyUMOrderRequest & request) { }
    Binance::PM::CancelUMOrderResponse cancelOrder(Binance::PM::CancelUMOrderRequest & request) { }
    Binance::PM::QueryUMOrderResponse queryOrder(Binance::PM::QueryUMOrderRequest & request) { }
};

class CoinmClient : public Client
{
};
}