#pragma once

#include "../QueryData.hpp"

#include <ostream>
#include <iterator>
#include <vector>

#define DEFINE_OPERATORS(Type) \
namespace LunarDB::Moonlight::QueryData { \
bool operator==(const Type& lhs, const Type& rhs); \
std::ostream& operator<<(std::ostream& os, const Type& rhs); \
}

namespace LunarDB::Moonlight::QueryData {

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::optional<T>& rhs)
{
    if (static_cast<bool>(rhs))
    {
        os << *rhs;
    }
    else
    {
        os << "---";
    }
    return os;
}

template<>
std::ostream& operator<<(std::ostream& os, const std::optional<bool>& rhs);

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& rhs)
{
    os << "[";
    std::copy(rhs.begin(), rhs.end(), std::ostream_iterator<T>(os, ", "));
    os << "]";
    return os;
}

} // namespace LunarDB::Moonlight::QueryData

DEFINE_OPERATORS(Create::Binding)
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
