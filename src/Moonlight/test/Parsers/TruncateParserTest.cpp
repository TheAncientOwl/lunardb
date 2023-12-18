#include <gtest/gtest.h>

#include "QueryDataHelpers/Helpers.hpp"
#include "ParsedQuery.hpp"

#define EXPECT_SUCCESS(query, expected) \
    const auto out = API::ParsedQuery::from(query).get<Truncate>(); \
    EXPECT_EQ(out, expected)

#define EXPECT_FAIL(query) \
    EXPECT_THROW(API::ParsedQuery::from(query).get<Truncate>(), std::runtime_error)

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
