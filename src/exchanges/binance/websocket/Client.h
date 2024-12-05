#pragma once
#include <util/WebsocketClient.h>
namespace Binance::Websocket {
    class Client: public util::Websocket::Client {
    public:
       Client() {
           host = "stream.binance.com";
           path = "/stream?streams=";
       }
    };
}
