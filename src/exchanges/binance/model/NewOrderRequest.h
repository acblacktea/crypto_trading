#pragma once
#include <rapidjson/document.h>
#include <util/jsonBase.h>
#include <exchanges/binance/model/Event.hpp>
#include <optional>
#include <any>

namespace Binance {
    class NewOrderRequest : public JsonObject {
    public:
        bool deserialize(const rapidjson::Value &obj) override;
        std::string serialize() override;

        std::string symbol;
        std::string side;
        std::string type;
        std::optional<std::string> timeInForce;
        std::optional<std::string> quantity;
        std::optional<std::string> price;
        std::optional<std::string> quoteOrderQty;
        std::optional<std::string> stopPrice;
    };


    bool NewOrderRequest::deserialize(const rapidjson::Value &obj) {
        return false;
    }

    std::string NewOrderRequest::serialize() {
        rapidjson::Document doc;
        doc.SetObject();
        doc.AddMember("symbol", rapidjson::StringRef(symbol.c_str()), doc.GetAllocator());
        doc.AddMember("side", rapidjson::StringRef(side.c_str()), doc.GetAllocator());
        doc.AddMember("type", rapidjson::StringRef(side.c_str()), doc.GetAllocator());

        if (timeInForce.has_value()) {
            doc.AddMember("timeInForce", rapidjson::StringRef(timeInForce.value().c_str()), doc.GetAllocator());
        }

        if (quantity.has_value()) {
            doc.AddMember("quantity", rapidjson::StringRef(quantity.value().c_str()), doc.GetAllocator());
        }

        if (price.has_value()) {
            doc.AddMember("price", rapidjson::StringRef(price.value().c_str()), doc.GetAllocator());
        }

        if (quoteOrderQty.has_value()) {
            doc.AddMember("quoteOrderQty", rapidjson::StringRef(quoteOrderQty.value().c_str()), doc.GetAllocator());
        }

        if (stopPrice.has_value()) {
            doc.AddMember("stopPrice", rapidjson::StringRef(stopPrice.value().c_str()), doc.GetAllocator());
        }

        // 3. Stringify the DOM
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        doc.Accept(writer);


        return buffer.GetString();
    }
}