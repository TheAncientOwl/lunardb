#pragma once

#include "Primitives.hpp"

#include <string>
#include <optional>
#include <vector>

namespace LunarDB::Moonlight::QueryData {

struct Create
{
    bool is_volatile;
    Primitives::EStructureType structure_type;

    struct Binding
    {
        std::string field;
        std::string table;
    };
    std::optional<std::string> structure_name;
    std::optional<std::string> schema_name;
    std::optional<std::vector<Binding>> bindings;
    std::optional<bool> blended;

    std::optional<std::vector<std::string>> schema_names;
    std::optional<std::string> structure_name_format;
};

struct Drop
{
    std::string structure_name;
    bool cascade;
};

struct Migrate
{
    std::string structure_name;
    std::string new_schema_name;

    struct Mapping
    {
        std::string old_field;
        std::string new_field;
    };
    std::optional<std::vector<Mapping>> mappings;
};

struct Truncate
{
    std::string structure_name;
};

struct Rename
{
    Primitives::ERenameType type;
    std::string old_name;
    std::string new_name;
};

// TODO: Provide detailed implementation
struct WhereClause
{
    std::string content;
};

struct Select
{
    std::vector<std::string> from;
    WhereClause where;
    std::vector<std::string> fields;

    struct Order
    {
        std::string field;
        Primitives::EOrderType type;
    };
    std::optional<std::vector<Order>> order_by;
};

struct Insert
{
    std::string into;
    std::vector<std::string> values;
};

struct Update
{
    std::string structure_name;
    WhereClause where;

    struct Modify
    {
        std::string field;
        std::string expression;
    };
    std::vector<Modify> modify;
};

struct Delete
{
    std::string from;
    WhereClause where;
};

struct Lock
{
    std::string structure_name;
    bool concurrency;
};

struct Grant
{
    std::vector<Primitives::EUserPermissionType> permissions;
    std::string to_user;
    std::optional<std::string> structure_name;
};

struct Revoke
{
    std::vector<Primitives::EUserPermissionType> permissions;
    std::string from_user;
    std::optional<std::string> structure_name;
};

struct Commit
{
    std::optional<std::string> hash;
};

struct Rollback
{
    std::optional<std::string> hash;
};

struct SavePoint
{
    std::optional<std::string> hash;
};

struct Index
{
    std::string on_structure_name;
    bool unique;
    std::optional<std::string> name;
    std::optional<std::vector<std::string>> using_fields;
};

struct Database
{
    Primitives::EDatabaseOperationType operation_type;
    std::string name;
    std::optional<std::string> backup_path;
};

struct View
{
    Select as_select;
};

struct Rebind
{
    std::string structure_name;
    std::string field;
    std::string bind_structure_name;
    std::optional<bool> clean;
};

struct Schema
{
    struct Field
    {
        std::string name;
        std::string type;
        bool optional;
        bool array;
    };

    std::string name;
    std::vector<Field> fields;
};

} // namespace LunarDB::Moonlight::QueryData
