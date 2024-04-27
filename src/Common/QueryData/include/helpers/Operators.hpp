#pragma once

#include <ostream>

#include "Common/QueryData/QueryData.hpp"

///
/// @brief Define operator==(Type, Type) and operator<<(ostream, Type) signatures.
///
#define DEFINE_OPERATORS(Type)                                   \
    namespace LunarDB::QueryData {                               \
    bool operator==(Type const& lhs, Type const& rhs);           \
    std::ostream& operator<<(std::ostream& os, const Type& rhs); \
    }

DEFINE_OPERATORS(Create::Single::Binding)
DEFINE_OPERATORS(Create::Single)
DEFINE_OPERATORS(Create::Multiple)
DEFINE_OPERATORS(Create)
DEFINE_OPERATORS(Drop)
DEFINE_OPERATORS(Migrate::Mapping)
DEFINE_OPERATORS(Migrate)
DEFINE_OPERATORS(Truncate)
DEFINE_OPERATORS(Rename)
DEFINE_OPERATORS(WhereClause::BinaryExpression)
DEFINE_OPERATORS(WhereClause::BooleanExpression)
DEFINE_OPERATORS(WhereClause)
DEFINE_OPERATORS(Select::Order)
DEFINE_OPERATORS(Select)
DEFINE_OPERATORS(Insert::Object)
DEFINE_OPERATORS(Insert)
DEFINE_OPERATORS(Update::Modify)
DEFINE_OPERATORS(Update)
DEFINE_OPERATORS(Delete)
DEFINE_OPERATORS(Lock)
DEFINE_OPERATORS(Grant)
DEFINE_OPERATORS(Revoke)
DEFINE_OPERATORS(Commit)
DEFINE_OPERATORS(Rollback)
DEFINE_OPERATORS(SavePoint)
DEFINE_OPERATORS(Index)
DEFINE_OPERATORS(Database)
DEFINE_OPERATORS(View)
DEFINE_OPERATORS(Rebind)
DEFINE_OPERATORS(Schema::Field)
DEFINE_OPERATORS(Schema)
