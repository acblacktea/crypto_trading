#include <iostream>
#include <exchanges/binance/websocket/Client.h>
#include <exchanges/binance/model/AggregateTradeEvent.h>
#include <exchanges/binance/http/Client.h>
#include <rapidjson/document.h>

int main() {
    Binance::Websocket::Client client;
    Binance::Http::Client httpClient;



    client.subscrible({"btcusdt@aggTrade"}, [](rapidjson::Document &d) {
        //std::cout << d["data"]["bids"][0][0].GetString() << std::endl;
    });

    client.listen();

    /*
    client.subscrible({"btcusdt@bookTicker"}, [](Rapidjson::Document &d) {
        //std::cout << d["data"]["u"].GetInt64() << std::endl;
    });
    */


    /*
    client.subscrible({"btcusdt@aggTrade"}, [](Rapidjson::Document &d) {
        binance::aggregateTradeEventTest event;
        event.Deserialize(d["data"]);
        std::cout << event.tradeTime << std::endl;
        std::cout << event.lastTradeID << std::endl;
        std::cout << event.firstTradeID << std::endl;
        std::cout << event.quantity << std::endl;
        std::cout << event.symbol << std::endl;
        std::cout << event.eventTime << std::endl;
        std::cout << event.eventType << std::endl;
        std::cout << event.price << std::endl;
        std::cout << event.aggTradeID << std::endl;
        std::cout << event.isMarketMaker << std::endl;

        //std::cout << d["data"]["u"].GetInt64() << std::endl;
    });

    client.listen();
    */


    /*
    for (auto i = 0; i < 1; ++i) {
        //httpClient.get("asdsad", "");
        auto orderBook = httpClient.getOrderBook("BNBBTC");
        std::cout << orderBook.lastUpdateId << std::endl;
        std::cout << orderBook.asks.size() << std::endl;
        for (auto& ve: orderBook.asks) {
            std::cout << ve[0] << " " << ve[1] << std::endl;
        }

        std::cout << orderBook.bids.size() << std::endl;
        for (auto& ve: orderBook.bids) {
            std::cout << ve[0] << " " << ve[1] << std::endl;
        }
    }
     */

    return 0;
}