#include <sstream>
#include <string>

#include "QueryPrompt.hpp"

#include "LunarDB/Common/CppExtensions/StringUtils.hpp"

namespace LunarDB::CLI {

QueryPrompt::QueryPrompt(std::istream& is) : m_is{is}
{
}

namespace {

void readSchema(std::istream& is, std::ostringstream& oss)
{
    oss << '\n';

    std::string buffer{};

    while (std::getline(is, buffer))
    {
        oss << buffer << '\n';

        std::string_view line_sv{buffer};
        LunarDB::Common::CppExtensions::StringUtils::rtrim(line_sv);

        if (line_sv.back() == ';')
        {
            line_sv.remove_suffix(1);
            Common::CppExtensions::StringUtils::rtrim(line_sv);
        }

        if (line_sv.back() == '}')
        {
            break;
        }
    }
}

void readQuery(std::istream& is, std::ostringstream& oss)
{
    oss << '\n';

    std::string buffer{};

    while (std::getline(is, buffer))
    {
        oss << buffer << '\n';

        std::string_view line_sv{buffer};
        LunarDB::Common::CppExtensions::StringUtils::rtrim(line_sv);
        if (line_sv.back() == ';')
        {
            break;
        }
    }
}

} // namespace

std::string QueryPrompt::readQuery()
{
    std::ostringstream oss{};

    std::string line{};

    std::getline(m_is, line);
    oss << line;

    std::string_view line_sv{line};
    Common::CppExtensions::StringUtils::trim(line_sv);
    if (Common::CppExtensions::StringUtils::startsWithIgnoreCase(line_sv, "schema"))
    {
        if (line_sv.back() == ';')
        {
            line_sv.remove_suffix(1);
            Common::CppExtensions::StringUtils::rtrim(line_sv);
        }

        if (line_sv.back() != '}')
        {
            LunarDB::CLI::readSchema(m_is, oss);
        }
    }
    else if (line_sv.back() != ';')
    {
        LunarDB::CLI::readQuery(m_is, oss);
    }

    return oss.str();
}

bool QueryPrompt::done() const
{
    return !static_cast<bool>(m_is);
}

} // namespace LunarDB::CLI
