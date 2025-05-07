#include <iostream>
#include <string>
#include <stdexcept>
#include <future>
#include <nlohmann/json.hpp>
#include "CurlClient.hpp"
#include "LLM.hpp"
#include "Memory.hpp"

std::string get_input() {
    std::string input;
    std::cout << "\nEnter your message: ";
    std::getline(std::cin, input);
    return input;
}

int main(void) {
    auto future_llm = std::async(std::launch::async, []() {
        return LLM("http://localhost:11434", "gemma3:12b-it-qat", "You are a helpful assistant. Your name is 名無しの権兵衛(Nanasi no Gonbe). Answer into Japanese.", 0.7);
    });
    Memory memory;
    std::string input = get_input();
    LLM llm = future_llm.get();
    while(true) {
        if (input == "/exit") {
            break;
        }
        memory.add_memory("user", input);
        std::cout << "Response: ";
        std::string response;
        llm.get_response_stream(memory.get_memory(), [&](const std::string& chunk) {
            nlohmann::json json_chunk = nlohmann::json::parse(chunk);
            if (!json_chunk["done"]) {
                std::string content = static_cast<std::string>(json_chunk["message"]["content"]);
                std::cout << content;
                response += content;
                std::cout.flush();
            }
        });
        memory.add_memory("assistant", response);
        input = get_input();
    }
        
    return 0;
}