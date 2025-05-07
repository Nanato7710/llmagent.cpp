#pragma once

#include <string>
#include <nlohmann/json.hpp>

class CurlClient {
    public:
    CurlClient(const std::string& base_url);
    ~CurlClient();

    std::string post_json(const std::string& endpoint, const nlohmann::json& json_body);
    void post_json_stream(const std::string& endpoint, const nlohmann::json& json_body, const std::function<void(const std::string&)>& on_data);

    private:
    std::string base_url;
};