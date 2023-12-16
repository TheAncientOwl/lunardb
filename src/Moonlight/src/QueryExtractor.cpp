#include "QueryExtractor.hpp"
#include "Utils.hpp"

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

std::vector<std::string_view> QueryExtractor::extractMultiple(std::size_t count)
{
    std::vector<std::string_view> multiple{};
    multiple.reserve(count);

    for (std::size_t i = 0; i < count; ++i)
    {
        multiple.emplace_back(extractOne());
    }

    return multiple;
}

std::vector<std::string_view> QueryExtractor::extractList()
{
    // TODO: Provide implementation
    return {};
}

std::string_view QueryExtractor::extractIfCondition()
{
    // TODO: Provide implementation
    return "";
}

std::string_view QueryExtractor::data() const
{
    return m_data;
}

bool QueryExtractor::empty() const
{
    return m_data.empty();
}

} // namespace LunarDB::Moonlight::Implementation
