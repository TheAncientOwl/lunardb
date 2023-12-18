#include <gtest/gtest.h>

#include "QueryDataHelpers/Init.hpp"
#include "QueryDataHelpers/Operators.hpp"
#include "ParsedQuery.hpp"

#define EXPECT_SUCCESS(query, expected) \
    const auto out = API::ParsedQuery::from(query).get<Drop>(); \
    EXPECT_EQ(out, expected)

#define EXPECT_FAIL(query) \
    EXPECT_THROW(API::ParsedQuery::from(query).get<Drop>(), std::runtime_error)

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

TEST(DropParserTest, success01)
{
    const auto query = "drop structure SomeStructure";
    const auto expected = Init::DropInit{}
        .structure_name("SomeStructure")
        .cascade(false);

    EXPECT_SUCCESS(query, expected);
}

TEST(DropParserTest, success02)
{
    const auto query = "         drop structure SomeStructure    ;   ";
    const auto expected = Init::DropInit{}
        .structure_name("SomeStructure")
        .cascade(false);

    EXPECT_SUCCESS(query, expected);
}

TEST(DropParserTest, success03)
{
    const auto query = "drop structure SomeStructure cascade";
    const auto expected = Init::DropInit{}
        .structure_name("SomeStructure")
        .cascade(true);

    EXPECT_SUCCESS(query, expected);
}

TEST(DropParserTest, success04)
{
    const auto query = "  drop   structure   SomeStructure   cascade    ; ";
    const auto expected = Init::DropInit{}
        .structure_name("SomeStructure")
        .cascade(true);

    EXPECT_SUCCESS(query, expected);
}

TEST(DropParserTest, fail01)
{
    EXPECT_FAIL("drop structure sdada cascad");
    EXPECT_FAIL("drop structur SomeStruct;");
    EXPECT_FAIL("drop structure SomeStruct cascadee  ");
    EXPECT_FAIL("drop _ structure SomeStruct ");
    EXPECT_FAIL("dropp structure cascade SomeStruct");
}

} // namespace LunarDB::Moonlight::Implementation::Tests
