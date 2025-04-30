#include <iostream>
#include <string>
#include <stdexcept>
#include <future>
#include <nlohmann/json.hpp>
#include "CurlClient.hpp"
#include "LLM.hpp"
#include "Memory.hpp"

int main(void) {
    auto future_llm = std::async(std::launch::async, []() {
        return LLM("http://localhost:11434", "qwen3:32b", "You are a helpful assistant. Your name is 名無しの権兵衛(Nanasi no Gonbe). Answer into Japanese. /nothink", 0.7, false);
    });
    // std::string input;
    // std::cout << "Enter your message: ";
    // std::getline(std::cin, input);
    LLM llm = future_llm.get();
    Memory memory;
    while(true) {
        std::string input;
        std::cout << "Enter your message: ";
        std::getline(std::cin, input);
        if (input == "/exit") {
            break;
        }
        memory.add_memory("user", input);
        std::string response = llm.get_response(memory.get_memory());
        nlohmann::json json_response = nlohmann::json::parse(response);
        std::cout << "Response: " << static_cast<std::string>(json_response["message"]["content"]) << std::endl;
        memory.add_memory("assistant", static_cast<std::string>(json_response["message"]["content"]));
    }
        
    return 0;
}