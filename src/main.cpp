#include <iostream>
#include <string>
#include <stdexcept>
#include <future>
#include <nlohmann/json.hpp>
#include "CurlClient.hpp"
#include "LLM.hpp"

int main(void) {
    auto future_llm = std::async(std::launch::async, []() {
        return LLM("http://localhost:11434", "gemma3:4b-it-qat", "You are a helpful assistant. Your name is 名無しの権兵衛.", 0.7, false);
    });
    std::string input;
    std::cout << "Enter your message: ";
    std::getline(std::cin, input);
    LLM llm = future_llm.get();
    std::string response = llm.get_response(input);
    nlohmann::json json_response = nlohmann::json::parse(response);
    std::cout << "Response: " << static_cast<std::string>(json_response["message"]["content"]) << std::endl;

    return 0;
}