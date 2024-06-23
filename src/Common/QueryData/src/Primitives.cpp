#include "LunarDB/Common/QueryData/Primitives.hpp"

namespace LunarDB::Common::QueryData::Primitives {

// clang-format off
DEFINE_LUNAR_PRIMITIVE_IMPL(QueryType,
    { Literal::None, "None" },
    { Literal::Create, "Create" },
    { Literal::Drop, "Drop" },
    { Literal::Migrate, "Migrate" },
    { Literal::Truncate, "Truncate" },
    { Literal::Rename, "Rename" },
    { Literal::Select, "Select" },
    { Literal::Insert, "Insert" },
    { Literal::Update, "Update" },
    { Literal::Delete, "Delete" },
    { Literal::Grant, "Grant" },
    { Literal::Revoke, "Revoke" },
    { Literal::Commit, "Commit" },
    { Literal::Rollback, "Rollback" },
    { Literal::SavePoint, "SavePoint" },
    { Literal::Database, "Database" },
    { Literal::Rebind, "Rebind" },
    { Literal::Schema, "Schema" },
    { Literal::User, "User" },
    { Literal::Auth, "Auth" }
)

DEFINE_LUNAR_PRIMITIVE_IMPL(StructureType,
    { Literal::None, "None" },
    { Literal::Table, "Table" },
    { Literal::Collection, "Collection" }
)

DEFINE_LUNAR_PRIMITIVE_IMPL(RenameType,
    { Literal::None, "None" },
    { Literal::Structure, "Structure" },
    { Literal::Field, "Field" },
    { Literal::Database, "Database" }
)

DEFINE_LUNAR_PRIMITIVE_IMPL(OrderType,
    { Literal::None, "None" },
    { Literal::Asc, "Asc" },
    { Literal::Desc, "Desc" }
)

DEFINE_LUNAR_PRIMITIVE_IMPL(UserPermissionType,
    { Literal::None, "None" },
    { Literal::Migrate, "Migrate" },
    { Literal::Truncate, "Truncate" },
    { Literal::Rename, "Rename" },
    { Literal::Select, "Select" },
    { Literal::Insert, "Insert" },
    { Literal::Update, "Update" },
    { Literal::Delete, "Delete" },
)

DEFINE_LUNAR_PRIMITIVE_IMPL(DatabaseOperationType,
    { Literal::None, "None" },
    { Literal::Create, "Create" },
    { Literal::Drop, "Drop" },
    { Literal::Backup, "Backup" },
    { Literal::Use, "Use" }
)

DEFINE_LUNAR_PRIMITIVE_IMPL(BinaryOperator,
    { Literal::None, "None" },
    { Literal::Equals, "==" },
    { Literal::GreaterThan, ">" },
    { Literal::GreaterThanEqualTo, ">=" },
    { Literal::LessThan, "<" },
    { Literal::LessThanEqualTo, "<=" },
    { Literal::In, "in" },
    { Literal::Between, "between" },
    { Literal::Like, "like" }
)

DEFINE_LUNAR_PRIMITIVE_IMPL(BooleanOperator,
    { Literal::None, "None" },
    { Literal::And, "and" },
    { Literal::Or, "or" }
)

DEFINE_LUNAR_PRIMITIVE_IMPL(UserActionType,
    { Literal::None, "None" },
    { Literal::Create, "Create" },
    { Literal::Remove, "Remove" }
)
// clang-format on

} // namespace LunarDB::Common::QueryData::Primitives
