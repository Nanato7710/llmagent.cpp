#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <vector>

class Memory {
    public:
    Memory();
    void add_memory(const std::string& role, const std::string& content);
    nlohmann::json get_memory() const { return memory; }

    private:
    nlohmann::json memory;
};