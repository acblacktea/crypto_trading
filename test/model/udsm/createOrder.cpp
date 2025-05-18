#include <iostream>
#include <gtest/gtest.h>
#include <model/binance/USDM/NewOrder.hpp>
#include <rapidjson/document.h>

TEST(createUSDMOrder, testJson)
{
    const char * json = R"({
    "method": "order.place",
    "params": {
        "apiKey": "HMOchcfii9ZRZnhjp2XjGXhsOBd6msAhKz9joQaWwZ7arcJTlD2hGPHQj1lGdTjR",
        "positionSide": "BOTH",
        "price": "43187.00",
        "quantity": "0.1",
        "side": "BUY",
        "symbol": "BTCUSDT",
        "timeInForce": "GTC",
        "timestamp": 1702555533821,
        "type": "LIMIT",
        "signature": "0f04368b2d22aafd0ggc8809ea34297eff602272917b5f01267db4efbc1c9422"
    }})";

    rapidjson::Document d;
    d.Parse(json);
    auto event = Binance::USDM::NewOrderRequest::fromJson(d);
    EXPECT_EQ(event.method, "order.place");
    EXPECT_EQ(event.params.apiKey, "HMOchcfii9ZRZnhjp2XjGXhsOBd6msAhKz9joQaWwZ7arcJTlD2hGPHQj1lGdTjR");
    EXPECT_EQ(event.params.positionSide, "BOTH");
    EXPECT_EQ(event.params.price, "43187.00");
    EXPECT_EQ(event.params.quantity, "0.1");
    EXPECT_EQ(event.params.side, "BUY");
    EXPECT_EQ(event.params.symbol, "BTCUSDT");
    EXPECT_EQ(event.params.timeInForce, "GTC");
    EXPECT_EQ(event.params.timestamp, 1702555533821);
    EXPECT_EQ(event.params.type, "LIMIT");
    EXPECT_EQ(event.params.signature, "0f04368b2d22aafd0ggc8809ea34297eff602272917b5f01267db4efbc1c9422");

    auto str = event.toJson();
    EXPECT_EQ(
        str,
        R"({"method":"order.place","params":{"apiKey":"HMOchcfii9ZRZnhjp2XjGXhsOBd6msAhKz9joQaWwZ7arcJTlD2hGPHQj1lGdTjR","signature":"0f04368b2d22aafd0ggc8809ea34297eff602272917b5f01267db4efbc1c9422","symbol":"BTCUSDT","side":"BUY","type":"LIMIT","timestamp":1702555533821,"positionSide":"BOTH","timeInForce":"GTC","quantity":"0.1","price":"43187.00"}})");
}
