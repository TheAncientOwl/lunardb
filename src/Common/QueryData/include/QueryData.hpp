#pragma once

#include <map>
#include <optional>
#include <string>
#include <variant>
#include <vector>

#include "Primitives.hpp"

namespace LunarDB::QueryData {

struct Create
{
    struct Single
    {
        struct Binding
        {
            std::string field;
            std::string table;
        };

        std::string structure_name;
        std::string schema_name;
        std::vector<Binding> bindings;
        bool blended;
    };

    struct Multiple
    {
        std::string structure_name_format;
        std::vector<std::string> schema_names;
    };

    bool is_volatile;
    Primitives::EStructureType structure_type;
    std::optional<Single> single;
    std::optional<Multiple> multiple;
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
    std::vector<Mapping> mappings;
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

struct WhereClause
{
    struct BinaryExpression
    {
        bool negated; // TODO: remove
        std::string lhs;
        std::string rhs;
        Primitives::EBinaryOperator operation;
    };

    struct BooleanExpression
    {
        using type = std::variant<
            Primitives::EBooleanOperator,
            BinaryExpression,
            BooleanExpression
        >;

        bool negated;
        std::vector<type> data;
    };

    BooleanExpression expression;
};

struct Select
{
    std::string from;
    WhereClause where;
    std::vector<std::string> fields;

    struct Order
    {
        std::string field;
        Primitives::EOrderType type;
    };
    std::vector<Order> order_by;
};

struct Insert
{
    std::string into;

    struct Object
    {
        using type = std::variant<
            std::string,
            Object,
            std::vector<std::string>,
            std::vector<Object>
        >;

        std::map<std::string, type> entries;
    };

    std::vector<Object> objects;
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

struct Commit {};

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
    std::vector<std::string> using_fields;
};

struct Database
{
    Primitives::EDatabaseOperationType operation_type;
    std::string name;
    std::optional<std::string> backup_path;
};

struct View
{
    std::string name;
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
        bool nullable;
        bool array;
    };

    std::string name;
    std::vector<Field> fields;
};

} // namespace LunarDB::QueryData
