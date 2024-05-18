#include <tuple>

#include "LunarDB/Common/QueryData/helpers/Operators.hpp"

#define PROVIDE_EQUALITY_OPERATOR(Type, ...)                                       \
    namespace LunarDB::Common::QueryData {                                         \
    bool operator==(Type const& lhs, Type const& rhs)                              \
    {                                                                              \
        auto const reduce = [](Type const& obj) { return std::tie(__VA_ARGS__); }; \
        return reduce(lhs) == reduce(rhs);                                         \
    }                                                                              \
    }

#define FIELD(field_name) obj.field_name

// clang-format off
PROVIDE_EQUALITY_OPERATOR(Create::Single::Binding,
    FIELD(field),
    FIELD(table)
)

PROVIDE_EQUALITY_OPERATOR(Create::Single,
    FIELD(structure_name),
    FIELD(schema_name),
    FIELD(bindings),
    FIELD(blended)
)

PROVIDE_EQUALITY_OPERATOR(Create::Multiple,
    FIELD(structure_name_format),
    FIELD(schema_names)
)

PROVIDE_EQUALITY_OPERATOR(Create,
    FIELD(is_volatile),
    FIELD(structure_type),
    FIELD(single),
    FIELD(multiple)
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

PROVIDE_EQUALITY_OPERATOR(WhereClause::BinaryExpression,
    FIELD(negated),
    FIELD(lhs),
    FIELD(rhs),
    FIELD(operation)
)

PROVIDE_EQUALITY_OPERATOR(WhereClause::BooleanExpression,
    FIELD(negated),
    FIELD(data)
)

PROVIDE_EQUALITY_OPERATOR(WhereClause,
    FIELD(expression)
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

PROVIDE_EQUALITY_OPERATOR(Insert::Object,
    FIELD(entries)
)

PROVIDE_EQUALITY_OPERATOR(Insert,
    FIELD(into),
    FIELD(objects)
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

PROVIDE_EQUALITY_OPERATOR(Commit)

PROVIDE_EQUALITY_OPERATOR(Rollback,
    FIELD(hash)
)

PROVIDE_EQUALITY_OPERATOR(SavePoint,
    FIELD(hash)
)

PROVIDE_EQUALITY_OPERATOR(Database,
    FIELD(operation_type),
    FIELD(name),
    FIELD(backup_path)
)

PROVIDE_EQUALITY_OPERATOR(Rebind,
    FIELD(structure_name),
    FIELD(field),
    FIELD(bind_structure_name),
    FIELD(clean)
)

PROVIDE_EQUALITY_OPERATOR(Schema::Field,
    FIELD(name),
    FIELD(type),
    FIELD(nullable),
    FIELD(array)
)

PROVIDE_EQUALITY_OPERATOR(Schema,
    FIELD(name),
    FIELD(fields)
)

PROVIDE_EQUALITY_OPERATOR(User,
    FIELD(name),
    FIELD(password),
    FIELD(action)
)
// clang-format on
