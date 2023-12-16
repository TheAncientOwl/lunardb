#pragma once

#include <string_view>

#define DEFINE_MOONLIGHT_PRIMITIVE(name, ...) \
namespace name { \
    enum class Literal : std::uint8_t \
    { \
        __VA_ARGS__ \
    }; \
    std::string_view toString(Literal primitive); \
    Literal toLiteral(std::string_view str); \
} \
using E ## name = name::Literal;

namespace LunarDB::Moonlight::QueryData::Primitives {

DEFINE_MOONLIGHT_PRIMITIVE(QueryType,
    None = 0,
    Create = 1,
    Drop = 2,
    Migrate = 3,
    Truncate = 4,
    Rename = 5,
    Select = 6,
    Insert = 7,
    Update = 8,
    Delete = 9,
    Lock = 10,
    Grant = 11,
    Revoke = 12,
    Commit = 13,
    Rollback = 14,
    SavePoint = 15,
    Index = 16,
    Database = 17,
    View = 18
)

} // namespace LunarDB::Moonlight::QueryData::Primitives
