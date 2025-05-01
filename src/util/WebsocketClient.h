#pragma once
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <util/WebsocketSession.h>
#include <rapidjson/document.h>


namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http; // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio; // from <boost/asio.hpp>
namespace ssl = net::ssl;
using tcp = net::ip::tcp; // from <boost/asio/ip/tcp.hpp>

//-------------------------------------------------------------------------------------
namespace util::Websocket
{
class Client
{
public:
    void subscrible(const std::vector<std::string> & events, callBackFunc f)
    {
        auto pathWithEvents = path;
        for (int i = 0; i < events.size(); ++i)
        {
            pathWithEvents += events[i];
            if (i != static_cast<int>(events.size()) - 1)
            {
                pathWithEvents += "/";
            }
        }

        ssl::context ctx{ssl::context::tlsv12_client};
        ctx.set_verify_mode(ssl::verify_peer);
        ctx.set_default_verify_paths();
        std::make_shared<Session>(ioc, ctx, host)->run(pathWithEvents, f);
    }

    void listen() { ioc.run(); }


protected:
    net::io_context ioc;
    std::string path; // "/stream?streams=";
    std::string host;
};
}
