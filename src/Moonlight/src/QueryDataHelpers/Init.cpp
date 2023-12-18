#include "QueryDataHelpers/Init.hpp"

namespace LunarDB::Moonlight::QueryData::Init {

CreateInit::BindingInit& CreateInit::BindingInit::field(const std::string& value) { return base_t::field = value, *this; }
CreateInit::BindingInit& CreateInit::BindingInit::table(const std::string& value) { return base_t::table = value, *this; }

CreateInit& CreateInit::is_volatile(const bool& value) { return base_t::is_volatile = value, *this; }
CreateInit& CreateInit::structure_type(const Primitives::EStructureType& value) { return base_t::structure_type = value, *this; }
CreateInit& CreateInit::structure_name(const std::optional<std::string>& value) { return base_t::structure_name = value, *this; }
CreateInit& CreateInit::schema_name(const std::optional<std::string>& value) { return base_t::schema_name = value, *this; }
CreateInit& CreateInit::bindings(const std::optional<std::vector<Binding>>& value) { return base_t::bindings = value, *this; }
CreateInit& CreateInit::blended(const bool& value) { return base_t::blended = value, *this; }
CreateInit& CreateInit::schema_names(const std::optional<std::vector<std::string>>& value) { return base_t::schema_names = value, *this; }
CreateInit& CreateInit::structure_name_format(const std::optional<std::string>& value) { return base_t::structure_name_format = value, *this; }

DropInit& DropInit::structure_name(const std::string& value) { return base_t::structure_name = value, *this; }
DropInit& DropInit::cascade(const bool& value) { return base_t::cascade = value, *this; }

MigrateInit::MappingInit& MigrateInit::MappingInit::old_field(const std::string& value) { return base_t::old_field = value, *this; }
MigrateInit::MappingInit& MigrateInit::MappingInit::new_field(const std::string& value) { return base_t::new_field = value, *this; }

MigrateInit& MigrateInit::structure_name(const std::string& value) { return base_t::structure_name = value, *this; }
MigrateInit& MigrateInit::new_schema_name(const std::string& value) { return base_t::new_schema_name = value, *this; }
MigrateInit& MigrateInit::mappings(const std::optional<std::vector<Mapping>>& value) { return base_t::mappings = value, *this; }

TruncateInit& TruncateInit::structure_name(const std::string& value) { return base_t::structure_name = value, *this; }

RenameInit& RenameInit::type(const Primitives::ERenameType& value) { return base_t::type = value, *this; }
RenameInit& RenameInit::old_name(const std::string& value) { return base_t::old_name = value, *this; }
RenameInit& RenameInit::new_name(const std::string& value) { return base_t::new_name = value, *this; }

WhereClauseInit::BinaryExpressionInit& WhereClauseInit::BinaryExpressionInit::negated(const bool& value) { return base_t::negated = value, *this; }
WhereClauseInit::BinaryExpressionInit& WhereClauseInit::BinaryExpressionInit::lhs(const std::string& value) { return base_t::lhs = value, *this; }
WhereClauseInit::BinaryExpressionInit& WhereClauseInit::BinaryExpressionInit::rhs(const std::string& value) { return base_t::rhs = value, *this; }
WhereClauseInit::BinaryExpressionInit& WhereClauseInit::BinaryExpressionInit::operation(const Primitives::EBinaryOperator& value) { return base_t::operation = value, *this; }

WhereClauseInit::BooleanExpressionInit& WhereClauseInit::BooleanExpressionInit::negated(const bool& value) { return base_t::negated = value, *this; }
WhereClauseInit::BooleanExpressionInit& WhereClauseInit::BooleanExpressionInit::data(const std::vector<type>& value) { return base_t::data = value, *this; };

WhereClauseInit& WhereClauseInit::expression(const WhereClause::BooleanExpression& value) { return base_t::expression = value, *this; }

SelectInit::OrderInit& SelectInit::OrderInit::field(const std::string& value) { return base_t::field = value, *this; }
SelectInit::OrderInit& SelectInit::OrderInit::type(const Primitives::EOrderType& value) { return base_t::type = value, *this; }

SelectInit& SelectInit::from(const std::vector<std::string>& value) { return base_t::from = value, *this; }
SelectInit& SelectInit::where(const WhereClause& value) { return base_t::where = value, *this; }
SelectInit& SelectInit::fields(const std::vector<std::string>& value) { return base_t::fields = value, *this; }
SelectInit& SelectInit::order_by(const std::optional<std::vector<Order>>& value) { return base_t::order_by = value, *this; }

InsertInit& InsertInit::into(const std::string& value) { return base_t::into = value, *this; }
InsertInit& InsertInit::values(const std::vector<std::string>& value) { return base_t::values = value, *this; }

UpdateInit::ModifyInit& UpdateInit::ModifyInit::field(const std::string& value) { return base_t::field = value, *this; }
UpdateInit::ModifyInit& UpdateInit::ModifyInit::expression(const std::string& value) { return base_t::expression = value, *this; }

UpdateInit& UpdateInit::structure_name(const std::string& value) { return base_t::structure_name = value, *this; }
UpdateInit& UpdateInit::where(const WhereClause& value) { return base_t::where = value, *this; }
UpdateInit& UpdateInit::modify(const std::vector<Modify>& value) { return base_t::modify = value, *this; }

DeleteInit& DeleteInit::from(const std::string& value) { return base_t::from = value, *this; }
DeleteInit& DeleteInit::where(const WhereClause& value) { return base_t::where = value, *this; }

LockInit& LockInit::structure_name(const std::string& value) { return base_t::structure_name = value, *this; }
LockInit& LockInit::concurrency(const bool& value) { return base_t::concurrency = value, *this; }

GrantInit& GrantInit::permissions(const std::vector<Primitives::EUserPermissionType>& value) { return base_t::permissions = value, *this; }
GrantInit& GrantInit::to_user(const std::string& value) { return base_t::to_user = value, *this; }
GrantInit& GrantInit::structure_name(const std::optional<std::string>& value) { return base_t::structure_name = value, *this; }

RevokeInit& RevokeInit::permissions(const std::vector<Primitives::EUserPermissionType>& value) { return base_t::permissions = value, *this; }
RevokeInit& RevokeInit::from_user(const std::string& value) { return base_t::from_user = value, *this; }
RevokeInit& RevokeInit::structure_name(const std::optional<std::string>& value) { return base_t::structure_name = value, *this; }

CommitInit& CommitInit::hash(const std::optional<std::string>& value) { return base_t::hash = value, *this; }

RollbackInit& RollbackInit::hash(const std::optional<std::string>& value) { return base_t::hash = value, *this; }

SavePointInit& SavePointInit::hash(const std::optional<std::string>& value) { return base_t::hash = value, *this; }

IndexInit& IndexInit::on_structure_name(const std::string& value) { return base_t::on_structure_name = value, *this; }
IndexInit& IndexInit::unique(const bool& value) { return base_t::unique = value, *this; }
IndexInit& IndexInit::name(const std::optional<std::string>& value) { return base_t::name = value, *this; }
IndexInit& IndexInit::using_fields(const std::optional<std::vector<std::string>>& value) { return base_t::using_fields = value, *this; }

DatabaseInit& DatabaseInit::operation_type(const Primitives::EDatabaseOperationType& value) { return base_t::operation_type = value, *this; }
DatabaseInit& DatabaseInit::name(const std::string& value) { return base_t::name = value, *this; }
DatabaseInit& DatabaseInit::backup_path(const std::optional<std::string>& value) { return base_t::backup_path = value, *this; }

ViewInit& ViewInit::as_select(const Select& value) { return base_t::as_select = value, *this; }

RebindInit& RebindInit::structure_name(const std::string& value) { return base_t::structure_name = value, *this; }
RebindInit& RebindInit::field(const std::string& value) { return base_t::field = value, *this; }
RebindInit& RebindInit::bind_structure_name(const std::string& value) { return base_t::bind_structure_name = value, *this; }
RebindInit& RebindInit::clean(const std::optional<bool>& value) { return base_t::clean = value, *this; }

SchemaInit::FieldInit& SchemaInit::FieldInit::name(const std::string& value) { return base_t::name = value, *this; }
SchemaInit::FieldInit& SchemaInit::FieldInit::type(const std::string& value) { return base_t::type = value, *this; }
SchemaInit::FieldInit& SchemaInit::FieldInit::optional(const bool& value) { return base_t::optional, * this; };
SchemaInit::FieldInit& SchemaInit::FieldInit::array(const bool& value) { return base_t::array, * this; };

SchemaInit& SchemaInit::name(const std::string& value) { return base_t::name = value, *this; }
SchemaInit& SchemaInit::fields(const std::vector<Field>& value) { return base_t::fields = value, *this; }

} // namespace LunarDB::Moonlight::QueryData::Init
