#pragma once

#include <string_view>
#include <vector>
#include <stdexcept>

#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

template<typename Literal>
class LiteralToStringMap
{
public:
    static_assert(std::is_enum<Literal>());

    using container = std::vector<std::pair<Literal, std::string_view>>;

public:
    LiteralToStringMap(container data);
    std::string_view findByLiteral(Literal literal) const;
    Literal findByString(std::string_view str) const;

private:
    container m_data;
};

template<typename Literal>
LiteralToStringMap<Literal>::LiteralToStringMap(LiteralToStringMap<Literal>::container data)
    : m_data(std::move(data))
{}

template<typename Literal>
std::string_view LiteralToStringMap<Literal>::findByLiteral(Literal literal) const
{
    const auto it = std::find_if(m_data.begin(), m_data.end(),
        [literal](const auto& value) {
            return value.first == literal;
        });

    if (it == m_data.end())
    {
        throw Utils::buildError("Cannot parse primitive from literal '", static_cast<std::uint8_t>(literal), "'");
    }

    return it->second;
}

template<typename Literal>
Literal LiteralToStringMap<Literal>::findByString(std::string_view str) const
{
    const auto it = std::find_if(m_data.begin(), m_data.end(),
        [&str](const auto& value) {
            return Utils::equalsIgnoreCase(value.second, str);
        });

    if (it == m_data.end())
    {
        throw Utils::buildError("Cannot parse primitive from string '", str, "'");
    }

    return it->first;
}

} // namespace LunarDB::Moonlight::Implementation
