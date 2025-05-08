#include <exchanges/binance/model/KLine.hpp>
#include <gtest/gtest.h>
#include <rapidjson/document.h>


TEST(kLineEvent, testDeserialize)
{
    const char * json
        = R"({"stream":"btcusdt@kline_1s","data":{"e":"kline","E":1733561824006,"s":"BTCUSDT","k":{"t":1733561823000,"T":1733561823999,"s":"BTCUSDT","i":"1s","f":4222889129,"L":4222889132,"o":"99512.02000000","c":"99512.02000000","h":"99512.02000000","l":"99512.01000000","v":"0.00701000","n":4,"x":true,"q":"697.57925570","V":"0.00656000","Q":"652.79885120","B":"0"}}})";
    rapidjson::Document d;
    d.Parse(json);
    auto event = Binance::KLineEvent::fromJson(d);

    EXPECT_EQ(event.stream, "btcusdt@kline_1s");
    EXPECT_EQ(event.data.eventType, "kline");
    EXPECT_EQ(event.data.eventTime, 1733561824006);
    EXPECT_EQ(event.data.symbol, "BTCUSDT");
    EXPECT_EQ(event.data.kLine.startTime, 1733561823000);
    EXPECT_EQ(event.data.kLine.closeTime, 1733561823999);
    EXPECT_EQ(event.data.kLine.symbol, "BTCUSDT");
    EXPECT_EQ(event.data.kLine.interval, "1s");
    EXPECT_EQ(event.data.kLine.firstTradeID, 4222889129);
    EXPECT_EQ(event.data.kLine.lastTradeID, 4222889132);
    EXPECT_EQ(event.data.kLine.openPrice, "99512.02000000");
    EXPECT_EQ(event.data.kLine.closePrice, "99512.02000000");
    EXPECT_EQ(event.data.kLine.highPrice, "99512.02000000");
    EXPECT_EQ(event.data.kLine.lowPrice, "99512.01000000");
    EXPECT_EQ(event.data.kLine.baseAssetVolume, "0.00701000");
    EXPECT_EQ(event.data.kLine.numberTrades, 4);
    EXPECT_EQ(event.data.kLine.isKLineClosed, true);
    EXPECT_EQ(event.data.kLine.quoteAssetVolume, "697.57925570");
    EXPECT_EQ(event.data.kLine.takerBuyAssetVolume, "0.00656000");
    EXPECT_EQ(event.data.kLine.takerBuyQuoteVolume, "652.79885120");
}
