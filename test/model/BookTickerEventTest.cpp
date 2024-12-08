#include <exchanges/binance/model/BookTicker.hpp>
#include <rapidjson/document.h>
#include <gtest/gtest.h>

TEST(bookTickerEvent, testDeserialize) {
    Binance::BookTickerEvent event;
    const char* json = R"({"stream":"btcusdt@bookTicker","data":{"u":56052199039,"s":"BTCUSDT","b":"99566.42000000","B":"3.12604000","a":"99566.43000000","A":"2.90961000"}})";
    rapidjson::Document d;
    d.Parse(json);
    auto flag = event.deserialize(d);
    EXPECT_EQ(flag, true);
    EXPECT_EQ(event.stream, "btcusdt@bookTicker");
    EXPECT_EQ(event.updateID, 56052199039);
    EXPECT_EQ(event.symbol, "BTCUSDT");
    EXPECT_EQ(event.bestBidPrice, "99566.42000000");
    EXPECT_EQ(event.bestBidQuantity, "3.12604000");
    EXPECT_EQ(event.bestAskPrice, "99566.43000000");
    EXPECT_EQ(event.bestAskQuantity, "2.90961000");
}
