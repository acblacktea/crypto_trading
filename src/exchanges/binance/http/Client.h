#pragma once
#include <util/HTTPClient.h>
#include <exchanges/binance/model/PartialBookDepth.h>
//-------------------------------------------------------------------------------------
namespace Binance::Http {
    class Client : public util::Http::Client {
    public:
        Client() {
            host = "api.binance.com";
            headers = {
                    {"User-Agent",   "Mozilla/4.0 (compatible; Node binance API)"},
                    {"Accept",       "application/json"},
                    {"Content-Type", "application/x-www-form-urlencoded"}
            };
        }

        /*
        OrderBook getOrderBook(const std::string& symbol) {
             auto path = "/api/v3/depth?symbol=" + symbol;
             auto orderBook = get<OrderBook>(path, "{}");
             return orderBook;
        }
        */

    };
}