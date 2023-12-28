#include "QueryParserTest.hpp"

#define QUERY_TYPE Drop

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
