#pragma once
#include <rapidjson/document.h>
#include <util/jsonBase.h>
#include <concepts>
#include <vector>

namespace Binance {
    class OrderBook: public JsonObject {
    public:
        bool deserialize(const rapidjson::Value &obj) override;
        long long lastUpdateId;
        std::vector<std::vector<double>> bids;
        std::vector<std::vector<double>> asks;
    private:
        void setLastUpdateId(long long _lastUpdateId) { lastUpdateId = _lastUpdateId; }

        void setBids(const rapidjson::Value::ConstArray& array) {
            for (auto &element : array) {
                std::vector<double> ve;
                const auto& subArray = element.GetArray();
                for (auto &item: subArray) {
                    ve.emplace_back(std::stod(item.GetString()));
                }

                bids.emplace_back(ve);
            }
        }


        void setAsks(const rapidjson::Value::ConstArray& array) {
            for (auto &element : array) {
                std::vector<double> ve;
                const auto& subArray = element.GetArray();
                for (auto &item: subArray) {
                    ve.emplace_back(std::stod(item.GetString()));
                }

                asks.emplace_back(ve);
            }
        }
    };


    bool OrderBook::deserialize(const rapidjson::Value &obj) {
        setLastUpdateId(obj["lastUpdateId"].GetInt64());
        setBids(obj["bids"].GetArray());
        setAsks(obj["asks"].GetArray());

        return true;
    }
}