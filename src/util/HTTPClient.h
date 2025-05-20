#pragma once
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <ranges>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <rapidjson/document.h>
#include <util/HTTPSession.h>


namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http; // from <boost/beast/http.hpp>
namespace net = boost::asio; // from <boost/asio.hpp>
namespace ssl = net::ssl;
using tcp = net::ip::tcp; // from <boost/asio/ip/tcp.hpp>

//-------------------------------------------------------------------------------------
namespace util::Http
{
template <class T>
concept hasFromJson = requires(const rapidjson::Value & jsonObj) {
    { T::fromJson(jsonObj) } -> std::same_as<T>;
};

class Client
{
public:
    Client(std::string & host)
        : host_(host)
    {
    }

    template <class T>
    requires hasFromJson<T>
    T get(const std::string & path, std::string & params, const std::string & body, std::unordered_map<std::string, std::string> & headers)
    {
        net::io_context ioc;
        ssl::context ctx{ssl::context::tlsv12_client};
        ctx.set_verify_mode(ssl::verify_peer);
        ctx.set_default_verify_paths();
        auto se = std::make_shared<session>(net::make_strand(ioc), ctx, host, headers);
        se->run(path + "?" + params, http::verb::get, body);
        ioc.run();

        rapidjson::Document document;
        document.Parse(se->res.body().c_str());
        return T::from(json);
    }

    template <class T>
    requires hasFromJson<T>
    T post(const std::string & path, std::string & params, const std::string & body, std::unordered_map<std::string, std::string> & headers)
    {
        net::io_context ioc;

        ssl::context ctx{ssl::context::tlsv12_client};
        ctx.set_verify_mode(ssl::verify_peer);
        auto se = std::make_shared<session>(net::make_strand(ioc), ctx, host_, headers);
        se->run(path + "?" + params, http::verb::post, body);
        ioc.run();

        rapidjson::Document document;
        document.Parse(se->res.body().c_str());
        return T::from(json);
    }

    template <class T>
    requires hasFromJson<T>
    T put(const std::string & path, std::string & params, const std::string & body, std::unordered_map<std::string, std::string> & headers)
    {
        net::io_context ioc;
        ssl::context ctx{ssl::context::tlsv12_client};
        ctx.set_verify_mode(ssl::verify_peer);
        auto se = std::make_shared<session>(net::make_strand(ioc), ctx, host_, headers);
        se->run(path + "?" + params, http::verb::put, body);
        ioc.run();

        rapidjson::Document document;
        document.Parse(se->res.body().c_str());
        return T::from(json);
    }

    template <class T>
    requires hasFromJson<T>
    T delete_(
        const std::string & path, std::string & params, const std::string & body, std::unordered_map<std::string, std::string> & headers)
    {
        net::io_context ioc;
        ssl::context ctx{ssl::context::tlsv12_client};
        ctx.set_verify_mode(ssl::verify_peer);
        auto se = std::make_shared<session>(net::make_strand(ioc), ctx, host_, headers);
        se->run(path + "?" + params, http::verb::delete_, body);
        ioc.run();

        rapidjson::Document document;
        document.Parse(se->res.body().c_str());
        return T::from(json);
    }

protected:
    std::string host_;
};
}