#pragma once
#include <string>
#include <rapidjson/prettywriter.h>
#include <rapidjson/document.h>
#include <boost/preprocessor.hpp>

class JsonObject {
public:
    JsonObject() {

    }
    virtual bool deserialize(const rapidjson::Value& obj) = 0;
    virtual std::string serialize() {
        return "";
    };
};


/*
   template <typename T1, typename T2>
   long long getElement(const rapidjson::Value &obj, const std::string&& fieldName) {
       if (std::is_same<T1, std::vector<std::vector<double>>>::value) {
           return obj[fieldName.c_str()].GetArray();
       } else if (std::is_same<T1, double>::value || std::is_same<T1, std::string>::value) {
           return obj[fieldName.c_str()].GetString();
       } else if (std::is_same<T1, long long>::value) {
           return obj[fieldName.c_str()].GetInt64();
       }
   }
*/