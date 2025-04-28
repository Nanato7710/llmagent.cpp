#include "Memory.hpp"
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

Memory::Memory() {}

void Memory::add_memory(const std::string& role, const std::string& content) {
    memory.push_back({{"role", role}, {"content", content}});
}

nlohmann::json Memory::to_json() {
    nlohmann::json json_memory;
    json_memory["messages"] = memory;
    return json_memory;
}
