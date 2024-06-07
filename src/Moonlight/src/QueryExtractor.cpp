#include <stdexcept>

#include "Errors.hpp"
#include "LunarDB/Common/CppExtensions/StringUtils.hpp"
#include "LunarDB/Moonlight/QueryExtractor.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

namespace CppExtensions = LunarDB::Common::CppExtensions;
namespace StringUtils = Common::CppExtensions::StringUtils;

QueryExtractor::QueryExtractor(std::string_view query) : m_data(query)
{
    StringUtils::trim(m_data);

    if (!m_data.empty() && m_data.back() == ';')
    {
        m_data.remove_suffix(1);
    }

    StringUtils::rtrim(m_data);
}

std::string_view QueryExtractor::extractOne()
{
    auto const whitespace_pos = m_data.find_first_of(StringUtils::whitespace());

    if (whitespace_pos == std::string_view::npos)
    {
        auto const one{m_data};
        m_data.remove_prefix(m_data.size());

        return one;
    }
    else
    {
        auto const one{m_data.substr(0, whitespace_pos)};
        m_data.remove_prefix(whitespace_pos);
        StringUtils::ltrim(m_data);

        return one;
    }
}

std::vector<std::string_view> QueryExtractor::extractList(
    char sep,
    std::pair<char, char> bound_chars,
    bool raw_percent_percent)
{
    if (m_data.empty())
    {
        return {};
    }

    if (m_data.front() != bound_chars.first)
    {
        std::string str{};
        str.push_back(bound_chars.first);
        throw Errors::buildMissingError(str);
    }
    m_data.remove_prefix(1);
    StringUtils::ltrim(m_data);

    bool percent_percent{false};
    auto closed_square_bracket_pos{std::string_view::npos};
    for (std::size_t index = 1; index < m_data.length(); ++index)
    {
        if (m_data[index] == bound_chars.second && !percent_percent)
        {
            closed_square_bracket_pos = index;
            break;
        }
        else if (m_data[index] == '%' && m_data[index - 1] == '%')
        {
            percent_percent = !percent_percent;
        }
    }

    if (closed_square_bracket_pos == std::string_view::npos)
    {
        std::string str{};
        str.push_back(bound_chars.second);
        throw Errors::buildMissingError(str);
    }

    auto const list_str{m_data.substr(0, closed_square_bracket_pos)};
    m_data.remove_prefix(closed_square_bracket_pos + 1);
    StringUtils::ltrim(m_data);

    return Utils::split(list_str, sep, Utils::ESplitModifier::EscapeQuotes, raw_percent_percent);
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
