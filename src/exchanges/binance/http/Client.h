#pragma once
#include <util/HTTPClient.h>

#include <utility>

//-------------------------------------------------------------------------------------
//is.set_option(urdl::http::request_content_type("application/json"));
//is.set_option(urdl::http::request_content("{\"username\":\"user@name.co\", \"password\":\"test\"}"));


namespace Binance::Http
{
class Client : public util::Http::Client
{
public:
    Client() = default;
    explicit Client(std::string _apiKey)
        : apiKey(std::move(_apiKey))
    {
        host = "api.binance.com";
        headers
            = {{"User-Agent", "Mozilla/4.0 (compatible; Node binance API)"},
               {"Accept", "application/json"},
               {"Content-Type", "application/x-www-form-urlencoded"},
               {"X-MBX-APIKEY", this->apiKey}};
    }

private:
    std::string apiKey;
    std::string secretKey;
};
}