#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <type_traits>
#include <boost/preprocessor.hpp>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

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

template <>
inline double getJsonValue<double>(const rapidjson::Value & jsonObj, const char * fieldName)
{
    return jsonObj[fieldName].GetDouble();
}

template <>
inline std::optional<std::string> getJsonValue<std::optional<std::string>>(const rapidjson::Value & jsonObj, const char * fieldName)
{
    if (jsonObj.HasMember(fieldName))
    {
        return jsonObj[fieldName].GetString();
    }
    else [[likely]]
    {
        return std::nullopt;
    }
}

template <>
inline std::optional<long long> getJsonValue<std::optional<long long>>(const rapidjson::Value & jsonObj, const char * fieldName)
{
    if (jsonObj.HasMember(fieldName))
    {
        return jsonObj[fieldName].GetInt64();
    }
    else [[likely]]
    {
        return std::nullopt;
    }
}

template <>
inline std::optional<bool> getJsonValue<std::optional<bool>>(const rapidjson::Value & jsonObj, const char * fieldName)
{
    if (jsonObj.HasMember(fieldName))
    {
        return jsonObj[fieldName].GetBool();
    }
    else [[likely]]
    {
        return std::nullopt;
    }
}


template <typename T>
concept hasToJsonValue = requires(T obj) {
    { obj.toJsonValue() } -> std::same_as<rapidjson::Document>;
};

template <class T>
inline void fieldToJsonValue(
    rapidjson::Document & d, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator, T & obj, const char * fieldName)
{
}

template <>
inline void fieldToJsonValue<int>(
    rapidjson::Document & d, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator, int & obj, const char * fieldName)
{
    d.AddMember(fieldName, obj, allocator);
}

template <class T>
requires hasToJsonValue<T>
inline void fieldToJsonValue(rapidjson::Document & d, rapidjson::CrtAllocator & allocator, T & obj, const char * fieldName)
{
    d.AddMember(fieldName, obj.toJsonValue(), allocator);
}

template <>
inline void fieldToJsonValue<bool>(rapidjson::Document & d, rapidjson::CrtAllocator & allocator, int & obj, const char * fieldName)
{
    d.AddMember(fieldName, rapidjson::value(obj), allocator);
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

template <>
inline double getJsonValue<double>(const rapidjson::Value & jsonObj, const char * fieldName)
{
    return jsonObj[fieldName].GetDouble();
}

template <>
inline std::optional<std::string> getJsonValue<std::optional<std::string>>(const rapidjson::Value & jsonObj, const char * fieldName)
{
    if (jsonObj.HasMember(fieldName))
    {
        return jsonObj[fieldName].GetString();
    }
    else [[likely]]
    {
        return std::nullopt;
    }
}

template <>
inline std::optional<long long> getJsonValue<std::optional<long long>>(const rapidjson::Value & jsonObj, const char * fieldName)
{
    if (jsonObj.HasMember(fieldName))
    {
        return jsonObj[fieldName].GetInt64();
    }
    else [[likely]]
    {
        return std::nullopt;
    }
}

template <>
inline std::optional<bool> getJsonValue<std::optional<bool>>(const rapidjson::Value & jsonObj, const char * fieldName)
{
    if (jsonObj.HasMember(fieldName))
    {
        return jsonObj[fieldName].GetBool();
    }
    else [[likely]]
    {
        return std::nullopt;
    }
}


#define DECLARE_MEMBER(r, data, elem) BOOST_PP_TUPLE_ELEM(0, elem) BOOST_PP_TUPLE_ELEM(1, elem);

#define GET_FROM_JSON(r, data, elem) \
    obj.BOOST_PP_TUPLE_ELEM(1, elem) = getJsonValue<BOOST_PP_TUPLE_ELEM(0, elem)>(jsonObj, BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(2, elem)));

#define TO_FROM_OBJ(r, data, elem) \
    obj.BOOST_PP_TUPLE_ELEM(1, elem) = getJsonValue<BOOST_PP_TUPLE_ELEM(0, elem)>(jsonObj, BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(2, elem)));

#define TO_FROM_OBJ2(r, data, elem) \
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
        rapidjson::Document toJsonValue() \
        { \
            rapidjson::Document doc(rapidjson::kObjectType); \
            auto & allocator = doc.GetAllocator(); \
            \   
            BOOST_PP_SEQ_FOR_EACH(TO_FROM_JSON, _, members) return doc; \
        } \
        std::string toJson() \
        { \
            rapidjson::Document doc = toJsonValue(); \
            StringBuffer buffer; \
            Writer<StringBuffer> writer(buffer); \
            value.Accept(writer); \
            return buffer.GetString(); \
        } \
    };

class JsonObject
{
public:
    JsonObject() { }
    virtual bool deserialize(const rapidjson::Value & obj) = 0;
    virtual std::string serialize() { return ""; };
};
