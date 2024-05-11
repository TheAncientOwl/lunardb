#pragma once

#include "LunarDB/Common/CppExtensions/DefinePrimitive.hpp"

namespace LunarDB::QueryData::Primitives {

// clang-format off
DEFINE_LUNAR_PRIMITIVE(QueryType,
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
    Grant = 10,
    Revoke = 11,
    Commit = 12,
    Rollback = 13,
    SavePoint = 14,
    Database = 15,
    Rebind = 16,
    Schema = 17
)

DEFINE_LUNAR_PRIMITIVE(StructureType,
    None = 0,
    Table = 1,
    Collection = 2
)

DEFINE_LUNAR_PRIMITIVE(RenameType,
    None = 0,
    Structure = 1,
    Field = 2,
    Database = 3
)

DEFINE_LUNAR_PRIMITIVE(OrderType,
    None = 0,
    Asc = 1,
    Desc = 2
)

DEFINE_LUNAR_PRIMITIVE(UserPermissionType,
    None = 0,
    Create = 1,
    Update = 2,
    Insert = 3,
    Delete = 4,
    Select = 5
)

DEFINE_LUNAR_PRIMITIVE(DatabaseOperationType,
    None = 0,
    Create = 1,
    Drop = 2,
    Backup = 3,
    Use
)

DEFINE_LUNAR_PRIMITIVE(BinaryOperator,
    None = 0,
    Equals = 1,
    GreaterThan = 2,
    GreaterThanEqualTo = 3,
    LessThan = 4,
    LessThanEqualTo = 5,
    In = 6,
    Between = 7,
    Like = 8
)

DEFINE_LUNAR_PRIMITIVE(BooleanOperator,
    None = 0,
    And = 1,
    Or = 2
)
// clang-format on

} // namespace LunarDB::QueryData::Primitives
