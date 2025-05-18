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

/*
template <typename T>
concept optionalHasFromJson = requires(const rapidjson::Value & jsonObj) {
    { T::value_type::fromJson(jsonObj) } -> std::same_as<T::value_type>;
};
*/


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

template <class T>
requires hasFromJson<T>
inline T getJsonValue(const rapidjson::Value & jsonObj, const char * fieldName)
{
    return T::fromJson(jsonObj[fieldName]);
}

template <class T>
inline std::optional<double> getJsonValue<std::optional<double>>(const rapidjson::Value & jsonObj, const char * fieldName)
{
    if (jsonObj.HasMember(fieldName))
    {
        return jsonObj[fieldName].GetDouble();
    }
    else [[likely]]
    {
        return std::nullopt;
    }
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

template <>
inline std::optional<double> getJsonValue<std::optional<double>>(const rapidjson::Value & jsonObj, const char * fieldName)
{
    if (jsonObj.HasMember(fieldName))
    {
        return jsonObj[fieldName].GetDouble();
    }
    else [[likely]]
    {
        return std::nullopt;
    }
}

// rapidjson::Document toJsonValue()
template <typename T>
concept hasToJsonValue = requires(T & obj) {
    { obj.toJsonValue() } -> std::same_as<rapidjson::Value>;
};

template <class T>
inline void fieldToJsonValue(
    rapidjson::Value & d, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator, T & obj, const char * fieldName) { };

template <class T>
requires hasToJsonValue<T>
inline void
fieldToJsonValue(rapidjson::Value & d, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator, T & obj, const char * fieldName)
{
    rapidjson::Value key(fieldName, allocator);


    d.AddMember(key, obj.toJsonValue(), allocator);
}

template <>
inline void fieldToJsonValue<int>(
    rapidjson::Value & d, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator, int & obj, const char * fieldName)
{
    rapidjson::Value key(fieldName, allocator);
    rapidjson::Value value(obj);
    d.AddMember(key, value, allocator);
}

template <>
inline void fieldToJsonValue<bool>(
    rapidjson::Value & d, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator, bool & obj, const char * fieldName)
{
    rapidjson::Value key(fieldName, allocator);
    rapidjson::Value value(obj);
    d.AddMember(key, value, allocator);
}

template <>
inline void fieldToJsonValue<long long>(
    rapidjson::Value & d, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator, long long & obj, const char * fieldName)
{
    rapidjson::Value key(fieldName, allocator);
    rapidjson::Value value;
    value.SetInt64(obj);
    d.AddMember(key, value, allocator);
}


template <>
inline void fieldToJsonValue<std::string>(
    rapidjson::Value & d, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator, std::string & obj, const char * fieldName)
{
    rapidjson::Value key(fieldName, allocator);
    rapidjson::Value value;
    value.SetString(obj.c_str(), obj.size(), allocator);
    d.AddMember(key, value, allocator);
}

template <>
inline void fieldToJsonValue<double>(
    rapidjson::Value & d, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator, double & obj, const char * fieldName)
{
    rapidjson::Value key(fieldName, allocator);
    rapidjson::Value value(obj);
    d.AddMember(key, value, allocator);
}

template <>
inline void fieldToJsonValue<std::optional<std::string>>(
    rapidjson::Value & d,
    rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator,
    std::optional<std::string> & obj,
    const char * fieldName)
{
    if (obj == std::nullopt)
    {
        return;
    }

    rapidjson::Value key(fieldName, allocator);
    rapidjson::Value value;
    auto & str = obj.value();
    value.SetString(str.c_str(), str.size(), allocator);
    d.AddMember(key, value, allocator);
}

template <>
inline void fieldToJsonValue<std::optional<long long>>(
    rapidjson::Value & d,
    rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator,
    std::optional<long long> & obj,
    const char * fieldName)
{
    if (obj == std::nullopt)
    {
        return;
    }

    rapidjson::Value key(fieldName, allocator);
    rapidjson::Value value;
    value.SetInt64(obj.value());
    d.AddMember(key, value, allocator);
}

template <>
inline void fieldToJsonValue<std::optional<double>>(
    rapidjson::Value & d,
    rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator,
    std::optional<double> & obj,
    const char * fieldName)
{
    if (obj == std::nullopt)
    {
        return;
    }

    rapidjson::Value key(fieldName, allocator);
    rapidjson::Value value(obj.value());
    d.AddMember(key, value, allocator);
}

template <>
inline void fieldToJsonValue<std::optional<bool>>(
    rapidjson::Value & d,
    rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> & allocator,
    std::optional<bool> & obj,
    const char * fieldName)
{
    if (obj == std::nullopt)
    {
        return;
    }

    rapidjson::Value key(fieldName, allocator);
    rapidjson::Value value(obj.value());
    d.AddMember(key, value, allocator);
}


#define DECLARE_MEMBER(r, data, elem) BOOST_PP_TUPLE_ELEM(0, elem) BOOST_PP_TUPLE_ELEM(1, elem);

#define GET_FROM_JSON(r, data, elem) \
    obj.BOOST_PP_TUPLE_ELEM(1, elem) = getJsonValue<BOOST_PP_TUPLE_ELEM(0, elem)>(jsonObj, BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(2, elem)));

#define TO_FROM_OBJ(r, data, elem) \
    fieldToJsonValue<BOOST_PP_TUPLE_ELEM(0, elem)>( \
        val, allocator, this->BOOST_PP_TUPLE_ELEM(1, elem), BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(2, elem)));

#define DEFINE_CLASS(ClassName, members) \
    class ClassName \
    { \
    public: \
        BOOST_PP_SEQ_FOR_EACH(DECLARE_MEMBER, _, members) \
        inline static ClassName fromJson(const rapidjson::Value & jsonObj) \
        { \
            ClassName obj; \
            BOOST_PP_SEQ_FOR_EACH(GET_FROM_JSON, _, members) \
            return obj; \
        } \
        inline static ClassName fromString(const std::string & str) \
        { \
            rapidjson::Document jsonObj; \
            jsonObj.Parse(str.data()); \
            ClassName obj; \
            BOOST_PP_SEQ_FOR_EACH(GET_FROM_JSON, _, members) \
            return obj; \
        } \
        inline rapidjson::Value toJsonValue() \
        { \
            rapidjson::Document doc; \
            rapidjson::Value val(rapidjson::kObjectType); \
            auto & allocator = doc.GetAllocator(); \
\
            BOOST_PP_SEQ_FOR_EACH(TO_FROM_OBJ, _, members) \
            return val; \
        } \
        inline rapidjson::Document toJsonDocument() \
        { \
            rapidjson::Document doc; \
            rapidjson::Value val(rapidjson::kObjectType); \
            auto & allocator = doc.GetAllocator(); \
            BOOST_PP_SEQ_FOR_EACH(TO_FROM_OBJ, _, members) \
            doc.CopyFrom(val, doc.GetAllocator()); \
            return doc; \
        } \
        inline std::string toJson() \
        { \
            rapidjson::Document doc = toJsonDocument(); \
            rapidjson::StringBuffer buffer; \
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer); \
            doc.Accept(writer); \
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
