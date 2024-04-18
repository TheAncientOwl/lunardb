#include "QueryParserTest.hpp"

#define QUERY_TYPE Lock

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

// clang-format off
TEST(Moonlight_LockParserTest, success01)
{
    const auto query = "set concurrency on structure StructureName on";
    const auto expected = Init::LockInit{}
        .structure_name("StructureName")
        .concurrency(true);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_LockParserTest, success02)
{
    const auto query = "set concurrency     \non  structure\n StructureName on     ;";
    const auto expected = Init::LockInit{}
        .structure_name("StructureName")
        .concurrency(true);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_LockParserTest, success03)
{
    const auto query = "set concurrency on structure StructureName off";
    const auto expected = Init::LockInit{}
        .structure_name("StructureName")
        .concurrency(false);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_LockParserTest, success04)
{
    const auto query = "    set  concurrency         on      structure      \n  StructureName   off  \n;     ";
    const auto expected = Init::LockInit{}
        .structure_name("StructureName")
        .concurrency(false);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_LockParserTest, fail01)
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
// clang-format on

} // namespace LunarDB::Moonlight::Implementation::Tests
