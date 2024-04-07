#pragma once

#include <cstdint>

#include "Common/CppExtensions/LiteralToStringMap.hpp"

namespace LunarDB::CppExtensions::DataStructures {

template<Enumeration Literal>
LiteralToStringMap<Literal>::LiteralToStringMap(LiteralToStringMap<Literal>::container data)
    : m_data(std::move(data))
{}

template<Enumeration Literal>
std::string_view LiteralToStringMap<Literal>::findByLiteral(Literal literal) const
{
    const auto it = std::find_if(m_data.begin(), m_data.end(),
        [literal](const auto& value) {
            return value.first == literal;
        });

    if (it == m_data.end())
    {
        throw std::runtime_error{ StringUtils::stringify("Cannot parse primitive from literal '", static_cast<std::uint8_t>(literal), "'") };
    }

    return it->second;
}

template<Enumeration Literal>
Literal LiteralToStringMap<Literal>::findByString(std::string_view str) const
{
    const auto it = std::find_if(m_data.begin(), m_data.end(),
        [&str](const auto& value) {
            return StringUtils::equalsIgnoreCase(value.second, str);
        });

    if (it == m_data.end())
    {
        throw std::runtime_error{ StringUtils::stringify("Cannot parse primitive from string '", str, "'") };
    }

    return it->first;
}

} // namespace LunarDB::CppExtensions::DataStructures
