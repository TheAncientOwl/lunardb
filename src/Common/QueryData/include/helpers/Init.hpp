#pragma once

#include "QueryData/include/QueryData.hpp"

namespace LunarDB::QueryData::Init {

struct CreateInit : public Create
{
    using base_t = Create;

    struct SingleInit : public Single
    {
        using base_t = Single;

        struct BindingInit : public Binding
        {
            using base_t = Binding;

            BindingInit& field(const std::string_view& value);
            BindingInit& table(const std::string_view& value);
        };

        SingleInit& structure_name(const std::string_view& value);
        SingleInit& schema_name(const std::string_view& value);
        SingleInit& bindings(const std::vector<Binding>& value);
        SingleInit& blended(const bool& value);
    };

    struct MultipleInit : public Multiple
    {
        using base_t = Multiple;

        MultipleInit& structure_name_format(const std::string_view& value);
        MultipleInit& schema_names(const std::vector<std::string_view>& value);
    };

    CreateInit& is_volatile(const bool& value);
    CreateInit& structure_type(const Primitives::EStructureType& value);
    CreateInit& single(const std::optional<Single>& value);
    CreateInit& multiple(const std::optional<Multiple>& value);
};

struct DropInit : public Drop
{
    using base_t = Drop;

    DropInit& structure_name(const std::string_view& value);
    DropInit& cascade(const bool& value);
};

struct MigrateInit : public Migrate
{
    using base_t = Migrate;

    MigrateInit& structure_name(const std::string_view& value);
    MigrateInit& new_schema_name(const std::string_view& value);

    struct MappingInit : public Mapping
    {
        using base_t = Mapping;

        MappingInit& old_field(const std::string_view& value);
        MappingInit& new_field(const std::string_view& value);
    };
    MigrateInit& mappings(const std::vector<Mapping>& value);
};

struct TruncateInit : public Truncate
{
    using base_t = Truncate;

    TruncateInit& structure_name(const std::string_view& value);
};

struct RenameInit : public Rename
{
    using base_t = Rename;

    RenameInit& type(const Primitives::ERenameType& value);
    RenameInit& old_name(const std::string_view& value);
    RenameInit& new_name(const std::string_view& value);
};

struct WhereClauseInit : public WhereClause
{
    using base_t = WhereClause;

    struct BinaryExpressionInit : public BinaryExpression
    {
        using base_t = BinaryExpression;

        BinaryExpressionInit& negated(const bool& value);
        BinaryExpressionInit& lhs(const std::string_view& value);
        BinaryExpressionInit& rhs(const std::string_view& value);
        BinaryExpressionInit& operation(const Primitives::EBinaryOperator& value);
    };

    struct BooleanExpressionInit : public BooleanExpression
    {
        using base_t = BooleanExpression;

        BooleanExpressionInit& negated(const bool& value);
        BooleanExpressionInit& data(const std::vector<type>& value);
    };

    WhereClauseInit& expression(const WhereClause::BooleanExpression& value);
};

struct SelectInit : public Select
{
    using base_t = Select;

    SelectInit& from(const std::string_view& value);
    SelectInit& where(const WhereClause& value);
    SelectInit& fields(const std::vector<std::string_view>& value);

    struct OrderInit : public Order
    {
        using base_t = Order;

        OrderInit& field(const std::string_view& value);
        OrderInit& type(const Primitives::EOrderType& value);
    };
    SelectInit& order_by(const std::vector<Order>& value);
};

struct InsertInit : public Insert
{
    using base_t = Insert;

    struct ObjectInit : public Object
    {
        using base_t = Object;

        ObjectInit& entries(const std::map<std::string_view, type>& value);
    };

    InsertInit& into(const std::string_view& value);
    InsertInit& objects(const std::vector<Object>& value);
};

struct UpdateInit : public Update
{
    using base_t = Update;

    UpdateInit& structure_name(const std::string_view& value);
    UpdateInit& where(const WhereClause& value);

    struct ModifyInit : public Modify
    {
        using base_t = Modify;

        ModifyInit& field(const std::string_view& value);
        ModifyInit& expression(const std::string_view& value);
    };
    UpdateInit& modify(const std::vector<Modify>& value);
};

struct DeleteInit : public Delete
{
    using base_t = Delete;

    DeleteInit& from(const std::string_view& value);
    DeleteInit& where(const WhereClause& value);
};

struct LockInit : public Lock
{
    using base_t = Lock;

    LockInit& structure_name(const std::string_view& value);
    LockInit& concurrency(const bool& value);
};

struct GrantInit : public Grant
{
    using base_t = Grant;

    GrantInit& permissions(const std::vector<Primitives::EUserPermissionType>& value);
    GrantInit& to_user(const std::string_view& value);
    GrantInit& structure_name(const std::optional<std::string_view>& value);
};

struct RevokeInit : public Revoke
{
    using base_t = Revoke;

    RevokeInit& permissions(const std::vector<Primitives::EUserPermissionType>& value);
    RevokeInit& from_user(const std::string_view& value);
    RevokeInit& structure_name(const std::optional<std::string_view>& value);
};

struct CommitInit : public Commit
{
    using base_t = Commit;
};

struct RollbackInit : public Rollback
{
    using base_t = Rollback;

    RollbackInit& hash(const std::optional<std::string_view>& value);
};

struct SavePointInit : public SavePoint
{
    using base_t = SavePoint;

    SavePointInit& hash(const std::optional<std::string_view>& value);
};

struct IndexInit : public Index
{
    using base_t = Index;

    IndexInit& on_structure_name(const std::string_view& value);
    IndexInit& unique(const bool& value);
    IndexInit& name(const std::optional<std::string_view>& value);
    IndexInit& using_fields(const std::vector<std::string_view>& value);
};

struct DatabaseInit : public Database
{
    using base_t = Database;

    DatabaseInit& operation_type(const Primitives::EDatabaseOperationType& value);
    DatabaseInit& name(const std::string_view& value);
    DatabaseInit& backup_path(const std::optional<std::string_view>& value);
};

struct ViewInit : public View
{
    using base_t = View;

    ViewInit& name(const std::string_view& name);
    ViewInit& as_select(const Select& value);
};

struct RebindInit : public Rebind
{
    using base_t = Rebind;

    RebindInit& structure_name(const std::string_view& value);
    RebindInit& field(const std::string_view& value);
    RebindInit& bind_structure_name(const std::string_view& value);
    RebindInit& clean(const std::optional<bool>& value);
};

struct SchemaInit : public Schema
{
    using base_t = Schema;

    struct FieldInit : public Field
    {
        using base_t = Field;

        FieldInit& name(const std::string_view& value);
        FieldInit& type(const std::string_view& value);
        FieldInit& nullable(const bool& value);
        FieldInit& array(const bool& value);
    };

    SchemaInit& name(const std::string_view& value);
    SchemaInit& fields(const std::vector<Field>& value);
};

} // namespace LunarDB::QueryData::Init
