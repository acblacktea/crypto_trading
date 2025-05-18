#pragma once
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <boost/asio.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <rapidjson/document.h>
#include <util/WebsocketSession.h>


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
    void subscrible(const std::vector<std::string> & events, rawDataCallBackFunc f)
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

class OrderClient
{
public:
    OrderClient(const std::string && host, const std::string && path, const std::string && port)
        : ctx_(ssl::context::tlsv12_client)
        , resolver_(ioc_)
        , ws_(ioc_, ctx_)

    {
        SSL_set_tlsext_host_name(ws_.next_layer().native_handle(), host.c_str());
        auto const results = resolver_.resolve(host, port);
        net::connect(ws_.next_layer().next_layer(), results.begin(), results.end());

        // 3. SSL Handshake
        ws_.next_layer().handshake(ssl::stream_base::client);


        ws_.handshake(host, path);
    }

    std::string sendOrder(const std::string & message)
    {
        std::cout << message << std::endl;
        // Send message
        ws_.write(net::buffer(message));

        // Read response
        beast::flat_buffer buffer;
        ws_.read(buffer);
        std::cout << beast::buffers_to_string(buffer.data()) << std::endl;
        return beast::buffers_to_string(buffer.data());
    }

    net::io_context ioc_;
    tcp::resolver resolver_;
    ssl::context ctx_;
    websocket::stream<beast::ssl_stream<tcp::socket>> ws_;
};
}
