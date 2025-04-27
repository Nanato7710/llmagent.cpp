#include <iostream>
#include <string>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include "LLM.hpp"
#include "CurlClient.hpp"

LLM::LLM(const std::string& base_url, const std::string& model_name, const std::string& system_prompt, double temperature, bool stream)
    : client(base_url), model(model_name), system_prompt(system_prompt), temperature(temperature), stream(stream) {
        nlohmann::json json_body = {
            {"model", model}
        };
        client.postJson("/api/generate", json_body);
    }
LLM::~LLM() {}

std::string LLM::get_response(const std::string& input) {
    nlohmann::json json_body = {
        {"model", model},
        {"messages", {
            {
                {"role", "system"},
                {"content", system_prompt}
            },
            {
                {"role", "user"},
                {"content", input}
            }
        }},
        {"stream", stream},
        {"options", {{"temperature", temperature}}}
    };

    try {
        std::string response = client.postJson("/api/chat", json_body);
        return response;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return "";
    }
}