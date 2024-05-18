#pragma once

#include "LunarDB/Common/QueryData/QueryData.hpp"

namespace LunarDB::Common::QueryData::Init {

struct CreateInit : public Create
{
    using base_t = Create;

    struct SingleInit : public Single
    {
        using base_t = Single;

        struct BindingInit : public Binding
        {
            using base_t = Binding;

            BindingInit& field(std::string const& value);
            BindingInit& table(std::string const& value);
        };

        SingleInit& structure_name(std::string const& value);
        SingleInit& schema_name(std::string const& value);
        SingleInit& bindings(std::vector<Binding> const& value);
        SingleInit& blended(bool const& value);
    };

    struct MultipleInit : public Multiple
    {
        using base_t = Multiple;

        MultipleInit& structure_name_format(std::string const& value);
        MultipleInit& schema_names(std::vector<std::string> const& value);
    };

    CreateInit& is_volatile(bool const& value);
    CreateInit& structure_type(Primitives::EStructureType const& value);
    CreateInit& single(std::optional<Single> const& value);
    CreateInit& multiple(std::optional<Multiple> const& value);
};

struct DropInit : public Drop
{
    using base_t = Drop;

    DropInit& structure_name(std::string const& value);
    DropInit& cascade(bool const& value);
};

struct MigrateInit : public Migrate
{
    using base_t = Migrate;

    MigrateInit& structure_name(std::string const& value);
    MigrateInit& new_schema_name(std::string const& value);

    struct MappingInit : public Mapping
    {
        using base_t = Mapping;

        MappingInit& old_field(std::string const& value);
        MappingInit& new_field(std::string const& value);
    };
    MigrateInit& mappings(std::vector<Mapping> const& value);
};

struct TruncateInit : public Truncate
{
    using base_t = Truncate;

    TruncateInit& structure_name(std::string const& value);
};

struct RenameInit : public Rename
{
    using base_t = Rename;

    RenameInit& type(Primitives::ERenameType const& value);
    RenameInit& old_name(std::string const& value);
    RenameInit& new_name(std::string const& value);
};

struct WhereClauseInit : public WhereClause
{
    using base_t = WhereClause;

    struct BinaryExpressionInit : public BinaryExpression
    {
        using base_t = BinaryExpression;

        BinaryExpressionInit& negated(bool const& value);
        BinaryExpressionInit& lhs(std::string const& value);
        BinaryExpressionInit& rhs(std::string const& value);
        BinaryExpressionInit& operation(Primitives::EBinaryOperator const& value);
    };

    struct BooleanExpressionInit : public BooleanExpression
    {
        using base_t = BooleanExpression;

        BooleanExpressionInit& negated(bool const& value);
        BooleanExpressionInit& data(std::vector<type> const& value);
    };

    WhereClauseInit& expression(WhereClause::BooleanExpression const& value);
};

struct SelectInit : public Select
{
    using base_t = Select;

    SelectInit& from(std::string const& value);
    SelectInit& where(WhereClause const& value);
    SelectInit& fields(std::vector<std::string> const& value);

    struct OrderInit : public Order
    {
        using base_t = Order;

        OrderInit& field(std::string const& value);
        OrderInit& type(Primitives::EOrderType const& value);
    };
    SelectInit& order_by(std::vector<Order> const& value);
};

struct InsertInit : public Insert
{
    using base_t = Insert;

    struct ObjectInit : public Object
    {
        using base_t = Object;

        ObjectInit& entries(std::map<std::string, type> const& value);
    };

    InsertInit& into(std::string const& value);
    InsertInit& objects(std::vector<Object> const& value);
};

struct UpdateInit : public Update
{
    using base_t = Update;

    UpdateInit& structure_name(std::string const& value);
    UpdateInit& where(WhereClause const& value);

    struct ModifyInit : public Modify
    {
        using base_t = Modify;

        ModifyInit& field(std::string const& value);
        ModifyInit& expression(std::string const& value);
    };
    UpdateInit& modify(std::vector<Modify> const& value);
};

struct DeleteInit : public Delete
{
    using base_t = Delete;

    DeleteInit& from(std::string const& value);
    DeleteInit& where(WhereClause const& value);
};

struct GrantInit : public Grant
{
    using base_t = Grant;

    GrantInit& permissions(std::vector<Primitives::EUserPermissionType> const& value);
    GrantInit& to_user(std::string const& value);
    GrantInit& structure_name(std::optional<std::string> const& value);
};

struct RevokeInit : public Revoke
{
    using base_t = Revoke;

    RevokeInit& permissions(std::vector<Primitives::EUserPermissionType> const& value);
    RevokeInit& from_user(std::string const& value);
    RevokeInit& structure_name(std::optional<std::string> const& value);
};

struct CommitInit : public Commit
{
    using base_t = Commit;
};

struct RollbackInit : public Rollback
{
    using base_t = Rollback;

    RollbackInit& hash(std::optional<std::string> const& value);
};

struct SavePointInit : public SavePoint
{
    using base_t = SavePoint;

    SavePointInit& hash(std::optional<std::string> const& value);
};

struct DatabaseInit : public Database
{
    using base_t = Database;

    DatabaseInit& operation_type(const Primitives::EDatabaseOperationType& value);
    DatabaseInit& name(std::string const& value);
    DatabaseInit& backup_path(std::optional<std::string> const& value);
};

struct RebindInit : public Rebind
{
    using base_t = Rebind;

    RebindInit& structure_name(std::string const& value);
    RebindInit& field(std::string const& value);
    RebindInit& bind_structure_name(std::string const& value);
    RebindInit& clean(std::optional<bool> const& value);
};

struct SchemaInit : public Schema
{
    using base_t = Schema;

    struct FieldInit : public Field
    {
        using base_t = Field;

        FieldInit& name(std::string const& value);
        FieldInit& type(std::string const& value);
        FieldInit& nullable(bool const& value);
        FieldInit& array(bool const& value);
    };

    SchemaInit& name(std::string const& value);
    SchemaInit& fields(std::vector<Field> const& value);
};

struct UserInit : public User
{
    using base_t = User;

    UserInit& name(std::string const& value);
    UserInit& password(std::optional<std::string> const& value);
    UserInit& action(Primitives::EUserActionType const& value);
};

} // namespace LunarDB::Common::QueryData::Init
