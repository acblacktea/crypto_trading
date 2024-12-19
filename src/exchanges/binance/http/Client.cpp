#include <exchanges/binance/http/Client.h>
#include <chrono>
namespace Binance::Http {
    std::tuple<NewOrderResponse, beast::error_code> Client::newOrder(const NewOrderRequest& req) {
        util::Http::params params;
        params["symbol"] = req.symbol;
        params["side"] = req.side;
        params["type"] = req.type;
        if (req.timeInForce.has_value()) {
            params["timeInForce"] = req.timeInForce.value();
        }

        if (req.quantity.has_value()) {
            params["quantity"] = req.quantity.value();
        }

        if (req.price.has_value()) {
            params["price"] = req.price.value();
        }

        if (req.quoteOrderQty.has_value()) {
            params["quoteOrderQty"] = req.quoteOrderQty.value();
        }

        if (req.stopPrice.has_value()) {
            params["stopPrice"] = req.stopPrice.value();
        }

        auto paramStr = util::Http::flattenParams(params);
        return post<NewOrderResponse>("/api/v3/order", paramStr, "");
    };

    std::tuple<TestNewOrderResponse, beast::error_code> Client::testNewOrder(const TestNewOrderRequest& req) {
        util::Http::params params;
        params["symbol"] = req.symbol;
        params["side"] = req.side;
        params["type"] = req.type;
        if (req.timeInForce.has_value()) {
            params["timeInForce"] = req.timeInForce.value();
        }

        if (req.quantity.has_value()) {
            params["quantity"] = req.quantity.value();
        }

        if (req.price.has_value()) {
            params["price"] = req.price.value();
        }

        if (req.quoteOrderQty.has_value()) {
            params["quoteOrderQty"] = req.quoteOrderQty.value();
        }

        if (req.stopPrice.has_value()) {
            params["stopPrice"] = req.stopPrice.value();
        }

        if (req.computeCommissionRates.has_value()) {
            params["computeCommissionRates"] = std::to_string(req.computeCommissionRates.value());
        }

        auto paramStr = util::Http::flattenParams(params);
        return post<TestNewOrderResponse>("/api/v3/order/test", paramStr, "");
    }

    std::tuple<CancelOrderResponse, beast::error_code> Client::cancelOrder(const CancelOrderRequest& req) {
        util::Http::params params;
        params["symbol"] = req.symbol;

        std::chrono::milliseconds ms = duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
        params["timestamp"] = std::to_string(ms.count());

        if (req.orderID.has_value()) {
            params["orderID"] =  std::to_string(req.orderID.value());
        }

        if (req.origClientOrderId.has_value()) {
            params["origClientOrderId"] = req.origClientOrderId.value();
        }

        if (req.recvWindow.has_value()) {
            params["recvWindow"] =  std::to_string(req.recvWindow.value());
        }

        auto paramStr = util::Http::flattenParams(params);
        return delete_<CancelOrderResponse>("/api/v3/order", paramStr, "");
    }

    std::tuple<QueryOrderResponse, beast::error_code> Client::queryOrder(const QueryOrderRequest& req) {
        util::Http::params params;
        params["symbol"] = req.symbol;

        std::chrono::milliseconds ms = duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
        params["timestamp"] = std::to_string(ms.count());

        if (req.orderID.has_value()) {
            params["orderID"] =  std::to_string(req.orderID.value());
        }

        if (req.origClientOrderId.has_value()) {
            params["origClientOrderId"] = req.origClientOrderId.value();
        }

        if (req.recvWindow.has_value()) {
            params["recvWindow"] =  std::to_string(req.recvWindow.value());
        }

        auto paramStr = util::Http::flattenParams(params);
        return get<QueryOrderResponse>("/api/v3/order", paramStr, "");
    }
}