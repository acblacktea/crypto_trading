#pragma once
#include <util/WebsocketClient.h>
namespace Binance::Websocket
{
class SpotClient : public util::Websocket::Client
{
public:
    SpotClient()
    {
        host = "stream.binance.com";
        path = "/stream?streams=";
    }
};

class USDMClient : public util::Websocket::Client
{
public:
    USDMClient()
    {
        host = "fstream.binance.com";
        path = "/stream?streams=";
    }
};

class OrderUSDMClient : public util::Websocket::OrderClient
{
public:
    OrderUSDMClient(const std::string & host, const std::string & port)
        : OrderClient(host, port)
    {
    }


    std::string openOrder() { return ""; }

    std::string modifyOrder() { return ""; }

    std::string cancelOrder() { return ""; }
};

class COINMClient : public util::Websocket::Client
{
public:
    COINMClient()
    {
        host = "wss://ws-dapi.binance.com/ws-dapi/v1";
        path = "/stream?streams=";
    }
};
}