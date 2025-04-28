#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <vector>

class Memory {
    public:
    Memory();
    nlohmann::json to_json();
    void add_memory(const std::string& role, const std::string& content);
    std::vector<std::vector<std::vector<std::string>>> get_memory() const { return memory; }

    private:
    std::vector<std::vector<std::vector<std::string>>> memory;
};