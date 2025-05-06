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
#include <rapidjson/document.h>

namespace util::Websocket
{
namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http; // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio; // from <boost/asio.hpp>
namespace ssl = net::ssl;
using tcp = net::ip::tcp; // from <boost/asio/ip/tcp.hpp>
using callBackFunc = std::function<void(rapidjson::Document &)>;
using rawDataCallBackFunc = std::function<void(std::string &)>;

void fail(beast::error_code ec, char const * what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

class Session : public std::enable_shared_from_this<Session>
{
public:
    explicit Session(net::io_context & ioc, ssl::context & ctx, std::string host)
        : resolver_(net::make_strand(ioc))
        , ws(net::make_strand(ioc), ctx)
        , host(std::move(host))
    {
    }

    void run(std::string p, rawDataCallBackFunc f)
    {
        this->path = std::move(p);
        this->rawDataFunc = f;
        resolver_.async_resolve(host, port, beast::bind_front_handler(&Session::onResolve, shared_from_this()));
    }

    void onResolve(beast::error_code ec, const tcp::resolver::results_type & results)
    {
        if (ec)
        {
            return fail(ec, "resolve");
        }

        if (!SSL_set_tlsext_host_name(ws.next_layer().native_handle(), host.c_str()))
        {
            throw beast::system_error{beast::error_code(::ERR_get_error(), net::error::get_ssl_category())};
        }

        //beast::get_lowest_layer(ws).expires_after(std::chrono::seconds(30));
        beast::get_lowest_layer(ws).async_connect(results, beast::bind_front_handler(&Session::onConnect, shared_from_this()));
    }

    void onConnect(beast::error_code ec, const tcp::resolver::results_type::endpoint_type & ep)
    {
        if (ec)
        {
            return fail(ec, "connect");
        }

        ws.next_layer().async_handshake(ssl::stream_base::client, beast::bind_front_handler(&Session::onSSLHandshake, shared_from_this()));
    }

    void onSSLHandshake(beast::error_code ec)
    {
        if (ec)
        {
            return fail(ec, "ssl_handshake");
        }

        beast::get_lowest_layer(ws).expires_never();
        ws.set_option(websocket::stream_base::timeout::suggested(beast::role_type::client));
        ws.set_option(
            websocket::stream_base::decorator(
                [](websocket::request_type & req)
                { req.set(http::field::user_agent, std::string(BOOST_BEAST_VERSION_STRING) + " websocket-client-async"); }));

        ws.async_handshake(host + ":" + port, path, beast::bind_front_handler(&Session::onHandshake, shared_from_this()));
    }

    void onHandshake(beast::error_code ec)
    {
        if (ec)
        {
            return fail(ec, "handshake");
        }

        ws.async_read(buffer_, beast::bind_front_handler(&Session::onRead, shared_from_this()));
    }

    void onRead(beast::error_code ec, std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);

        if (ec)
        {
            return fail(ec, "read");
        }


        auto dataStr = boost::beast::buffers_to_string(buffer_.data());
        rawDataFunc(dataStr);

        /*
        rapidjson::Document document;
        document.Parse(dataStr.c_str());
        func(document);
        */

        buffer_.consume(buffer_.size());
        ws.async_read(buffer_, beast::bind_front_handler(&Session::onRead, shared_from_this()));
    }

private:
    tcp::resolver resolver_;
    websocket::stream<beast::ssl_stream<beast::tcp_stream>> ws;
    beast::flat_buffer buffer_;
    std::string host; // = "stream.binance.com";
    std::string port = "443";
    std::string path;
    std::string text_;
    callBackFunc func;
    rawDataCallBackFunc rawDataFunc;
};
}