#pragma once

#include <iostream>
#include <string>

namespace LunarDB::CLI {

std::string readQuery();

class QueryPrompt
{
public:
    QueryPrompt(std::istream& is);

    std::string readQuery();

private:
    std::istream& m_is;
};

} // namespace LunarDB::CLI
