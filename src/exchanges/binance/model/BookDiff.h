#pragma once
#include <rapidjson/document.h>
#include <util/jsonBase.h>
#include <concepts>
#include <vector>
#include <exchanges/binance/model/Event.hpp>

namespace Binance {
    class BookDiffEvent: public JsonObject, public Event {
    public:
        bool deserialize(const rapidjson::Value &obj) override;
        std::string eventType;
        long long eventTime;
        std::string symbol;
        long long firstUpdateID;
        long long lastUpdateID;
        std::vector<std::vector<std::string>> bids;
        std::vector<std::vector<std::string>> asks;
    private:
        void setEventType(std::string &&_eventType) { eventType = std::move(_eventType); }
        void setEventTime(long long _eventTime) { eventTime = _eventTime; }
        void setSymbol(std::string &&_symbol) { symbol = std::move(_symbol); }
        void setFirstUpdateID(long long _firstUpdateID) { firstUpdateID = _firstUpdateID; }
        void setLastUpdateID(long long _lastUpdateID) { lastUpdateID = _lastUpdateID; }

        void setBids(const rapidjson::Value::ConstArray& array) {
            for (auto &element : array) {
                std::vector<std::string> ve;
                const auto& subArray = element.GetArray();
                for (auto &item: subArray) {
                    ve.emplace_back(item.GetString());
                }

                bids.emplace_back(ve);
            }
        }


        void setAsks(const rapidjson::Value::ConstArray& array) {
            for (auto &element : array) {
                std::vector<std::string> ve;
                const auto& subArray = element.GetArray();
                for (auto &item: subArray) {
                    ve.emplace_back(item.GetString());
                }

                asks.emplace_back(ve);
            }
        }
    };


    bool BookDiffEvent::deserialize(const rapidjson::Value &obj) {
        setStream(obj["stream"].GetString());
        setEventType(obj["data"]["e"].GetString());
        setEventTime(obj["data"]["E"].GetInt64());
        setSymbol(obj["data"]["s"].GetString());
        setFirstUpdateID(obj["data"]["U"].GetInt64());
        setLastUpdateID(obj["data"]["u"].GetInt64());
        setBids(obj["data"]["b"].GetArray());
        setAsks(obj["data"]["a"].GetArray());

        return true;
    }
}