#pragma once

#include <iostream>
#include <string>

namespace LunarDB::CLI {

class QueryPrompt
{
public:
    QueryPrompt(std::istream& is);

    std::string readQuery();
    bool done() const;

private:
    std::istream& m_is;
};

} // namespace LunarDB::CLI
