#include "QueryData.hpp"

#define PROVIDE_EQUALITY_OPERATOR(Type, ...) \
namespace LunarDB::Moonlight::QueryData { \
bool operator==(const Type& lhs, const Type& rhs) \
{ \
const auto reduce = [](const Type& obj) { return std::tie(__VA_ARGS__); }; \
return reduce(lhs) == reduce(rhs); \
} \
}

#define FIELD(field_name) obj.field_name

PROVIDE_EQUALITY_OPERATOR(Create::Binding,
    FIELD(field),
    FIELD(table)
)

PROVIDE_EQUALITY_OPERATOR(Create,
    FIELD(is_volatile),
    FIELD(structure_type),
    FIELD(structure_name),
    FIELD(schema_name),
    FIELD(bindings),
    FIELD(blended),
    FIELD(schema_names),
    FIELD(structure_name_format)
)

PROVIDE_EQUALITY_OPERATOR(Drop,
    FIELD(structure_name),
    FIELD(cascade)
)

PROVIDE_EQUALITY_OPERATOR(Migrate::Mapping,
    FIELD(old_field),
    FIELD(new_field)
)

PROVIDE_EQUALITY_OPERATOR(Migrate,
    FIELD(structure_name),
    FIELD(new_schema_name),
    FIELD(mappings)
)

PROVIDE_EQUALITY_OPERATOR(Truncate,
    FIELD(structure_name)
)

PROVIDE_EQUALITY_OPERATOR(Rename,
    FIELD(type),
    FIELD(old_name),
    FIELD(new_name)
)

// TODO: Provide detailed implementation
PROVIDE_EQUALITY_OPERATOR(WhereClause,
    FIELD(content)
)

PROVIDE_EQUALITY_OPERATOR(Select::Order,
    FIELD(field),
    FIELD(type)
)

PROVIDE_EQUALITY_OPERATOR(Select,
    FIELD(from),
    FIELD(where),
    FIELD(fields),
    FIELD(order_by)
)

PROVIDE_EQUALITY_OPERATOR(Insert,
    FIELD(into),
    FIELD(values)
)

PROVIDE_EQUALITY_OPERATOR(Update::Modify,
    FIELD(field),
    FIELD(expression)
)

PROVIDE_EQUALITY_OPERATOR(Update,
    FIELD(structure_name),
    FIELD(where),
    FIELD(modify)
)

PROVIDE_EQUALITY_OPERATOR(Delete,
    FIELD(from),
    FIELD(where)
)

PROVIDE_EQUALITY_OPERATOR(Lock,
    FIELD(structure_name),
    FIELD(concurrency)
)

PROVIDE_EQUALITY_OPERATOR(Grant,
    FIELD(permissions),
    FIELD(to_user),
    FIELD(structure_name)
)

PROVIDE_EQUALITY_OPERATOR(Revoke,
    FIELD(permissions),
    FIELD(from_user),
    FIELD(structure_name)
)

PROVIDE_EQUALITY_OPERATOR(Commit,
    FIELD(hash)
)

PROVIDE_EQUALITY_OPERATOR(Rollback,
    FIELD(hash)
)

PROVIDE_EQUALITY_OPERATOR(SavePoint,
    FIELD(hash)
)

PROVIDE_EQUALITY_OPERATOR(Index,
    FIELD(on_structure_name),
    FIELD(unique),
    FIELD(name),
    FIELD(using_fields)
)

PROVIDE_EQUALITY_OPERATOR(Database,
    FIELD(operation_type),
    FIELD(name),
    FIELD(backup_path)
)

PROVIDE_EQUALITY_OPERATOR(View,
    FIELD(as_select)
)

PROVIDE_EQUALITY_OPERATOR(Rebind,
    FIELD(structure_name),
    FIELD(field),
    FIELD(bind_structure_name),
    FIELD(clean)
)
