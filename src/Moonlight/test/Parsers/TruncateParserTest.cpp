#include "QueryParserTest.hpp"

#define QUERY_TYPE Truncate

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

// clang-format off
TEST(Moonlight_TruncateParserTest, success01)
{
    const auto query = "truncate structure SomeStructure";
    const auto expected = Init::TruncateInit{}
    .structure_name("SomeStructure");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_TruncateParserTest, success02)
{
    const auto query = "truncate structure SomeStructure;";
    const auto expected = Init::TruncateInit{}
    .structure_name("SomeStructure");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_TruncateParserTest, success03)
{
    const auto query = "    truncate         structure   SomeStructure    ";
    const auto expected = Init::TruncateInit{}
    .structure_name("SomeStructure");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_TruncateParserTest, success04)
{
    const auto query = "    truncate         structure   SomeStructure    ;  ";
    const auto expected = Init::TruncateInit{}
    .structure_name("SomeStructure");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_TruncateParserTest, fail01)
{
    EXPECT_FAIL("truncate structure");
    EXPECT_FAIL("truncate structure SomeStructure dadad");
    EXPECT_FAIL("truncate SomeStructure");
}
// clang-format on

} // namespace LunarDB::Moonlight::Implementation::Tests
