#include <exchanges/binance/model/AggregateTradeEvent.h>
#include <rapidjson/document.h>
#include <util/jsonBase.h>
#include <gtest/gtest.h>
TEST(AggregateTradeEventTest, test_deserialize) {
    Binance::AggregateTradeEvent event;
    const char* json = R"({"e":"aggTrade","E":1733410207629,"s":"BTCUSDT","a":3302378726,"p":"103300.00000000","q":"0.00266000","f":4209134914,"l":4209134914,"T":1733410207628,"m":true,"M":true})";
    rapidjson::Document d;
    d.Parse(json);
    auto flag = event.deserialize(d);
    EXPECT_EQ(flag, true);
    EXPECT_EQ(event.eventType, "aggTrade");
    EXPECT_EQ(event.eventTime, 1733410207629);
    EXPECT_EQ(event.symbol, "BTCUSDT");
    EXPECT_EQ(event.aggTradeID, 3302378726);
    EXPECT_EQ(event.price, 103300.00000000);
    EXPECT_EQ(event.quantity, "0.00266000");
    EXPECT_EQ(event.firstTradeID, 4209134914);
    EXPECT_EQ(event.lastTradeID, 4209134914);
    EXPECT_EQ(event.tradeTime, 1733410207628);
    EXPECT_EQ(event.isMarketMaker, true);
}