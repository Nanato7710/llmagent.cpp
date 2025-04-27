#pragma once

#include <string>
#include <nlohmann/json.hpp>

class CurlClient {
    public:
    CurlClient(const std::string& base_url);
    ~CurlClient();

    std::string postJson(const std::string& endpoint, const nlohmann::json& json_body);

    private:
    std::string baseUrl;
};