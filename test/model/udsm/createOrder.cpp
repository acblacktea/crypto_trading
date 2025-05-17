#include <exchanges/binance/model/USDM/NewOrder.hpp>
#include <gtest/gtest.h>
#include <rapidjson/document.h>

TEST(createUSDMOrder, testDeserialize)
{
    const char * json = R"({
    "method": "order.place",
    "params": {
        "apiKey": "HMOchcfii9ZRZnhjp2XjGXhsOBd6msAhKz9joQaWwZ7arcJTlD2hGPHQj1lGdTjR",
        "positionSide": "BOTH",
        "price": "43187.00",
        "quantity": 0.1,
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
}
