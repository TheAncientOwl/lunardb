#include <stdexcept>

#include "QueryExtractor.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace CppExtensions;

QueryExtractor::QueryExtractor(std::string_view query)
    : m_data(query)
{
    StringUtils::trim(m_data);

    if (m_data.back() == ';')
    {
        m_data.remove_suffix(1);
    }

    StringUtils::rtrim(m_data);
}

std::string_view QueryExtractor::extractOne()
{
    const auto whitespace_pos = m_data.find_first_of(StringUtils::c_whitespace);

    if (whitespace_pos == std::string_view::npos)
    {
        const auto one{ m_data };
        m_data.remove_prefix(m_data.size());

        return one;
    }
    else
    {
        const auto one{ m_data.substr(0, whitespace_pos) };
        m_data.remove_prefix(whitespace_pos);
        StringUtils::ltrim(m_data);

        return one;
    }
}

std::vector<std::string_view> QueryExtractor::extractList(char sep, std::pair<char, char> bound_chars)
{
    if (m_data.front() != bound_chars.first)
    {
        std::string str{};
        str.push_back(bound_chars.first);
        throw Errors::buildMissingError(str);
    }
    m_data.remove_prefix(1);
    StringUtils::ltrim(m_data);

    const auto closed_square_bracket_pos = m_data.find_first_of(bound_chars.second);
    if (closed_square_bracket_pos == std::string_view::npos)
    {
        std::string str{};
        str.push_back(bound_chars.second);
        throw Errors::buildMissingError(str);
    }

    const auto list_str{ m_data.substr(0, closed_square_bracket_pos) };
    m_data.remove_prefix(closed_square_bracket_pos + 1);
    StringUtils::ltrim(m_data);

    return Utils::split(list_str, sep);
}

std::string_view QueryExtractor::data() const
{
    return m_data;
}

std::string_view& QueryExtractor::unsafe_data()
{
    return m_data;
}

bool QueryExtractor::empty() const
{
    return m_data.empty();
}

void QueryExtractor::remove_prefix(std::size_t size)
{
    m_data.remove_prefix(size);
    StringUtils::ltrim(m_data);
}

} // namespace LunarDB::Moonlight::Implementation
