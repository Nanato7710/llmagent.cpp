#include "Memory.hpp"
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

Memory::Memory() : memory(nlohmann::json::array()) {}

void Memory::add_memory(const std::string& role, const std::string& content) {
    nlohmann::json message = {
        {"role", role},
        {"content", content}
    };
    memory.push_back(message);
}
