#include <atomic>
#include <random>
#include <vector>
#include <unistd.h>
#include <exchanges/binance/websocket/Client.hpp>
#include <gtest/gtest.h>
#include <model/binance/Util.hpp>
static std::string apiKey = "&&&";
static std::string secretKey = "***";

// 685989929304
/*
{"status":200,"result":{"orderId":685989929304,"symbol":"BTCUSDT","status":"NEW","clientOrderId":"93Mbegwes6NHYIiwcodq68","price":"50000.00","avgPrice":"0.00","origQty":"0.002","executedQty":"0.000","cumQty":"0.000","cumQuote":"0.00000","timeInForce":"GTC","type":"LIMIT","reduceOnly":false,"closePosition":false,"side":"BUY","positionSide":"BOTH","stopPrice":"0.00","workingType":"CONTRACT_PRICE","priceProtect":false,"origType":"LIMIT","priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0,"updateTime":1747568334548}}
*/
TEST(USDMTest, newOrder)
{
    Binance::USDM::OrderClient client(apiKey, secretKey);
    Binance::USDM::NewOrderRequest newOrderRequest;
    newOrderRequest.params.symbol = "BTCUSDT";
    newOrderRequest.params.side = Binance::BUYSIDE;
    newOrderRequest.params.price = "50000.00";
    newOrderRequest.params.type = Binance::LIMITTYPE;
    newOrderRequest.params.quantity = "0.002";
    newOrderRequest.params.timeInForce = "GTC";
    auto newOrderResponse = client.newOrder(newOrderRequest);
    std::cout << newOrderResponse.toJson() << std::endl;
}

TEST(USDMTest, queryOrder)
{
    Binance::USDM::OrderClient client(apiKey, secretKey);
    Binance::USDM::QueryOrderRequest queryOrderRequest;
    queryOrderRequest.params.apiKey = apiKey;
    queryOrderRequest.params.orderId = 685989929304;
    queryOrderRequest.params.symbol = "BTCUSDT";
    auto response = client.queryOrder(queryOrderRequest);
    std::cout << response.toJson() << std::endl;
}


TEST(USDMTest, modifyOrder)
{
    Binance::USDM::OrderClient client(apiKey, secretKey);
    Binance::USDM::ModifyOrderRequest modifyOrderRequest;
    modifyOrderRequest.params.orderId = 685989929304;
    modifyOrderRequest.params.symbol = "BTCUSDT";
    modifyOrderRequest.params.price = "50002";
    modifyOrderRequest.params.quantity = "0.003";
    modifyOrderRequest.params.side = Binance::BUYSIDE;
    auto response = client.modifyOrder(modifyOrderRequest);
    std::cout << response.toJson() << std::endl;
}

TEST(USDMTest, cancelOrder)
{
    Binance::USDM::OrderClient client(apiKey, secretKey);
    Binance::USDM::CancelOrderRequest cancelOrderRequest;
    cancelOrderRequest.params.orderId = 685989929304;
    cancelOrderRequest.params.symbol = "BTCUSDT";
    auto response = client.cancelOrder(cancelOrderRequest);
    std::cout << response.toJson() << std::endl;
}