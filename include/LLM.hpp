#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include "CurlClient.hpp"

class LLM {
    public:
    LLM(const std::string& base_url, const std::string& model_name, const std::string& system_prompt, double temperature = 0.7, bool stream = false);
    ~LLM();

    std::string get_response(const std::string& input);
    
    private:
    CurlClient client;
    std::string model;
    std::string system_prompt;
    double temperature;
    bool stream;
};