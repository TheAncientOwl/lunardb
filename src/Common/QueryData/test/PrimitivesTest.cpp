#include <gtest/gtest.h>

#include "Primitives.hpp"

namespace LunarDB::QueryData::Primitives::Tests {

TEST(Common_QueryData_PrimitivesTest, QueryType)
{
    using namespace QueryType;

    EXPECT_EQ(EQueryType::None, toLiteral(toString(EQueryType::None)));
    EXPECT_EQ(EQueryType::Create, toLiteral(toString(EQueryType::Create)));
    EXPECT_EQ(EQueryType::Drop, toLiteral(toString(EQueryType::Drop)));
    EXPECT_EQ(EQueryType::Migrate, toLiteral(toString(EQueryType::Migrate)));
    EXPECT_EQ(EQueryType::Truncate, toLiteral(toString(EQueryType::Truncate)));
    EXPECT_EQ(EQueryType::Rename, toLiteral(toString(EQueryType::Rename)));
    EXPECT_EQ(EQueryType::Select, toLiteral(toString(EQueryType::Select)));
    EXPECT_EQ(EQueryType::Insert, toLiteral(toString(EQueryType::Insert)));
    EXPECT_EQ(EQueryType::Update, toLiteral(toString(EQueryType::Update)));
    EXPECT_EQ(EQueryType::Delete, toLiteral(toString(EQueryType::Delete)));
    EXPECT_EQ(EQueryType::Grant, toLiteral(toString(EQueryType::Grant)));
    EXPECT_EQ(EQueryType::Revoke, toLiteral(toString(EQueryType::Revoke)));
    EXPECT_EQ(EQueryType::Commit, toLiteral(toString(EQueryType::Commit)));
    EXPECT_EQ(EQueryType::Rollback, toLiteral(toString(EQueryType::Rollback)));
    EXPECT_EQ(EQueryType::SavePoint, toLiteral(toString(EQueryType::SavePoint)));
    EXPECT_EQ(EQueryType::Index, toLiteral(toString(EQueryType::Index)));
    EXPECT_EQ(EQueryType::Database, toLiteral(toString(EQueryType::Database)));
    EXPECT_EQ(EQueryType::Rebind, toLiteral(toString(EQueryType::Rebind)));
    EXPECT_EQ(EQueryType::Schema, toLiteral(toString(EQueryType::Schema)));
}

TEST(Common_QueryData_PrimitivesTest, StructureType)
{
    using namespace StructureType;

    EXPECT_EQ(EStructureType::None, toLiteral(toString(EStructureType::None)));
    EXPECT_EQ(EStructureType::Table, toLiteral(toString(EStructureType::Table)));
    EXPECT_EQ(EStructureType::Collection, toLiteral(toString(EStructureType::Collection)));
}

TEST(Common_QueryData_PrimitivesTest, RenameType)
{
    using namespace RenameType;

    EXPECT_EQ(ERenameType::None, toLiteral(toString(ERenameType::None)));
    EXPECT_EQ(ERenameType::Structure, toLiteral(toString(ERenameType::Structure)));
    EXPECT_EQ(ERenameType::Field, toLiteral(toString(ERenameType::Field)));
    EXPECT_EQ(ERenameType::Database, toLiteral(toString(ERenameType::Database)));
}

TEST(Common_QueryData_PrimitivesTest, OrderType)
{
    using namespace OrderType;

    EXPECT_EQ(EOrderType::None, toLiteral(toString(EOrderType::None)));
    EXPECT_EQ(EOrderType::Asc, toLiteral(toString(EOrderType::Asc)));
    EXPECT_EQ(EOrderType::Desc, toLiteral(toString(EOrderType::Desc)));
}

TEST(Common_QueryData_PrimitivesTest, UserPermissionType)
{
    using namespace UserPermissionType;

    EXPECT_EQ(EUserPermissionType::None, toLiteral(toString(EUserPermissionType::None)));
    EXPECT_EQ(EUserPermissionType::Create, toLiteral(toString(EUserPermissionType::Create)));
    EXPECT_EQ(EUserPermissionType::Update, toLiteral(toString(EUserPermissionType::Update)));
    EXPECT_EQ(EUserPermissionType::Insert, toLiteral(toString(EUserPermissionType::Insert)));
    EXPECT_EQ(EUserPermissionType::Delete, toLiteral(toString(EUserPermissionType::Delete)));
    EXPECT_EQ(EUserPermissionType::Select, toLiteral(toString(EUserPermissionType::Select)));
}

TEST(Common_QueryData_PrimitivesTest, DatabaseOperationType)
{
    using namespace DatabaseOperationType;

    EXPECT_EQ(EDatabaseOperationType::None, toLiteral(toString(EDatabaseOperationType::None)));
    EXPECT_EQ(EDatabaseOperationType::Create, toLiteral(toString(EDatabaseOperationType::Create)));
    EXPECT_EQ(EDatabaseOperationType::Drop, toLiteral(toString(EDatabaseOperationType::Drop)));
    EXPECT_EQ(EDatabaseOperationType::Backup, toLiteral(toString(EDatabaseOperationType::Backup)));
    EXPECT_EQ(EDatabaseOperationType::Use, toLiteral(toString(EDatabaseOperationType::Use)));
}

TEST(Common_QueryData_PrimitivesTest, BinaryOperator)
{
    using namespace BinaryOperator;

    EXPECT_EQ(EBinaryOperator::None, toLiteral(toString(EBinaryOperator::None)));
    EXPECT_EQ(EBinaryOperator::Equals, toLiteral(toString(EBinaryOperator::Equals)));
    EXPECT_EQ(EBinaryOperator::GreaterThan, toLiteral(toString(EBinaryOperator::GreaterThan)));
    EXPECT_EQ(
        EBinaryOperator::GreaterThanEqualTo, toLiteral(toString(EBinaryOperator::GreaterThanEqualTo)));
    EXPECT_EQ(EBinaryOperator::LessThan, toLiteral(toString(EBinaryOperator::LessThan)));
    EXPECT_EQ(EBinaryOperator::LessThanEqualTo, toLiteral(toString(EBinaryOperator::LessThanEqualTo)));
    EXPECT_EQ(EBinaryOperator::In, toLiteral(toString(EBinaryOperator::In)));
    EXPECT_EQ(EBinaryOperator::Between, toLiteral(toString(EBinaryOperator::Between)));
    EXPECT_EQ(EBinaryOperator::Like, toLiteral(toString(EBinaryOperator::Like)));
}

TEST(Common_QueryData_PrimitivesTest, BooleanOperator)
{
    using namespace BooleanOperator;

    EXPECT_EQ(EBooleanOperator::None, toLiteral(toString(EBooleanOperator::None)));
    EXPECT_EQ(EBooleanOperator::And, toLiteral(toString(EBooleanOperator::And)));
    EXPECT_EQ(EBooleanOperator::Or, toLiteral(toString(EBooleanOperator::Or)));
}

} // namespace LunarDB::QueryData::Primitives::Tests
