#include <gtest/gtest.h>

#include <Primitives.hpp>

namespace LunarDB::Moonlight::QueryData::Primitives::Tests {

TEST(PrimitivesTest, QueryType)
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
    EXPECT_EQ(EQueryType::Lock, toLiteral(toString(EQueryType::Lock)));
    EXPECT_EQ(EQueryType::Grant, toLiteral(toString(EQueryType::Grant)));
    EXPECT_EQ(EQueryType::Revoke, toLiteral(toString(EQueryType::Revoke)));
    EXPECT_EQ(EQueryType::Commit, toLiteral(toString(EQueryType::Commit)));
    EXPECT_EQ(EQueryType::Rollback, toLiteral(toString(EQueryType::Rollback)));
    EXPECT_EQ(EQueryType::SavePoint, toLiteral(toString(EQueryType::SavePoint)));
    EXPECT_EQ(EQueryType::Index, toLiteral(toString(EQueryType::Index)));
    EXPECT_EQ(EQueryType::Database, toLiteral(toString(EQueryType::Database)));
    EXPECT_EQ(EQueryType::View, toLiteral(toString(EQueryType::View)));
}

} // namespace LunarDB::Moonlight::QueryData::Primitives::Tests
