#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include "LLM.hpp"
#include "CurlClient.hpp"

LLM::LLM(const std::string& base_url, const std::string& model_name, const std::string& system_prompt, double temperature)
    : client(base_url), model(model_name), system_prompt(system_prompt), temperature(temperature) {
        nlohmann::json json_body = {
            {"model", model}
        };
        client.post_json("/api/generate", json_body);
    }
LLM::~LLM() {}

std::string LLM::get_response(const nlohmann::json& messages) {
    nlohmann::json json_body;
    json_body["model"] = model;
    json_body["stream"] = false;
    json_body["options"]["temperature"] = temperature;
    json_body["messages"] = messages;

    if (messages.empty() || messages[0]["role"] != "system" || messages[0]["content"] != system_prompt) {
        json_body["messages"].insert(json_body["messages"].begin(),{{
            {"role", "system"},
            {"content", system_prompt}
        }});
    }

    try {
        std::string response = client.post_json("/api/chat", json_body);
        return response;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return "";
    }
}

void LLM::get_response_stream(const nlohmann::json& messages, const std::function<void(const std::string&)>& on_data) {
    nlohmann::json json_body;
    json_body["model"] = model;
    json_body["stream"] = true;
    json_body["options"]["temperature"] = temperature;
    json_body["messages"] = messages;

    if (messages.empty() || messages[0]["role"] != "system" || messages[0]["content"] != system_prompt) {
        json_body["messages"].insert(json_body["messages"].begin(),{{
            {"role", "system"},
            {"content", system_prompt}
        }});
    }

    try {
        client.post_json_stream("/api/chat", json_body, on_data);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}