#include "QueryData.hpp"

#include <ostream>
#include <vector>

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

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& rhs)
{
    os << "[";
    std::copy(rhs.begin(), rhs.end(), std::ostream_iterator<T>(os));
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Create::Binding& rhs)
{
    return os << "{" << rhs.field << " from " << rhs.table << "}";
}

std::ostream& operator<<(std::ostream& os, const Create& rhs)
{
    return os
        << "volatile: " << std::boolalpha << rhs.is_volatile << " | "
        << "structure_type: " << rhs.structure_type << " | "
        << "structure_name: " << rhs.structure_name << " | "
        << "schema_name: " << rhs.schema_name << " | "
        << "bindings: " << rhs.bindings << " | "
        << "blended: " << rhs.blended << " | "
        << "schema_names: " << rhs.schema_names << " | "
        << "structure_name_format: " << rhs.structure_name_format;
}

std::ostream& operator<<(std::ostream& os, const Drop& rhs)
{
    return os
        << "structure_name: " << rhs.structure_name << " | "
        << "cascade: " << std::boolalpha << rhs.cascade;
}

std::ostream& operator<<(std::ostream& os, const Migrate::Mapping& rhs)
{
    return os << "{" << rhs.old_field << " to " << rhs.new_field << "}";
}

std::ostream& operator<<(std::ostream& os, const Migrate& rhs)
{
    return os
        << "structure_name: " << rhs.structure_name << " | "
        << "new_schema_name: " << rhs.new_schema_name << " | "
        << "mappings: " << rhs.mappings;
}

std::ostream& operator<<(std::ostream& os, const Truncate& rhs)
{
    return os << "structure_name: " << rhs.structure_name;
}

std::ostream& operator<<(std::ostream& os, const Rename& rhs)
{
    return os
        << "type: " << rhs.type << " | "
        << "old_name: " << rhs.old_name << " | "
        << "new_name: " << rhs.new_name;
}

// TODO: Provide detailed implementation
std::ostream& operator<<(std::ostream& os, const WhereClause& rhs)
{
    return os << rhs.content;
}

std::ostream& operator<<(std::ostream& os, const Select::Order& rhs)
{
    return os << "{" << rhs.field << " -> " << rhs.type << "}";
}

std::ostream& operator<<(std::ostream& os, const Select& rhs)
{
    return os
        << "from: " << rhs.from << " | "
        << "where: " << rhs.where << " | "
        << "fields: " << rhs.fields << " | "
        << "order_by: " << rhs.order_by;
}

std::ostream& operator<<(std::ostream& os, const Insert& rhs)
{
    return os
        << "into: " << rhs.into << " | "
        << "values: " << rhs.values;
}

std::ostream& operator<<(std::ostream& os, const Update::Modify& rhs)
{
    return os << "{" << rhs.field << " => " << rhs.expression << "}";
};

std::ostream& operator<<(std::ostream& os, const Update& rhs)
{
    return os
        << "structure_name: " << rhs.structure_name << " | "
        << "where: " << rhs.where << " | "
        << "modify: " << rhs.modify;
}

std::ostream& operator<<(std::ostream& os, const Delete& rhs)
{
    return os
        << "from: " << rhs.from << " | "
        << "where: " << rhs.where;
}

std::ostream& operator<<(std::ostream& os, const Lock& rhs)
{
    return os
        << "structure_name: " << rhs.structure_name << " | "
        << "concurrency: " << std::boolalpha << rhs.concurrency;
}

std::ostream& operator<<(std::ostream& os, const Grant& rhs)
{
    return os
        << "permissions: " << rhs.permissions << " | "
        << "to_user: " << rhs.to_user << " | "
        << "structure_name: " << rhs.structure_name;
}

std::ostream& operator<<(std::ostream& os, const Revoke& rhs)
{
    return os
        << "permissions: " << rhs.permissions << " | "
        << "to_user: " << rhs.from_user << " | "
        << "structure_name: " << rhs.structure_name;
}

std::ostream& operator<<(std::ostream& os, const Commit& rhs)
{
    return os << "hash: " << rhs.hash;
}

std::ostream& operator<<(std::ostream& os, const Rollback& rhs)
{
    return os << "hash: " << rhs.hash;
}

std::ostream& operator<<(std::ostream& os, const SavePoint& rhs)
{
    return os << "hash: " << rhs.hash;
}

std::ostream& operator<<(std::ostream& os, const Index& rhs)
{
    return os
        << "on_structure_name: " << rhs.on_structure_name << " | "
        << "name: " << rhs.unique << " | "
        << "name: " << rhs.name << " | "
        << "using_fields: " << rhs.using_fields;
}

std::ostream& operator<<(std::ostream& os, const Database& rhs)
{
    return os
        << "operation_type: " << rhs.operation_type << " | "
        << "name: " << rhs.name << " | "
        << "backup_path: " << rhs.backup_path;
}

std::ostream& operator<<(std::ostream& os, const View& rhs)
{
    return os << "as_select: " << rhs.as_select;
}

std::ostream& operator<<(std::ostream& os, const Rebind& rhs)
{
    return os
        << "structure_name: " << rhs.structure_name << " | "
        << "field: " << rhs.field << " | "
        << "bind_structure_name: " << rhs.bind_structure_name << " | "
        << "clean: " << rhs.clean;
}

std::ostream& operator<<(std::ostream& os, const Schema::Field& rhs)
{
    return os
        << "name: " << rhs.name << " | "
        << "type: " << rhs.type << " | "
        << "optional: " << std::boolalpha << rhs.optional << " | "
        << "array: " << std::boolalpha << rhs.array;
}

std::ostream& operator<<(std::ostream& os, const Schema& rhs)
{
    return os
        << "name: " << rhs.name << " | "
        << "fields: " << rhs.fields;
}

} // namespace LunarDB::Moonlight::QueryData
