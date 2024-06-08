#include "QueryPrompt.hpp"

#include <iostream>

namespace LunarDB::CLI {

std::string readQuery()
{
    std::string query{};

    std::getline(std::cin, query);

    return query;
}

} // namespace LunarDB::CLI
