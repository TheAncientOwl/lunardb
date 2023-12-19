#include <gtest/gtest.h>

#include "QueryDataHelpers/Init.hpp"
#include "QueryDataHelpers/Operators.hpp"
#include "ParsedQuery.hpp"

#include "Common/Expectations.hpp"
#define QUERY_TYPE Truncate

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

TEST(TruncateParserTest, success01)
{
    const auto query = "truncate structure SomeStructure";
    const auto expected = Init::TruncateInit{}
    .structure_name("SomeStructure");

    EXPECT_SUCCESS(query, expected);
}

TEST(TruncateParserTest, success02)
{
    const auto query = "truncate structure SomeStructure;";
    const auto expected = Init::TruncateInit{}
    .structure_name("SomeStructure");

    EXPECT_SUCCESS(query, expected);
}

TEST(TruncateParserTest, success03)
{
    const auto query = "    truncate         structure   SomeStructure    ";
    const auto expected = Init::TruncateInit{}
    .structure_name("SomeStructure");

    EXPECT_SUCCESS(query, expected);
}

TEST(TruncateParserTest, success04)
{
    const auto query = "    truncate         structure   SomeStructure    ;  ";
    const auto expected = Init::TruncateInit{}
    .structure_name("SomeStructure");

    EXPECT_SUCCESS(query, expected);
}

TEST(TruncateParserTest, fail01)
{
    EXPECT_FAIL("truncate structure");
    EXPECT_FAIL("truncate structure SomeStructure dadad");
    EXPECT_FAIL("truncate SomeStructure");
}

} // namespace LunarDB::Moonlight::Implementation::Tests
