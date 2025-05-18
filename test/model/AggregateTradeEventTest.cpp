#include <gtest/gtest.h>
#include <model/binance/AggregateTrade.h>
#include <rapidjson/document.h>

TEST(aggregateTradeEvent, testDeserialize)
{
    Binance::AggregateTradeEvent event;
    const char * json
        = R"({"stream":"btcusdt@aggTrade","data":{"e":"aggTrade","E":1733464456075,"s":"BTCUSDT","a":3305280883,"p":"97900.88000000","q":"0.00208000","f":4216590360,"l":4216590360,"T":1733464456074,"m":true,"M":true}})";
    rapidjson::Document d;
    d.Parse(json);
    auto flag = event.deserialize(d);
    EXPECT_EQ(flag, true);
    EXPECT_EQ(event.stream, "btcusdt@aggTrade");
    EXPECT_EQ(event.eventType, "aggTrade");
    EXPECT_EQ(event.eventTime, 1733464456075);
    EXPECT_EQ(event.symbol, "BTCUSDT");
    EXPECT_EQ(event.aggTradeID, 3305280883);
    EXPECT_EQ(event.price, "97900.88000000");
    EXPECT_EQ(event.quantity, "0.00208000");
    EXPECT_EQ(event.firstTradeID, 4216590360);
    EXPECT_EQ(event.lastTradeID, 4216590360);
    EXPECT_EQ(event.tradeTime, 1733464456074);
    EXPECT_EQ(event.isMarketMaker, true);
}
