#pragma once
#include <rapidjson/document.h>
#include <string>

class Event {
public:
    std::string stream;
    void setStream(std::string &&_stream) { stream = std::move(_stream); }
};