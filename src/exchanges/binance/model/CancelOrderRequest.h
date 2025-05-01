#pragma once
#include <optional>
#include <exchanges/binance/model/Event.hpp>
#include <rapidjson/document.h>
#include <util/jsonBase.h>


namespace Binance
{
class CancelOrderRequest : public JsonObject
{
public:
    bool deserialize(const rapidjson::Value & obj) override;
    std::string serialize() override;

    std::string symbol;
    long long timestamp;
    std::optional<long long> orderID;
    std::optional<std::string> origClientOrderId;
    std::optional<std::string> cancelRestrictions;
    std::optional<long long> recvWindow;
};

bool CancelOrderRequest::deserialize(const rapidjson::Value & obj)
{
    return false;
}

std::string CancelOrderRequest::serialize()
{
    /*
    rapidjson::Document doc;
    doc.SetObject();
    doc.AddMember("symbol", rapidjson::StringRef(symbol.c_str()), doc.GetAllocator());
    //doc.AddMember("timestamp", timestamp, doc.GetAllocator());

    if (orderID.has_value())
    {
        doc.AddMember("orderID", orderID.value(), doc.GetAllocator());
    }

    if (origClientOrderId.has_value())
    {
        doc.AddMember("origClientOrderId", rapidjson::StringRef(origClientOrderId.value().c_str()), doc.GetAllocator());
    }

    if (cancelRestrictions.has_value())
    {
        doc.AddMember("cancelRestrictions", rapidjson::StringRef(cancelRestrictions.value().c_str()), doc.GetAllocator());
    }

    if (recvWindow.has_value())
    {
        doc.AddMember("recvWindow", recvWindow.value(), doc.GetAllocator());
    }


    // 3. Stringify the DOM
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);


    return buffer.GetString();
    */

    return "";
}


}