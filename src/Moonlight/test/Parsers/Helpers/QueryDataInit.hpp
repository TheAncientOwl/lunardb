#pragma once

#include "QueryData.hpp"

namespace LunarDB::Moonlight::QueryData::Init {

struct CreateInit : public Create
{
    using base_t = Create;

    CreateInit& is_volatile(const bool& value) { return base_t::is_volatile = value, *this; }
    CreateInit& structure_type(const Primitives::EStructureType& value) { return base_t::structure_type = value, *this; }

    struct BindingInit : public Binding
    {
        using base_t = Binding;

        BindingInit& field(const std::string& value) { return base_t::field = value, *this; }
        BindingInit& table(const std::string& value) { return base_t::table = value, *this; }
    };
    CreateInit& structure_name(const std::optional<std::string>& value) { return base_t::structure_name = value, *this; }
    CreateInit& schema_name(const std::optional<std::string>& value) { return base_t::schema_name = value, *this; }
    CreateInit& bindings(const std::optional<std::vector<Binding>>& value) { return base_t::bindings = value, *this; }
    CreateInit& blended(const bool& value) { return base_t::blended = value, *this; }

    CreateInit& schema_names(const std::optional<std::vector<std::string>>& value) { return base_t::schema_names = value, *this; }
    CreateInit& structure_name_format(const std::optional<std::string>& value) { return base_t::structure_name_format = value, *this; }
};

struct DropInit : public Drop
{
    using base_t = Drop;

    DropInit& structure_name(const std::string& value) { return base_t::structure_name = value, *this; }
    DropInit& cascade(const bool& value) { return base_t::cascade = value, *this; }
};

struct MigrateInit : public Migrate
{
    using base_t = Migrate;

    MigrateInit& structure_name(const std::string& value) { return base_t::structure_name = value, *this; }
    MigrateInit& new_schema_name(const std::string& value) { return base_t::new_schema_name = value, *this; }

    struct MappingInit : public Mapping
    {
        using base_t = Mapping;

        MappingInit& old_field(const std::string& value) { return base_t::old_field = value, *this; }
        MappingInit& new_field(const std::string& value) { return base_t::new_field = value, *this; }
    };
    MigrateInit& mappings(const std::optional<std::vector<Mapping>>& value) { return base_t::mappings = value, *this; }
};

struct TruncateInit : public Truncate
{
    using base_t = Truncate;

    TruncateInit& structure_name(const std::string& value) { return base_t::structure_name = value, *this; }
};

struct RenameInit : public Rename
{
    using base_t = Rename;

    RenameInit& type(const Primitives::ERenameType& value) { return base_t::type = value, *this; }
    RenameInit& old_name(const std::string& value) { return base_t::old_name = value, *this; }
    RenameInit& new_name(const std::string& value) { return base_t::new_name = value, *this; }
};

// TODO: Provide detailed implementation
struct IfConditionInit : public IfCondition
{
    using base_t = IfCondition;

    IfConditionInit& content(const std::string& value) { return base_t::content = value, *this; }
};

struct SelectInit : public Select
{
    using base_t = Select;

    SelectInit& from(const std::vector<std::string>& value) { return base_t::from = value, *this; }
    SelectInit& if_condition(const IfCondition& value) { return base_t::if_condition = value, *this; }
    SelectInit& fields(const std::vector<std::string>& value) { return base_t::fields = value, *this; }

    struct OrderInit : public Order
    {
        using base_t = Order;

        OrderInit& field(const std::string& value) { return base_t::field = value, *this; }
        OrderInit& type(const Primitives::EOrderType& value) { return base_t::type = value, *this; }
    };
    SelectInit& order_by(const std::optional<std::vector<Order>>& value) { return base_t::order_by = value, *this; }
};

struct InsertInit : public Insert
{
    using base_t = Insert;

    InsertInit& into(const std::string& value) { return base_t::into = value, *this; }
    InsertInit& values(const std::vector<std::string>& value) { return base_t::values = value, *this; }
};

struct UpdateInit : public Update
{
    using base_t = Update;

    UpdateInit& structure_name(const std::string& value) { return base_t::structure_name = value, *this; }
    UpdateInit& if_condition(const IfCondition& value) { return base_t::if_condition = value, *this; }

    struct ModifyInit : public Modify
    {
        using base_t = Modify;

        ModifyInit& field(const std::string& value) { return base_t::field = value, *this; }
        ModifyInit& expression(const std::string& value) { return base_t::expression = value, *this; }
    };
    UpdateInit& modify(const std::vector<Modify>& value) { return base_t::modify = value, *this; }
};

struct DeleteInit : public Delete
{
    using base_t = Delete;

    DeleteInit& from(const std::string& value) { return base_t::from = value, *this; }
    DeleteInit& if_condition(const IfCondition& value) { return base_t::if_condition = value, *this; }
};

struct LockInit : public Lock
{
    using base_t = Lock;

    LockInit& structure_name(const std::string& value) { return base_t::structure_name = value, *this; }
    LockInit& concurrency(const bool& value) { return base_t::concurrency = value, *this; }
};

struct GrantInit : public Grant
{
    using base_t = Grant;

    GrantInit& permissions(const std::vector<Primitives::EUserPermissionType>& value) { return base_t::permissions = value, *this; }
    GrantInit& to_user(const std::string& value) { return base_t::to_user = value, *this; }
    GrantInit& structure_name(const std::optional<std::string>& value) { return base_t::structure_name = value, *this; }
};

struct RevokeInit : public Revoke
{
    using base_t = Revoke;

    RevokeInit& permissions(const std::vector<Primitives::EUserPermissionType>& value) { return base_t::permissions = value, *this; }
    RevokeInit& from_user(const std::string& value) { return base_t::from_user = value, *this; }
    RevokeInit& structure_name(const std::optional<std::string>& value) { return base_t::structure_name = value, *this; }
};

struct CommitInit : public Commit
{
    using base_t = Commit;

    CommitInit& hash(const std::optional<std::string>& value) { return base_t::hash = value, *this; }
};

struct RollbackInit : public Rollback
{
    using base_t = Rollback;

    RollbackInit& hash(const std::optional<std::string>& value) { return base_t::hash = value, *this; }
};

struct SavePointInit : public SavePoint
{
    using base_t = SavePoint;

    SavePointInit& hash(const std::optional<std::string>& value) { return base_t::hash = value, *this; }
};

struct IndexInit : public Index
{
    using base_t = Index;

    IndexInit& on_structure_name(const std::string& value) { return base_t::on_structure_name = value, *this; }
    IndexInit& unique(const bool& value) { return base_t::unique = value, *this; }
    IndexInit& name(const std::optional<std::string>& value) { return base_t::name = value, *this; }
    IndexInit& using_fields(const std::optional<std::vector<std::string>>& value) { return base_t::using_fields = value, *this; }
};

struct DatabaseInit : public Database
{
    using base_t = Database;

    DatabaseInit& operation_type(const Primitives::EDatabaseOperationType& value) { return base_t::operation_type = value, *this; }
    DatabaseInit& name(const std::string& value) { return base_t::name = value, *this; }
    DatabaseInit& backup_path(const std::optional<std::string>& value) { return base_t::backup_path = value, *this; }
};

struct ViewInit : public View
{
    using base_t = View;

    ViewInit& as_select(const Select& value) { return base_t::as_select = value, *this; }
};

struct RebindInit : public Rebind
{
    using base_t = Rebind;

    RebindInit& structure_name(const std::string& value) { return base_t::structure_name = value, *this; }
    RebindInit& field(const std::string& value) { return base_t::field = value, *this; }
    RebindInit& bind_structure_name(const std::string& value) { return base_t::bind_structure_name = value, *this; }
    RebindInit clean(const std::optional<bool>& value) { return base_t::clean = value, *this; }
};

} // namespace LunarDB::Moonlight::QueryData::Init
