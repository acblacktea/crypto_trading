#pragma once
#include <concepts>
#include <vector>
#include <model/binance/Event.hpp>
#include <rapidjson/document.h>
#include <util/jsonBase.h>

namespace Binance
{
class PartialBookDepthEvent : public JsonObject, public Event
{
public:
    bool deserialize(const rapidjson::Value & obj) override;

    long long lastUpdateId;
    std::vector<std::vector<std::string>> bids;
    std::vector<std::vector<std::string>> asks;

private:
    void setLastUpdateId(long long _lastUpdateId) { lastUpdateId = _lastUpdateId; }

    void setBids(const rapidjson::Value::ConstArray & array)
    {
        for (auto & element : array)
        {
            std::vector<std::string> ve;
            const auto & subArray = element.GetArray();
            for (auto & item : subArray)
            {
                ve.emplace_back(item.GetString());
            }

            bids.emplace_back(ve);
        }
    }


    void setAsks(const rapidjson::Value::ConstArray & array)
    {
        for (auto & element : array)
        {
            std::vector<std::string> ve;
            const auto & subArray = element.GetArray();
            for (auto & item : subArray)
            {
                ve.emplace_back(item.GetString());
            }

            asks.emplace_back(ve);
        }
    }
};


bool PartialBookDepthEvent::deserialize(const rapidjson::Value & obj)
{
    setStream(obj["stream"].GetString());
    setLastUpdateId(obj["data"]["lastUpdateId"].GetInt64());
    setBids(obj["data"]["bids"].GetArray());
    setAsks(obj["data"]["asks"].GetArray());

    return true;
}
}