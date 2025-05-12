#include <exchanges/binance/model/BookTicker.h>
#include <gtest/gtest.h>
#include <rapidjson/document.h>

TEST(bookTickerEvent, testDeserialize)
{
    const char * json
        = R"({"stream":"btcusdt@bookTicker","data":{"u":56052199039,"s":"BTCUSDT","b":"99566.42000000","B":"3.12604000","a":"99566.43000000","A":"2.90961000"}})";
    rapidjson::Document d;
    d.Parse(json);
    auto event = Binance::BookTickerEvent::fromJson(d);

    EXPECT_EQ(event.stream, "btcusdt@bookTicker");
    EXPECT_EQ(event.data.updateTime, 56052199039);
    EXPECT_EQ(event.data.symbol, "BTCUSDT");
    EXPECT_EQ(event.data.bestBidPrice, "99566.42000000");
    EXPECT_EQ(event.data.bestBidQuantity, "3.12604000");
    EXPECT_EQ(event.data.bestAskPrice, "99566.43000000");
    EXPECT_EQ(event.data.bestAskQuantity, "2.90961000");
}
