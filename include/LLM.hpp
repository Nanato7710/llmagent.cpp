#pragma once
#include <string>
#include <vector>
#include <functional>
#include <nlohmann/json.hpp>
#include "CurlClient.hpp"

class LLM {
    public:
    LLM(const std::string& base_url, const std::string& model_name, const std::string& system_prompt, double temperature = 0.7);
    ~LLM();

    std::string get_response(const nlohmann::json& messages);
    void get_response_stream(const nlohmann::json& messages, const std::function<void(const std::string&)>& on_data);
    
    private:
    CurlClient client;
    std::string model;
    std::string system_prompt;
    double temperature;
    bool stream;
};