#pragma once

#include <string_view>
#include <ostream>

#define DEFINE_MOONLIGHT_PRIMITIVE(name, ...) \
namespace name { \
    enum class Literal : std::uint8_t \
    { \
        __VA_ARGS__ \
    }; \
    std::string_view toString(Literal primitive); \
    Literal toLiteral(std::string_view str); \
    std::ostream& operator<<(std::ostream& os, const Literal& rhs); \
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
    View = 18,
    Rebind = 19,
    Schema = 20
)

DEFINE_MOONLIGHT_PRIMITIVE(StructureType,
    None = 0,
    Table = 1,
    Collection = 2
)

DEFINE_MOONLIGHT_PRIMITIVE(RenameType,
    None = 0,
    Structure = 1,
    Field = 2,
    Database = 3
)

DEFINE_MOONLIGHT_PRIMITIVE(OrderType,
    None = 0,
    Asc = 1,
    Desc = 2
)

DEFINE_MOONLIGHT_PRIMITIVE(UserPermissionType,
    None = 0,
    Create = 1,
    Update = 2,
    Insert = 3,
    Delete = 4,
    Select = 5
)

DEFINE_MOONLIGHT_PRIMITIVE(DatabaseOperationType,
    None = 0,
    Create = 1,
    Drop = 2,
    Backup = 3,
    Use
)

DEFINE_MOONLIGHT_PRIMITIVE(DataType,
    None = 0,
    Rid = 1,
    String = 2,
    Boolean = 3,
    DateTime = 4,
    Integer = 5,
    Integer8 = 6,
    Integer16 = 7,
    Integer32 = 8,
    Integer64 = 9,
    Float = 10,
    Float32 = 11,
    Float64 = 12
)

} // namespace LunarDB::Moonlight::QueryData::Primitives
