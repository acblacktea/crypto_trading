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
    virtual std::string serialize() = 0;
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


#define FIELD(FIELD_NAME, FIELD_TYPE, TAG_NAME) \
    FIELD_TYPE FIELD_NAME;                      \
    template<typename T, typename T2 = FIELD_TYPE>   \
    void set##FIELD_NAME(T& t) { \
        if (std::is_same<T2, long long>::value) { \
            FIELD_NAME = t;   \
        } else if (std::is_same<T2, string>::value) { \
            FIELD_NAME = t;                     \
        } else if (std::is_same<T2, string>::value) {\
            FIELD_NAME = t; \
        } else if (std::is_same<T2, vector<vector<double>>>::value) { \
            for (auto &element : array) {  \
                std::vector<double> ve;    \
                const auto& subArray = element.GetArray(); \
                for (auto &item: subArray) {    \
                    ve.emplace_back(std::stod(item.GetString())); \
                }                               \
                ##FIELD_NAME.emplace_back(ve);  \
            } \
        } \
    }

#define FIELDS(FIELD_NAME, FIELD_TYPE, TAG_NAME, ...)\
    FIELD(FIELD_NAME, FIELD_TYPE, TAG_NAME)     \
    FIELDS(...)

#define DESERIALIZE(FIELD_NAME, FIELD_TYPE, TAG_NAME) \
    template<typename T, typename T2 = FIELD_TYPE> \
    if (std::is_same<T2, long long>::value) { \
        FIELD_NAME = t;   \
    } else if (std::is_same<T2, string>::value) { \
        values = t; \
    } else if (std::is_same<T2, vector <vector<double>>>::value) { \
       \
    } \

#define DESERIALIZES(FIELD_NAME, FIELD_TYPE, TAG_NAME, ...) \
    DESERIALIZE(FIELD_NAME, FIELD_TYPE, TAG_NAME)     \
    DESERIALIZES(...)

#define MODEL(NAME, FIELDS) \
class NAME {                \
public:                     \
    FIELDS(FIELDS)          \
    bool ##NAME::deserialize(const rapidjson::Value &obj) {\
            DESERIALIZES(FIELDS)\
            return true;\
    } \
};\


#define CREATE_MY_MACRO_PLACEHOLDER_FILLER_0(X, Y, Z) \
  ((X, Y, Z)) CREATE_MY_MACRO_PLACEHOLDER_FILLER_1
#define CREATE_MY_MACRO_PLACEHOLDER_FILLER_1(X, Y, Z) \
  ((X, Y, Z)) CREATE_MY_MACRO_PLACEHOLDER_FILLER_0
#define CREATE_MY_MACRO_PLACEHOLDER_FILLER_0_END
#define CREATE_MY_MACRO_PLACEHOLDER_FILLER_1_END

#define DECLARE_DATA_MEMBER(R, _, TYPE_AND_NAME)                        \
  BOOST_PP_TUPLE_ELEM(3, 0, TYPE_AND_NAME) BOOST_PP_TUPLE_ELEM(3, 1, TYPE_AND_NAME);

#define DEFINE_SERIALIZATION_ELEMENT(R, _, TYPE_AND_NAME)               \
  { BOOST_PP_TUPLE_ELEM(3, 2, TYPE_AND_NAME), o.BOOST_PP_TUPLE_ELEM(3, 1, TYPE_AND_NAME) },

#define DEFINE_DESERIALIZATION_ELEMENT(R, _, TYPE_AND_NAME)             \
  o.BOOST_PP_TUPLE_ELEM(3, 1, TYPE_AND_NAME) = j.at(BOOST_PP_TUPLE_ELEM(3, 2, TYPE_AND_NAME)).get<BOOST_PP_TUPLE_ELEM(3, 0, TYPE_AND_NAME)>();

#define DEFINE_EQUAL_OPERATOR_ELEM(R, _, TYPE_AND_NAME)                 \
  lhs.BOOST_PP_TUPLE_ELEM(3, 1, TYPE_AND_NAME) == rhs.BOOST_PP_TUPLE_ELEM(3, 1, TYPE_AND_NAME) &&

#define DEFINE_MODEL(NAME, TYPES_AND_NAMES)                             \
  struct NAME {                                                         \
    BOOST_PP_SEQ_FOR_EACH(DECLARE_DATA_MEMBER, _, BOOST_PP_CAT(CREATE_MY_MACRO_PLACEHOLDER_FILLER_0 TYPES_AND_NAMES,_END)) \
  };                                                                    \
  void to_json(json& j, const NAME& o) {                                \
    j = json{BOOST_PP_SEQ_FOR_EACH(DEFINE_SERIALIZATION_ELEMENT, _, BOOST_PP_CAT(CREATE_MY_MACRO_PLACEHOLDER_FILLER_0 TYPES_AND_NAMES,_END))}; \
  }                                                                     \
  void from_json(const json& j, NAME& o) {                              \
    BOOST_PP_SEQ_FOR_EACH(DEFINE_DESERIALIZATION_ELEMENT, _, BOOST_PP_CAT(CREATE_MY_MACRO_PLACEHOLDER_FILLER_0 TYPES_AND_NAMES,_END)) \
  }                                                                     \
  bool operator ==(const NAME& lhs, const NAME& rhs) {                  \
    return BOOST_PP_SEQ_FOR_EACH(DEFINE_EQUAL_OPERATOR_ELEM, _, BOOST_PP_CAT(CREATE_MY_MACRO_PLACEHOLDER_FILLER_0 TYPES_AND_NAMES,_END)) true; \
  }

#define DEFINE_MODEL_JSON(NAME, TYPES_AND_NAMES)                        \
  struct NAME {                                                         \
    BOOST_PP_SEQ_FOR_EACH(DECLARE_DATA_MEMBER, _, BOOST_PP_CAT(CREATE_MY_MACRO_PLACEHOLDER_FILLER_0 TYPES_AND_NAMES,_END)) \
  };                                                                    \
  void to_json(json& j, const NAME& o) {                                \
    j = json{BOOST_PP_SEQ_FOR_EACH(DEFINE_SERIALIZATION_ELEMENT, _, BOOST_PP_CAT(CREATE_MY_MACRO_PLACEHOLDER_FILLER_0 TYPES_AND_NAMES,_END))}; \
  }                                                                     \
  void from_json(const json& j, NAME& o) {                              \
    BOOST_PP_SEQ_FOR_EACH(DEFINE_DESERIALIZATION_ELEMENT, _, BOOST_PP_CAT(CREATE_MY_MACRO_PLACEHOLDER_FILLER_0 TYPES_AND_NAMES,_END)) \
  }

#define DEFINE_MODEL_TO_JSON(NAME, TYPES_AND_NAMES)                     \
  struct NAME {                                                         \
    BOOST_PP_SEQ_FOR_EACH(DECLARE_DATA_MEMBER, _, BOOST_PP_CAT(CREATE_MY_MACRO_PLACEHOLDER_FILLER_0 TYPES_AND_NAMES,_END)) \
  };                                                                    \
  void to_json(json& j, const NAME& o) {                                \
    j = json{BOOST_PP_SEQ_FOR_EACH(DEFINE_SERIALIZATION_ELEMENT, _, BOOST_PP_CAT(CREATE_MY_MACRO_PLACEHOLDER_FILLER_0 TYPES_AND_NAMES,_END))}; \
  }                                                                     \
  bool operator ==(const NAME& lhs, const NAME& rhs) {                  \
    return BOOST_PP_SEQ_FOR_EACH(DEFINE_EQUAL_OPERATOR_ELEM, _, BOOST_PP_CAT(CREATE_MY_MACRO_PLACEHOLDER_FILLER_0 TYPES_AND_NAMES,_END)) true; \
  }

#define DEFINE_MODEL_FROM_JSON(NAME, TYPES_AND_NAMES)                   \
  struct NAME {                                                         \
    BOOST_PP_SEQ_FOR_EACH(DECLARE_DATA_MEMBER, _, BOOST_PP_CAT(CREATE_MY_MACRO_PLACEHOLDER_FILLER_0 TYPES_AND_NAMES,_END)) \
  };                                                                    \
  void from_json(const json& j, NAME& o) {                              \
    BOOST_PP_SEQ_FOR_EACH(DEFINE_DESERIALIZATION_ELEMENT, _, BOOST_PP_CAT(CREATE_MY_MACRO_PLACEHOLDER_FILLER_0 TYPES_AND_NAMES,_END)) \
      }                                                                 \
  bool operator ==(const NAME& lhs, const NAME& rhs) {                  \
    return BOOST_PP_SEQ_FOR_EACH(DEFINE_EQUAL_OPERATOR_ELEM, _, BOOST_PP_CAT(CREATE_MY_MACRO_PLACEHOLDER_FILLER_0 TYPES_AND_NAMES,_END)) true; \
  }

#define DEFINE_MODEL_TO_JSON_RAW(NAME, TYPES_AND_NAMES)                 \
  struct NAME {                                                         \
    BOOST_PP_SEQ_FOR_EACH(DECLARE_DATA_MEMBER, _, BOOST_PP_CAT(CREATE_MY_MACRO_PLACEHOLDER_FILLER_0 TYPES_AND_NAMES,_END)) \
  };                                                                    \
  void to_json(json& j, const NAME& o) {                                \
    j = json{BOOST_PP_SEQ_FOR_EACH(DEFINE_SERIALIZATION_ELEMENT, _, BOOST_PP_CAT(CREATE_MY_MACRO_PLACEHOLDER_FILLER_0 TYPES_AND_NAMES,_END))}; \
  }

#define DEFINE_MODEL_FROM_JSON_RAW(NAME, TYPES_AND_NAMES)               \
  struct NAME {                                                         \
    BOOST_PP_SEQ_FOR_EACH(DECLARE_DATA_MEMBER, _, BOOST_PP_CAT(CREATE_MY_MACRO_PLACEHOLDER_FILLER_0 TYPES_AND_NAMES,_END)) \
  };                                                                    \
  void from_json(const json& j, NAME& o) {                              \
    BOOST_PP_SEQ_FOR_EACH(DEFINE_DESERIALIZATION_ELEMENT, _, BOOST_PP_CAT(CREATE_MY_MACRO_PLACEHOLDER_FILLER_0 TYPES_AND_NAMES,_END)) \
  }