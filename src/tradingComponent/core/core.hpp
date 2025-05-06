#pragma once
#include <atomic>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <unistd.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <sys/wait.h>
#include <util/MMapQueue.hpp>

class Core
{
public:
    Core(std::string & mmapFile, size_t mmapSize)
    {
        _mmapFile = mmapFile;
        _mmapSize = mmapSize;
    }

    void execute()
    {
        auto mpQueue = MMapQueueV2(_mmapFile, _mmapSize);
        std::string s;
        while (true)
        {
            while (!mpQueue.pop(s))
            {
            }

            rapidjson::Document document;
            document.Parse(s.c_str());

            rapidjson::StringBuffer buffer;

            buffer.Clear();
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            document.Accept(writer);
            std::string value = buffer.GetString();
            std::cout << "test " << value << " " << value.size() << std::endl;
        }
    }

private:
    std::string _mmapFile;
    size_t _mmapSize;
};