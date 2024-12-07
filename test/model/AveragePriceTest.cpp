#include <exchanges/binance/model/AveragePrice.h>
#include <rapidjson/document.h>
#include <gtest/gtest.h>

TEST(AveragePriceEvent, testDeserialize) {
    Binance::AveragePriceEvent event;
    const char* json = R"({"stream":"btcusdt@avgPrice","data":{"e":"avgPrice","E":1733575508811,"s":"BTCUSDT","i":"5m","w":"99532.35935504","T":1733575508811}})";
    rapidjson::Document d;
    d.Parse(json);
    auto flag = event.deserialize(d);
    EXPECT_EQ(flag, true);
    EXPECT_EQ(event.stream, "btcusdt@avgPrice");
    EXPECT_EQ(event.eventType, "avgPrice");
    EXPECT_EQ(event.eventTime, 1733575508811);
    EXPECT_EQ(event.symbol, "BTCUSDT");
    EXPECT_EQ(event.interval, "5m");
    EXPECT_EQ(event.averagePrice, "99532.35935504");
    EXPECT_EQ(event.lastTradeTime, 1733575508811);
}
