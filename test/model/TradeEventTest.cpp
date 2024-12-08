#include <exchanges/binance/model/Trade.hpp>
#include <rapidjson/document.h>
#include <gtest/gtest.h>

TEST(tradeEvent, testDeserialize) {
    Binance::TradeEvent event;
    const char* json = R"({"stream":"btcusdt@trade","data":{"e":"trade","E":1733498426037,"s":"BTCUSDT","t":4219164344,"p":"98910.32000000","q":"0.05539000","T":1733498426037,"m":true,"M":true}})";
    rapidjson::Document d;
    d.Parse(json);
    auto flag = event.deserialize(d);
    EXPECT_EQ(flag, true);
    EXPECT_EQ(event.eventType, "trade");
    EXPECT_EQ(event.eventTime, 1733498426037);
    EXPECT_EQ(event.symbol, "BTCUSDT");
    EXPECT_EQ(event.tradeID, 4219164344);
    EXPECT_EQ(event.price, "98910.32000000");
    EXPECT_EQ(event.quantity, "0.05539000");
    EXPECT_EQ(event.tradeTime, 1733498426037);
    EXPECT_EQ(event.isMarketMaker, true);
}
