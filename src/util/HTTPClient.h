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
#include <tuple>
#include <vector>
#include <ranges>


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = net::ssl;
using tcp = net::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

//-------------------------------------------------------------------------------------
namespace util::Http {
    using params = std::unordered_map<std::string, std::string>;
    std::string flattenParams(const params& params) {
        std::string ans;
        bool isFirstPair = true;
        for (auto& pair : params) {
            if (!isFirstPair) {
                ans += "&";
            }

            isFirstPair = false;
            ans += pair.first + "=" + pair.second;
        }

        return ans;
    }

    class Client {
    public:
        template<class T>
        std::tuple<T, beast::error_code> get(const std::string& path, std::string &params, const std::string& body) {
            net::io_context ioc;
            ssl::context ctx{ssl::context::tlsv12_client};
            ctx.set_verify_mode(ssl::verify_peer);
            ctx.set_default_verify_paths();
            auto se = std::make_shared<session>(net::make_strand(ioc), ctx, host, headers);
            se->run(path + "?" + params, http::verb::get, body);
            ioc.run();

            rapidjson::Document document;
            document.Parse(se->res.body().c_str());
            T t;
            t.deserialize(document);
            return {t, se->errorCode};
        }

        template<class T>
        std::tuple<T, beast::error_code> post(const std::string& path, std::string &params, const std::string& body) {
            net::io_context ioc;

            ssl::context ctx{ssl::context::tlsv12_client};
            ctx.set_verify_mode(ssl::verify_peer);
            auto se = std::make_shared<session>(net::make_strand(ioc), ctx, host, headers);
            se->run(path + "?" + params, http::verb::post, body);
            ioc.run();

            rapidjson::Document document;
            document.Parse(se->res.body().c_str());
            T t;
            t.deserialize(document);
            return {t, se->errorCode};
        }

        template<class T>
        std::tuple<T, beast::error_code> put(const std::string& path, std::string &params, const std::string& body) {
            net::io_context ioc;
            ssl::context ctx{ssl::context::tlsv12_client};
            ctx.set_verify_mode(ssl::verify_peer);
            auto se = std::make_shared<session>(net::make_strand(ioc), ctx, host, headers);
            se->run(path + "?" + params, http::verb::put, body);
            ioc.run();

            rapidjson::Document document;
            document.Parse(se->res.body().c_str());
            T t;
            t.deserialize(document);
            return {t, se->errorCode};
        }

        template<class T>
        std::tuple<T, beast::error_code> delete_(const std::string& path, std::string &params, const std::string& body) {
            net::io_context ioc;
            ssl::context ctx{ssl::context::tlsv12_client};
            ctx.set_verify_mode(ssl::verify_peer);
            auto se = std::make_shared<session>(net::make_strand(ioc), ctx, host, headers);
            se->run(path + "?" + params, http::verb::delete_, body);
            ioc.run();

            rapidjson::Document document;
            document.Parse(se->res.body().c_str());
            T t;
            t.deserialize(document);
            return {t, se->errorCode};
        }

    protected:
        std::string host;
        std::unordered_map<std::string, std::string> headers;
    };
}