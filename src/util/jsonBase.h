#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <type_traits>
#include <boost/preprocessor.hpp>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>

template <typename T>
concept hasFromJson = requires(const rapidjson::Value & jsonObj) {
    { T::fromJson(jsonObj) } -> std::same_as<T>;
};

template <class T>
inline T getJsonValue(const rapidjson::Value & jsonObj, const char * fieldName)
{
    return T();
}

template <class T>
requires hasFromJson<T>
inline T getJsonValue(const rapidjson::Value & jsonObj, const char * fieldName)
{
    return T::fromJson(jsonObj[fieldName]);
}

template <>
inline int getJsonValue<int>(const rapidjson::Value & jsonObj, const char * fieldName)
{
    return jsonObj[fieldName].GetInt();
}
template <>
inline bool getJsonValue<bool>(const rapidjson::Value & jsonObj, const char * fieldName)
{
    return jsonObj[fieldName].GetBool();
}

template <>
inline long long getJsonValue<long long>(const rapidjson::Value & jsonObj, const char * fieldName)
{
    return jsonObj[fieldName].GetInt64();
}
template <>
inline std::string getJsonValue<std::string>(const rapidjson::Value & jsonObj, const char * fieldName)
{
    return jsonObj[fieldName].GetString();
}

#define DECLARE_MEMBER(r, data, elem) BOOST_PP_TUPLE_ELEM(0, elem) BOOST_PP_TUPLE_ELEM(1, elem);

#define GET_FROM_JSON(r, data, elem) \
    obj.BOOST_PP_TUPLE_ELEM(1, elem) = getJsonValue<BOOST_PP_TUPLE_ELEM(0, elem)>(jsonObj, BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(2, elem)));

#define DEFINE_CLASS(ClassName, members) \
    class ClassName \
    { \
    public: \
        BOOST_PP_SEQ_FOR_EACH(DECLARE_MEMBER, _, members) \
        static ClassName fromJson(const rapidjson::Value & jsonObj) \
        { \
            ClassName obj; \
            BOOST_PP_SEQ_FOR_EACH(GET_FROM_JSON, _, members) \
            return obj; \
        } \
    };

class JsonObject
{
public:
    JsonObject() { }
    virtual bool deserialize(const rapidjson::Value & obj) = 0;
    virtual std::string serialize() { return ""; };
};
