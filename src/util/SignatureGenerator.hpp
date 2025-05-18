#pragma once

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <vector>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <rapidjson/document.h>

std::string generateBinanceSignature(const std::string & secret_key, const std::string & query_string)
{
    unsigned char * digest = HMAC(
        EVP_sha256(), secret_key.c_str(), secret_key.length(), (unsigned char *)query_string.c_str(), query_string.length(), NULL, NULL);

    // Convert binary digest to hex string
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
    {
        ss << std::setw(2) << static_cast<unsigned>(digest[i]);
    }

    return ss.str();
}


std::string generateBinanceSignatureString(const std::string & secret_key, const rapidjson::Value & params)
{
    std::vector<std::pair<std::string, std::string>> paramPairs;

    // Extract and encode parameters
    for (auto it = params.MemberBegin(); it != params.MemberEnd(); ++it)
    {
        const std::string key = it->name.GetString();

        if (key == "signature")
        {
            continue;
        }

        const auto & value = it->value;
        std::string valueStr;

        // Convert value to string based on type
        if (value.IsString())
        {
            valueStr = value.GetString();
        }
        else
        {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            value.Accept(writer);
            valueStr = buffer.GetString();
        }

        paramPairs.emplace_back(key, valueStr);
    }

    std::sort(paramPairs.begin(), paramPairs.end(), [](const auto & a, const auto & b) { return a.first < b.first; });

    std::string queryString;
    bool first = true;

    for (const auto & [key, value] : paramPairs)
    {
        if (!first)
        {
            queryString += "&";
        }
        first = false;
        queryString += key + "=" + value;
    }

    return generateBinanceSignature(secret_key, queryString);
}