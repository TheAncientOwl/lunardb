#include "QueryExtractor.hpp"
#include "Utils.hpp"

#include <stdexcept>

namespace LunarDB::Moonlight::Implementation {

QueryExtractor::QueryExtractor(std::string_view query)
    : m_data(query)
{
    Utils::trim(m_data);

    if (m_data.back() == ';')
    {
        m_data.remove_suffix(1);
    }

    Utils::rtrim(m_data);
}

std::string_view QueryExtractor::extractOne()
{
    const auto whitespace_pos = m_data.find_first_of(Utils::c_whitespace);

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
        Utils::ltrim(m_data);

        return one;
    }
}

std::vector<std::string_view> QueryExtractor::extractList()
{
    if (m_data.front() != '[')
    {
        throw std::runtime_error("Missing '['");
    }
    m_data.remove_prefix(1);
    Utils::ltrim(m_data);

    const auto closed_square_bracket_pos = m_data.find_first_of(']');
    if (closed_square_bracket_pos == std::string_view::npos)
    {
        throw std::runtime_error("Missing ]");
    }

    const auto list_str{ m_data.substr(0, closed_square_bracket_pos) };
    m_data.remove_prefix(closed_square_bracket_pos + 1);
    Utils::ltrim(m_data);

    return Utils::split(list_str);
}

std::string_view QueryExtractor::data() const
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
    Utils::ltrim(m_data);
}

} // namespace LunarDB::Moonlight::Implementation
