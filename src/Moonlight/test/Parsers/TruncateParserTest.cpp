#include "QueryParserTest.hpp"

#define QUERY_TYPE Truncate

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

// clang-format off
TEST(Moonlight_TruncateParserTest, success01)
{
    auto const query = "truncate structure SomeStructure";
    auto const expected = Init::TruncateInit{}
    .structure_name("SomeStructure");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_TruncateParserTest, success02)
{
    auto const query = "truncate structure SomeStructure;";
    auto const expected = Init::TruncateInit{}
    .structure_name("SomeStructure");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_TruncateParserTest, success03)
{
    auto const query = "    truncate         structure   SomeStructure    ";
    auto const expected = Init::TruncateInit{}
    .structure_name("SomeStructure");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_TruncateParserTest, success04)
{
    auto const query = "    truncate         structure   SomeStructure    ;  ";
    auto const expected = Init::TruncateInit{}
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
