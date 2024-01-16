#pragma once

#include <map>
#include <optional>
#include <string_view>
#include <variant>
#include <vector>

#include "Primitives.hpp"
#include "simdjson/include/simdjson.hpp"

namespace LunarDB::QueryData {

struct Create
{
    struct Single
    {
        struct Binding
        {
            std::string_view field;
            std::string_view table;
        };

        std::string_view structure_name;
        std::string_view schema_name;
        std::vector<Binding> bindings;
        bool blended;
    };

    struct Multiple
    {
        std::string_view structure_name_format;
        std::vector<std::string_view> schema_names;
    };

    bool is_volatile;
    Primitives::EStructureType structure_type;
    std::optional<Single> single;
    std::optional<Multiple> multiple;
};

struct Drop
{
    std::string_view structure_name;
    bool cascade;
};

struct Migrate
{
    std::string_view structure_name;
    std::string_view new_schema_name;

    struct Mapping
    {
        std::string_view old_field;
        std::string_view new_field;
    };
    std::vector<Mapping> mappings;
};

struct Truncate
{
    std::string_view structure_name;
};

struct Rename
{
    Primitives::ERenameType type;
    std::string_view old_name;
    std::string_view new_name;
};

struct WhereClause
{
    struct BinaryExpression
    {
        bool negated; // TODO: remove
        std::string_view lhs;
        std::string_view rhs;
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
    std::string_view from;
    WhereClause where;
    std::vector<std::string_view> fields;

    struct Order
    {
        std::string_view field;
        Primitives::EOrderType type;
    };
    std::vector<Order> order_by;
};

struct Insert
{
    std::string_view into;

    struct Object
    {
        using type = std::variant<
            std::string_view,
            Object,
            std::vector<std::string_view>,
            std::vector<Object>
        >;

        std::map<std::string_view, type> entries;
    };

    struct InternalData
    {
        simdjson::ondemand::parser parser{};
        simdjson::ondemand::document_stream document_stream{};
    };

    std::vector<Object> objects;
    InternalData internal_data;
};

struct Update
{
    std::string_view structure_name;
    WhereClause where;

    struct Modify
    {
        std::string_view field;
        std::string_view expression;
    };
    std::vector<Modify> modify;
};

struct Delete
{
    std::string_view from;
    WhereClause where;
};

struct Lock
{
    std::string_view structure_name;
    bool concurrency;
};

struct Grant
{
    std::vector<Primitives::EUserPermissionType> permissions;
    std::string_view to_user;
    std::optional<std::string_view> structure_name;
};

struct Revoke
{
    std::vector<Primitives::EUserPermissionType> permissions;
    std::string_view from_user;
    std::optional<std::string_view> structure_name;
};

struct Commit {};

struct Rollback
{
    std::optional<std::string_view> hash;
};

struct SavePoint
{
    std::optional<std::string_view> hash;
};

struct Index
{
    std::string_view on_structure_name;
    bool unique;
    std::optional<std::string_view> name;
    std::vector<std::string_view> using_fields;
};

struct Database
{
    Primitives::EDatabaseOperationType operation_type;
    std::string_view name;
    std::optional<std::string_view> backup_path;
};

struct View
{
    std::string_view name;
    Select as_select;
};

struct Rebind
{
    std::string_view structure_name;
    std::string_view field;
    std::string_view bind_structure_name;
    std::optional<bool> clean;
};

struct Schema
{
    struct Field
    {
        std::string_view name;
        std::string_view type;
        bool nullable;
        bool array;
    };

    std::string_view name;
    std::vector<Field> fields;
};

} // namespace LunarDB::QueryData
