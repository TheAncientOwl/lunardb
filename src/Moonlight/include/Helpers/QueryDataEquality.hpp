#include "QueryData.hpp"

#define PROVIDE_EQUALITY_OPERATOR(Type, ...) \
namespace LunarDB::Moonlight::QueryData { \
bool operator==(const Type& lhs, const Type& rhs) \
{ \
const auto reduce = [](const Type& obj) { return std::tie(__VA_ARGS__); }; \
return reduce(lhs) == reduce(rhs); \
} \
}

// TODO: Provide struct fields
PROVIDE_EQUALITY_OPERATOR(Create)

// TODO: Provide struct fields
PROVIDE_EQUALITY_OPERATOR(Drop)

// TODO: Provide struct fields
PROVIDE_EQUALITY_OPERATOR(Migrate)

// TODO: Provide struct fields
PROVIDE_EQUALITY_OPERATOR(Truncate)

// TODO: Provide struct fields
PROVIDE_EQUALITY_OPERATOR(Rename)

// TODO: Provide struct fields
PROVIDE_EQUALITY_OPERATOR(Select)

// TODO: Provide struct fields
PROVIDE_EQUALITY_OPERATOR(Insert)

// TODO: Provide struct fields
PROVIDE_EQUALITY_OPERATOR(Update)

// TODO: Provide struct fields
PROVIDE_EQUALITY_OPERATOR(Delete)

// TODO: Provide struct fields
PROVIDE_EQUALITY_OPERATOR(Lock)

// TODO: Provide struct fields
PROVIDE_EQUALITY_OPERATOR(Grant)

// TODO: Provide struct fields
PROVIDE_EQUALITY_OPERATOR(Revoke)

// TODO: Provide struct fields
PROVIDE_EQUALITY_OPERATOR(Commit)

// TODO: Provide struct fields
PROVIDE_EQUALITY_OPERATOR(Rollback)

// TODO: Provide struct fields
PROVIDE_EQUALITY_OPERATOR(SavePoint)

// TODO: Provide struct fields
PROVIDE_EQUALITY_OPERATOR(Index)

// TODO: Provide struct fields(Database)
PROVIDE_EQUALITY_OPERATOR(View)

