#pragma once

#include <cstdint>

#include "LunarDB/Common/CppExtensions/LiteralToStringMap.hpp"

namespace LunarDB::CppExtensions::DataStructures {

template <Enumeration Literal>
LiteralToStringMap<Literal>::LiteralToStringMap(LiteralToStringMap<Literal>::container data)
    : m_data(std::move(data))
{
}

template <Enumeration Literal>
std::string_view LiteralToStringMap<Literal>::findByLiteral(Literal literal) const
{
    // clang-format off
    auto const it = std::find_if(m_data.begin(), m_data.end(),
        [literal](auto const& value) {
            return value.first == literal;
        });
    // clang-format on

    if (it == m_data.end())
    {
        throw std::runtime_error{StringUtils::stringify(
            "Cannot parse primitive from literal '", static_cast<std::uint8_t>(literal), "'")};
    }

    return it->second;
}

template <Enumeration Literal>
Literal LiteralToStringMap<Literal>::findByString(std::string_view str) const
{
    // clang-format off
    auto const it = std::find_if(m_data.begin(), m_data.end(),
        [&str](auto const& value) {
            return StringUtils::equalsIgnoreCase(value.second, str);
        });
    // clang-format on

    if (it == m_data.end())
    {
        throw std::runtime_error{
            StringUtils::stringify("Cannot parse primitive from string '", str, "'")};
    }

    return it->first;
}

} // namespace LunarDB::CppExtensions::DataStructures
