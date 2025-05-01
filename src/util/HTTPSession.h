#pragma once
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <boost/asio/strand.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>

namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http; // from <boost/beast/http.hpp>
namespace net = boost::asio; // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl; // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>

//------------------------------------------------------------------------------
namespace util::Http
{
// Report a failure
inline void fail(beast::error_code ec, char const * what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

// Performs an HTTP GET and prints the response
class session : public std::enable_shared_from_this<session>
{
public:
    explicit session(
        net::any_io_executor ex, ssl::context & ctx, std::string_view host, std::unordered_map<std::string, std::string> & headers)
        : host(host)
        , resolver(ex)
        , stream(ex, ctx)
        , headers(headers)
    {
    }

    // Start the asynchronous operation
    void run(std::string_view target, http::verb method, std::string_view body)
    {
        // Set up an HTTP GET request message
        req.version(version);
        req.method(method);
        req.target(target);
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        req.set(http::field::body, body);

        for (const auto & kv : headers)
        {
            req.set(kv.first, kv.second);
        }

        // Look up the domain name
        resolver.async_resolve(host, "443", beast::bind_front_handler(&session::onResolve, shared_from_this()));
    }

    void onResolve(beast::error_code ec, tcp::resolver::results_type results)
    {
        if (ec)
        {
            errorCode = ec;
            return fail(ec, "resolve");
        }

        // Set SNI Hostname (many hosts need this to handshake successfully)
        if (!SSL_set_tlsext_host_name(stream.native_handle(), host.data()))
        {
            beast::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};
            std::cerr << ec.message() << "\n";
            return;
        }


        // Set a timeout on the operation
        beast::get_lowest_layer(stream).expires_after(std::chrono::seconds(30));

        // Make the connection on the IP address we get from a lookup
        beast::get_lowest_layer(stream).async_connect(results, beast::bind_front_handler(&session::onConnect, shared_from_this()));
    }

    void onConnect(beast::error_code ec, tcp::resolver::results_type::endpoint_type)
    {
        if (ec)
        {
            errorCode = ec;
            return fail(ec, "connect");
        }

        // Perform the SSL handshake
        stream.async_handshake(ssl::stream_base::client, beast::bind_front_handler(&session::onHandshake, shared_from_this()));
    }

    void onHandshake(beast::error_code ec)
    {
        if (ec)
            errorCode = ec;
        return fail(ec, "handshake");

        // Set a timeout on the operation
        beast::get_lowest_layer(stream).expires_after(std::chrono::seconds(30));
        // Send the HTTP request to the remote host
        http::async_write(stream, req, beast::bind_front_handler(&session::onWrite, shared_from_this()));
    }

    void onWrite(beast::error_code ec, std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);

        if (ec)
        {
            errorCode = ec;
            return fail(ec, "write");
        }

        // Receive the HTTP response
        http::async_read(stream, buffer, res, beast::bind_front_handler(&session::onRead, shared_from_this()));
    }

    void onRead(beast::error_code ec, std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);

        if (ec)
        {
            errorCode = ec;
            return fail(ec, "read");
        }

        std::cout << res.body() << std::endl;
        beast::get_lowest_layer(stream).expires_after(std::chrono::seconds(30));
    }

    http::response<http::string_body> res;
    beast::error_code errorCode;

private:
    tcp::resolver resolver;
    beast::ssl_stream<beast::tcp_stream> stream;
    beast::flat_buffer buffer; // (Must persist between reads)
    http::request<http::empty_body> req;

    std::string_view host; // = "api.binance.com";
    std::unordered_map<std::string, std::string> headers;
    int version = 11;
};
}
