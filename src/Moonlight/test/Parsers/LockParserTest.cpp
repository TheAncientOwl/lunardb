#include <gtest/gtest.h>

#include "QueryDataHelpers/Helpers.hpp"
#include "ParsedQuery.hpp"

#define EXPECT_SUCCESS(query, expected) \
    const auto out = API::ParsedQuery::from(query).get<Lock>(); \
    EXPECT_EQ(out, expected)

#define EXPECT_FAIL(query) \
    EXPECT_THROW(API::ParsedQuery::from(query).get<Lock>(), std::runtime_error)


namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

TEST(LockParserTest, success01)
{
    const auto query = "set concurrency on structure StructureName on";
    const auto expected = Init::LockInit{}
        .structure_name("StructureName")
        .concurrency(true);

    EXPECT_SUCCESS(query, expected);
}

TEST(LockParserTest, success02)
{
    const auto query = "set concurrency     \non  structure\n StructureName on     ;";
    const auto expected = Init::LockInit{}
        .structure_name("StructureName")
        .concurrency(true);

    EXPECT_SUCCESS(query, expected);
}

TEST(LockParserTest, success03)
{
    const auto query = "set concurrency on structure StructureName off";
    const auto expected = Init::LockInit{}
        .structure_name("StructureName")
        .concurrency(true);

    EXPECT_SUCCESS(query, expected);
}

TEST(LockParserTest, success04)
{
    const auto query = "    set  concurrency         on      structure      \n  StructureName   off  \n;     ";
    const auto expected = Init::LockInit{}
        .structure_name("StructureName")
        .concurrency(true);

    EXPECT_SUCCESS(query, expected);
}

TEST(LockParserTest, fail01)
{
    EXPECT_FAIL("set concurrency on structure StructureName");
    EXPECT_FAIL("set concurrency on structure StructureName;");
    EXPECT_FAIL("set concurrency on StructureName on");
    EXPECT_FAIL("set concurrency on StructureName on;");
    EXPECT_FAIL("set concurrency on structure on");
    EXPECT_FAIL("set concurrency on structure on;");
    EXPECT_FAIL("set concurrency on StructureName off");
    EXPECT_FAIL("set concurrency on StructureName off;");
    EXPECT_FAIL("set concurrency on structure off");
    EXPECT_FAIL("set concurrency on structure off;");
}

} // namespace LunarDB::Moonlight::Implementation::Tests
