#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

#include "Common/CppExtensions/ItemArray.hpp"
#include "Common/CppExtensions/LiteralToStringMap.hpp"
#include "Common/QueryData/Primitives.hpp"

///
/// @brief Define enum Literal, toString, toLiteral, operator<<() under 'name' namespace.
///
#define DEFINE_LUNAR_PRIMITIVE(name, ...)                           \
    namespace name {                                                \
    enum class Literal : std::uint8_t                               \
    {                                                               \
        __VA_ARGS__                                                 \
    };                                                              \
    std::string_view toString(Literal primitive);                   \
    Literal toLiteral(std::string_view str);                        \
    std::ostream& operator<<(std::ostream& os, Literal const& rhs); \
    }                                                               \
    using E##name = name::Literal;

///
/// @brief Define implementation of toString, toLiteral, operator<<() under 'name::Internal' namespace.
///
#define DEFINE_LUNAR_PRIMITIVE_IMPL(name, ...)                                           \
    namespace name {                                                                     \
    namespace Internal {                                                                 \
    CppExtensions::DataStructures::LiteralToStringMap<Literal> const map{{__VA_ARGS__}}; \
    }                                                                                    \
    std::string_view toString(Literal literal)                                           \
    {                                                                                    \
        return Internal::map.findByLiteral(literal);                                     \
    }                                                                                    \
    Literal toLiteral(std::string_view str)                                              \
    {                                                                                    \
        return Internal::map.findByString(str);                                          \
    }                                                                                    \
    std::ostream& operator<<(std::ostream& os, Literal const& rhs)                       \
    {                                                                                    \
        return os << toString(rhs);                                                      \
    }                                                                                    \
    }
