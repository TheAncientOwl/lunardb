#pragma once

#include <algorithm>
#include <string_view>
#include <vector>
#include <stdexcept>

#include "Common/CppExtensions/StringUtils.hpp"

namespace LunarDB::CppExtensions::DataStructures {

template <typename T>
concept Enumeration = std::is_enum_v<T>;

template<Enumeration Literal>
class LiteralToStringMap
{
public:
    using container = std::vector<std::pair<Literal, std::string_view>>;

public: // methods
    LiteralToStringMap(container data);
    [[nodiscard]] std::string_view findByLiteral(Literal literal) const;
    [[nodiscard]] Literal findByString(std::string_view str) const;

private: // fields
    container m_data;
};

} // namespace LunarDB::CppExtensions::DataStructures

#include "Common/CppExtensions/private/LiteralToStringMap.inl"
