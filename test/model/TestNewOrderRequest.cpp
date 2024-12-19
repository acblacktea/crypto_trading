#include <exchanges/binance/model/TestNewOrderRequest.h>
#include <rapidjson/document.h>
#include <gtest/gtest.h>

TEST(TestNewOrderRequest, testSerialize) {
    Binance::TestNewOrderRequest request;
    request.symbol = "a";
    request.side = "b";
    request.type = "c";
    request.timeInForce = "d";
    request.quantity = "e";
    request.price = "f";
    request.quoteOrderQty = "g";
    request.stopPrice = "h";
    request.computeCommissionRates = true;


    auto jsonStr = request.serialize();
    EXPECT_EQ(jsonStr,  R"({"symbol":"a","side":"b","type":"c","timeInForce":"d","quantity":"e","price":"f","quoteOrderQty":"g","stopPrice":"h","computeCommissionRates":true})");
    std::cout << jsonStr << std::endl;
}

TEST(TestNewOrderRequest, testSendTestNewOrderRequest) {
    Binance::TestNewOrderRequest request;
    request.symbol = "a";
    request.side = "b";
    request.type = "c";
    request.timeInForce = "d";
    request.quantity = "e";
    request.price = "f";
    request.quoteOrderQty = "g";
    request.stopPrice = "h";
    request.computeCommissionRates = true;


    auto jsonStr = request.serialize();
    EXPECT_EQ(jsonStr,  R"({"symbol":"a","side":"b","type":"c","timeInForce":"d","quantity":"e","price":"f","quoteOrderQty":"g","stopPrice":"h","computeCommissionRates":true})");
    std::cout << jsonStr << std::endl;
}




TEST(TestNewOrderRequest, testDeserialize) {
    Binance::TestNewOrderRequest request;
    request.symbol = "a";
    request.side = "b";
    request.type = "c";
    request.timeInForce = "d";
    request.quantity = "e";
    request.price = "f";
    request.quoteOrderQty = "g";
    request.stopPrice = "h";
    request.computeCommissionRates = true;


    auto jsonStr = request.serialize();
    EXPECT_EQ(jsonStr,  R"({"symbol":"a","side":"b","type":"c","timeInForce":"d","quantity":"e","price":"f","quoteOrderQty":"g","stopPrice":"h","computeCommissionRates":true})");
    std::cout << jsonStr << std::endl;
}
