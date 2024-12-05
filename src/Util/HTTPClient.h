#pragma once
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include "rapidjson/document.h"
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio.hpp>
#include <util/HTTPSession.h>


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = net::ssl;
using tcp = net::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

//-------------------------------------------------------------------------------------
namespace util::Http {
    class Client {
    public:
        template<class T>
        T get(const std::string& path, const std::string& body) {
            net::io_context ioc;
            ssl::context ctx{ssl::context::tlsv12_client};
            ctx.set_verify_mode(ssl::verify_peer);
            ctx.set_default_verify_paths();
            auto se = std::make_shared<session>(net::make_strand(ioc), ctx, host, headers);
            se->run(path, http::verb::get, body);
            ioc.run();

            rapidjson::Document document;
            document.Parse(se->res.body().c_str());
            T t;
            t.deserialize(document);
            return t;
        }

        template<class T>
        T post(const std::string& path, const std::string& body) {
            net::io_context ioc;

            ssl::context ctx{ssl::context::tlsv12_client};
            ctx.set_verify_mode(ssl::verify_peer);
            auto se = std::make_shared<session>(net::make_strand(ioc), ctx, host, headers);
            se->run(path, http::verb::post, body);
            ioc.run();

            rapidjson::Document document;
            document.Parse(se->res.body().c_str());
            T t;
            t.deserialize(document);
            return t;
        }

        template<class T>
        T put(const std::string& path, const std::string& body) {
            net::io_context ioc;
            ssl::context ctx{ssl::context::tlsv12_client};
            ctx.set_verify_mode(ssl::verify_peer);
            auto se = std::make_shared<session>(net::make_strand(ioc), ctx, host, headers);
            se->run(path, http::verb::put, body);
            ioc.run();

            rapidjson::Document document;
            document.Parse(se->res.body().c_str());
            T t;
            t.deserialize(document);
            return t;
        }

    protected:
        std::string host;
        std::unordered_map<std::string, std::string> headers;
    };
}