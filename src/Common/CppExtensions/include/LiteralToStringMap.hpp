#pragma once

#include <algorithm>
#include <stdexcept>
#include <string_view>
#include <vector>

#include "Common/CppExtensions/StringUtils.hpp"

namespace LunarDB::CppExtensions::DataStructures {

///
/// @brief Concept to enforce a type to be enum.
///
template <typename T>
concept Enumeration = std::is_enum_v<T>;

///
/// @brief Utility class to map literals to string representation.
/// @tparam Literal Enum type
///
template <Enumeration Literal>
class LiteralToStringMap
{
public:
    using container = std::vector<std::pair<Literal, std::string_view>>;

public: // methods
    ///
    /// @brief Self explanatory.
    ///
    LiteralToStringMap(container data);

    ///
    /// @brief Self explanatory.
    /// @throw std::runtime_error if Literal not found in init data from @c LiteralToStringMap(data)
    ///
    [[nodiscard]] std::string_view findByLiteral(Literal literal) const;

    ///
    /// @brief Self explanatory.
    /// @throw std::runtime_error if Literal not found in init data from @c LiteralToStringMap(data)
    ///
    [[nodiscard]] Literal findByString(std::string_view str) const;

private: // fields
    container m_data;
};

} // namespace LunarDB::CppExtensions::DataStructures

#include "Common/CppExtensions/private/LiteralToStringMap.inl"
