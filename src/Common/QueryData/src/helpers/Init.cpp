#include "LunarDB/Common/QueryData/helpers/Init.hpp"

namespace LunarDB::Common::QueryData::Init {

CreateInit::SingleInit::BindingInit& CreateInit::SingleInit::BindingInit::field(const std::string& value)
{
    return base_t::field = value, *this;
}
CreateInit::SingleInit::BindingInit& CreateInit::SingleInit::BindingInit::table(const std::string& value)
{
    return base_t::table = value, *this;
}

CreateInit::SingleInit& CreateInit::SingleInit::structure_name(const std::string& value)
{
    return base_t::structure_name = value, *this;
}
CreateInit::SingleInit& CreateInit::SingleInit::schema_name(const std::string& value)
{
    return base_t::schema_name = value, *this;
}
CreateInit::SingleInit& CreateInit::SingleInit::bindings(const std::vector<Create::Single::Binding>& value)
{
    return base_t::bindings = value, *this;
}
CreateInit::SingleInit& CreateInit::SingleInit::blended(const bool& value)
{
    return base_t::blended = value, *this;
}

CreateInit::MultipleInit& CreateInit::MultipleInit::structure_name_format(const std::string& value)
{
    return base_t::structure_name_format = value, *this;
}
CreateInit::MultipleInit& CreateInit::MultipleInit::schema_names(const std::vector<std::string>& value)
{
    return base_t::schema_names = value, *this;
}

CreateInit& CreateInit::is_volatile(const bool& value)
{
    return base_t::is_volatile = value, *this;
}
CreateInit& CreateInit::structure_type(const Primitives::EStructureType& value)
{
    return base_t::structure_type = value, *this;
}
CreateInit& CreateInit::single(const std::optional<Create::Single>& value)
{
    return base_t::single = value, *this;
}
CreateInit& CreateInit::multiple(const std::optional<Create::Multiple>& value)
{
    return base_t::multiple = value, *this;
}

DropInit& DropInit::structure_name(const std::string& value)
{
    return base_t::structure_name = value, *this;
}
DropInit& DropInit::cascade(const bool& value)
{
    return base_t::cascade = value, *this;
}

MigrateInit::MappingInit& MigrateInit::MappingInit::old_field(const std::string& value)
{
    return base_t::old_field = value, *this;
}
MigrateInit::MappingInit& MigrateInit::MappingInit::new_field(const std::string& value)
{
    return base_t::new_field = value, *this;
}

MigrateInit& MigrateInit::structure_name(const std::string& value)
{
    return base_t::structure_name = value, *this;
}
MigrateInit& MigrateInit::new_schema_name(const std::string& value)
{
    return base_t::new_schema_name = value, *this;
}
MigrateInit& MigrateInit::mappings(const std::vector<Mapping>& value)
{
    return base_t::mappings = value, *this;
}

TruncateInit& TruncateInit::structure_name(const std::string& value)
{
    return base_t::structure_name = value, *this;
}

RenameInit& RenameInit::type(const Primitives::ERenameType& value)
{
    return base_t::type = value, *this;
}
RenameInit& RenameInit::old_name(const std::string& value)
{
    return base_t::old_name = value, *this;
}
RenameInit& RenameInit::new_name(const std::string& value)
{
    return base_t::new_name = value, *this;
}

WhereClauseInit::BinaryExpressionInit& WhereClauseInit::BinaryExpressionInit::negated(const bool& value)
{
    return base_t::negated = value, *this;
}
WhereClauseInit::BinaryExpressionInit& WhereClauseInit::BinaryExpressionInit::lhs(const std::string& value)
{
    return base_t::lhs = value, *this;
}
WhereClauseInit::BinaryExpressionInit& WhereClauseInit::BinaryExpressionInit::rhs(const std::string& value)
{
    return base_t::rhs = value, *this;
}
WhereClauseInit::BinaryExpressionInit& WhereClauseInit::BinaryExpressionInit::operation(
    const Primitives::EBinaryOperator& value)
{
    return base_t::operation = value, *this;
}

WhereClauseInit::BooleanExpressionInit& WhereClauseInit::BooleanExpressionInit::negated(const bool& value)
{
    return base_t::negated = value, *this;
}
WhereClauseInit::BooleanExpressionInit& WhereClauseInit::BooleanExpressionInit::data(
    const std::vector<type>& value)
{
    return base_t::data = value, *this;
};

WhereClauseInit& WhereClauseInit::expression(const WhereClause::BooleanExpression& value)
{
    return base_t::expression = value, *this;
}

SelectInit::OrderInit& SelectInit::OrderInit::field(const std::string& value)
{
    return base_t::field = value, *this;
}
SelectInit::OrderInit& SelectInit::OrderInit::type(const Primitives::EOrderType& value)
{
    return base_t::type = value, *this;
}

SelectInit& SelectInit::from(const std::string& value)
{
    return base_t::from = value, *this;
}
SelectInit& SelectInit::where(const WhereClause& value)
{
    return base_t::where = value, *this;
}
SelectInit& SelectInit::fields(const std::vector<std::string>& value)
{
    return base_t::fields = value, *this;
}
SelectInit& SelectInit::order_by(const std::vector<Order>& value)
{
    return base_t::order_by = value, *this;
}

InsertInit::ObjectInit& InsertInit::ObjectInit::entries(const std::map<std::string, type>& value)
{
    return base_t::entries = value, *this;
}

InsertInit& InsertInit::into(const std::string& value)
{
    return base_t::into = value, *this;
}
InsertInit& InsertInit::objects(const std::vector<InsertInit::Object>& value)
{
    return base_t::objects = value, *this;
}

UpdateInit::ModifyInit& UpdateInit::ModifyInit::field(const std::string& value)
{
    return base_t::field = value, *this;
}
UpdateInit::ModifyInit& UpdateInit::ModifyInit::expression(const std::string& value)
{
    return base_t::expression = value, *this;
}

UpdateInit& UpdateInit::structure_name(const std::string& value)
{
    return base_t::structure_name = value, *this;
}
UpdateInit& UpdateInit::where(const WhereClause& value)
{
    return base_t::where = value, *this;
}
UpdateInit& UpdateInit::modify(const std::vector<Modify>& value)
{
    return base_t::modify = value, *this;
}

DeleteInit& DeleteInit::from(const std::string& value)
{
    return base_t::from = value, *this;
}
DeleteInit& DeleteInit::where(const WhereClause& value)
{
    return base_t::where = value, *this;
}

GrantInit& GrantInit::permissions(const std::vector<Primitives::EUserPermissionType>& value)
{
    return base_t::permissions = value, *this;
}
GrantInit& GrantInit::to_user(const std::string& value)
{
    return base_t::to_user = value, *this;
}
GrantInit& GrantInit::structure_name(const std::optional<std::string>& value)
{
    return base_t::structure_name = value, *this;
}

RevokeInit& RevokeInit::permissions(const std::vector<Primitives::EUserPermissionType>& value)
{
    return base_t::permissions = value, *this;
}
RevokeInit& RevokeInit::from_user(const std::string& value)
{
    return base_t::from_user = value, *this;
}
RevokeInit& RevokeInit::structure_name(const std::optional<std::string>& value)
{
    return base_t::structure_name = value, *this;
}

RollbackInit& RollbackInit::hash(const std::optional<std::string>& value)
{
    return base_t::hash = value, *this;
}

SavePointInit& SavePointInit::hash(const std::optional<std::string>& value)
{
    return base_t::hash = value, *this;
}

DatabaseInit& DatabaseInit::operation_type(const Primitives::EDatabaseOperationType& value)
{
    return base_t::operation_type = value, *this;
}
DatabaseInit& DatabaseInit::name(const std::string& value)
{
    return base_t::name = value, *this;
}
DatabaseInit& DatabaseInit::backup_path(const std::optional<std::string>& value)
{
    return base_t::backup_path = value, *this;
}

RebindInit& RebindInit::structure_name(const std::string& value)
{
    return base_t::structure_name = value, *this;
}
RebindInit& RebindInit::field(const std::string& value)
{
    return base_t::field = value, *this;
}
RebindInit& RebindInit::bind_structure_name(const std::string& value)
{
    return base_t::bind_structure_name = value, *this;
}
RebindInit& RebindInit::clean(std::optional<bool> const& value)
{
    return base_t::clean = value, *this;
}

SchemaInit::FieldInit& SchemaInit::FieldInit::name(const std::string& value)
{
    return base_t::name = value, *this;
}
SchemaInit::FieldInit& SchemaInit::FieldInit::type(const std::string& value)
{
    return base_t::type = value, *this;
}
SchemaInit::FieldInit& SchemaInit::FieldInit::nullable(const bool& value)
{
    return base_t::nullable = value, *this;
};
SchemaInit::FieldInit& SchemaInit::FieldInit::array(const bool& value)
{
    return base_t::array = value, *this;
};

SchemaInit& SchemaInit::name(const std::string& value)
{
    return base_t::name = value, *this;
}
SchemaInit& SchemaInit::fields(const std::vector<Field>& value)
{
    return base_t::fields = value, *this;
}

} // namespace LunarDB::Common::QueryData::Init
