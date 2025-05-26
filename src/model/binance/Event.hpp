#pragma once
#include <string>
#include <rapidjson/document.h>

class Event
{
public:
    std::string stream;
    void setStream(std::string && _stream) { stream = std::move(_stream); }
};