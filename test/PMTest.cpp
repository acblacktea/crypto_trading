#include <atomic>
#include <random>
#include <vector>
#include <unistd.h>
#include <exchanges/binance/http/Client.hpp>
#include <gtest/gtest.h>
#include <model/binance/Util.hpp>

// set here
static std::string apiKey = "";
static std::string secretKey = "";

// 685989929304
/*
{"status":200,"result":{"orderId":685989929304,"symbol":"BTCUSDT","status":"NEW","clientOrderId":"93Mbegwes6NHYIiwcodq68","price":"50000.00","avgPrice":"0.00","origQty":"0.002","executedQty":"0.000","cumQty":"0.000","cumQuote":"0.00000","timeInForce":"GTC","type":"LIMIT","reduceOnly":false,"closePosition":false,"side":"BUY","positionSide":"BOTH","stopPrice":"0.00","workingType":"CONTRACT_PRICE","priceProtect":false,"origType":"LIMIT","priceMatch":"NONE","selfTradePreventionMode":"EXPIRE_MAKER","goodTillDate":0,"updateTime":1747568334548}}
*/
TEST(PMTest, newOrder)
{
    Binance::PM::Client client(apiKey, secretKey);
    Binance::PM::NewUMOrderRequest newOrderRequest;
    newOrderRequest.symbol = "BTCUSDT";
    newOrderRequest.side = Binance::BUYSIDE;
    newOrderRequest.price = "50000.00";
    newOrderRequest.type = Binance::LIMITTYPE;
    newOrderRequest.quantity = "0.002";
    newOrderRequest.timeInForce = "GTC";
    auto [response, errorMessage] = client.newUMOrder(newOrderRequest);
    std::cout << response.toJson() << std::endl;
    std::cout << errorMessage << std::endl;
}

TEST(PMTest, queryOrder)
{
    Binance::PM::Client client(apiKey, secretKey);
    Binance::PM::QueryUMOrderRequest queryOrderRequest;
    queryOrderRequest.orderId = 687839097451;
    queryOrderRequest.symbol = "BTCUSDT";
    auto [response, errorMessage] = client.queryUMOrder(queryOrderRequest);
    std::cout << response.toJson() << std::endl;
    std::cout << errorMessage << std::endl;
}


TEST(PMTest, modifyOrder)
{
    Binance::PM::Client client(apiKey, secretKey);
    Binance::PM::ModifyUMOrderRequest modifyOrderRequest;
    modifyOrderRequest.orderId = 687839097451;
    modifyOrderRequest.symbol = "BTCUSDT";
    modifyOrderRequest.price = "53212";
    modifyOrderRequest.quantity = "0.003";
    modifyOrderRequest.side = Binance::BUYSIDE;
    auto [response, errorMessage] = client.modifyUMOrder(modifyOrderRequest);
    std::cout << response.toJson() << std::endl;
    std::cout << errorMessage << std::endl;
}

TEST(PMTest, cancelOrder)
{
    Binance::PM::Client client(apiKey, secretKey);
    Binance::PM::CancelUMOrderRequest cancelOrderRequest;
    cancelOrderRequest.orderId = 687839097451;
    cancelOrderRequest.symbol = "BTCUSDT";
    auto [response, errorMessage] = client.cancelUMOrder(cancelOrderRequest);
    std::cout << response.toJson() << std::endl;
    std::cout << errorMessage << std::endl;
}