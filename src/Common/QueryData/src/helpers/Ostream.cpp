#include <algorithm>
#include <iterator>

#include "Common/QueryData/helpers/Operators.hpp"

#define PROVIDE_OSTREAM_OUTPUT_OPERATOR(Type, ...)              \
    namespace LunarDB::QueryData {                              \
    std::ostream& operator<<(std::ostream& os, const Type& rhs) \
    {                                                           \
        __VA_ARGS__, std::ignore;                               \
        return os;                                              \
    }                                                           \
    }

#define FIELD_SEP(field_name) os << #field_name ": " << rhs.field_name << " | "
#define FIELD_BOOL_SEP(field_name) os << #field_name ": " << std::boolalpha << rhs.field_name << " | "

#define FIELD(field_name) os << #field_name ": " << rhs.field_name
#define FIELD_BOOL(field_name) os << #field_name ": " << std::boolalpha << rhs.field_name

namespace LunarDB::QueryData {

template <typename T>
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

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& rhs)
{
    os << "[";
    std::for_each(rhs.begin(), rhs.end(), [&os](const auto& val) { os << val << ", "; });
    os << "]";
    return os;
}

template <typename T, typename... Ts>
std::ostream& operator<<(std::ostream& os, const std::variant<T, Ts...>& rhs)
{
    std::visit([&os](auto&& arg) { os << arg; }, rhs);
    return os;
}

template <typename Key, typename Value>
std::ostream& operator<<(std::ostream& os, const std::map<Key, Value>& rhs)
{
    os << "{";
    for (const auto& [key, value] : rhs)
    {
        os << key << ": " << value << ", ";
    }
    os << "}";
    return os;
}

template <>
std::ostream& operator<<(std::ostream& os, const std::optional<bool>& rhs)
{
    if (static_cast<bool>(rhs))
    {
        os << std::boolalpha << *rhs;
    }
    else
    {
        os << "---";
    }
    return os;
}

} // namespace LunarDB::QueryData

// clang-format off
PROVIDE_OSTREAM_OUTPUT_OPERATOR(Create::Single::Binding,
    os << "{" << rhs.field << " from " << rhs.table << "}"
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(Create::Single,
    FIELD_SEP(structure_name),
    FIELD_SEP(schema_name),
    FIELD_SEP(bindings),
    FIELD_BOOL(blended)
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(Create::Multiple,
    FIELD_SEP(structure_name_format),
    FIELD(schema_names)
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(Create,
    FIELD_BOOL_SEP(is_volatile),
    FIELD_SEP(structure_type),
    FIELD_SEP(single),
    FIELD(multiple)
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(Drop,
    FIELD_SEP(structure_name),
    FIELD_BOOL(cascade)
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(Migrate::Mapping,
    os << "{" << rhs.old_field << " to " << rhs.new_field << "}"
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(Migrate,
    FIELD_SEP(structure_name),
    FIELD_SEP(new_schema_name),
    FIELD(mappings)
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(Truncate,
    FIELD(structure_name)
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(Rename,
    FIELD_SEP(type),
    FIELD_SEP(old_name),
    FIELD(new_name)
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(WhereClause::BinaryExpression,
    os << (rhs.negated ? "!" : "") << rhs.lhs << " " << rhs.operation << " " << rhs.rhs
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(WhereClause::BooleanExpression,
    os << (rhs.negated ? " !" : "") << "(",
    std::for_each(rhs.data.begin(), rhs.data.end(), [&os](const auto& data) { os << data << " "; }),
    os << ")"
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(WhereClause,
    FIELD(expression)
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(Select::Order,
    os << "{" << rhs.field << " -> " << rhs.type << "}"
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(Select,
    FIELD_SEP(from),
    FIELD_SEP(where),
    FIELD_SEP(fields),
    FIELD(order_by)
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(Insert::Object,
    os << "{ " << rhs.entries << " } "
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(Insert,
    FIELD_SEP(into),
    FIELD(objects)
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(Update::Modify,
    os << "{" << rhs.field << " => " << rhs.expression << "}"
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(Update,
    FIELD_SEP(structure_name),
    FIELD_SEP(where),
    FIELD(modify)
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(Delete,
    FIELD_SEP(from),
    FIELD(where)
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(Lock,
    FIELD_SEP(structure_name),
    FIELD_BOOL(concurrency)
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(Grant,
    FIELD_SEP(permissions),
    FIELD_SEP(to_user),
    FIELD(structure_name)
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(Revoke,
    FIELD_SEP(permissions),
    FIELD_SEP(from_user),
    FIELD(structure_name)
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(Commit,
    os << "commit"
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(Rollback,
    FIELD(hash)
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(SavePoint,
    FIELD(hash)
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(Index,
    FIELD_SEP(on_structure_name),
    FIELD_BOOL_SEP(unique),
    FIELD_SEP(name),
    FIELD(using_fields)
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(Database,
    FIELD_SEP(operation_type),
    FIELD_SEP(name),
    FIELD(backup_path)
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(View,
    FIELD_SEP(name),
    FIELD(as_select)
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(Rebind,
    FIELD_SEP(structure_name),
    FIELD_SEP(field),
    FIELD_SEP(bind_structure_name),
    FIELD(clean)
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(Schema::Field,
    FIELD_SEP(name),
    FIELD_SEP(type),
    FIELD_BOOL_SEP(nullable),
    FIELD_BOOL(array)
)

PROVIDE_OSTREAM_OUTPUT_OPERATOR(Schema,
    FIELD_SEP(name),
    FIELD(fields)
)
// clang-format on
