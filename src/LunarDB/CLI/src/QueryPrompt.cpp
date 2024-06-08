#include <string>

#include "QueryPrompt.hpp"

namespace LunarDB::CLI {

QueryPrompt::QueryPrompt(std::istream& is) : m_is{is}
{
}

std::string QueryPrompt::readQuery()
{
    std::string query{};

    std::getline(m_is, query);

    return query;
}

} // namespace LunarDB::CLI
