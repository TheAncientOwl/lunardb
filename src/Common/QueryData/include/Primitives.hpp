#pragma once

#include "Common/CppExtensions/DefinePrimitive.hpp"

namespace LunarDB::QueryData::Primitives {

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

} // namespace LunarDB::QueryData::Primitives
