#include "QueryParserTest.hpp"

#define QUERY_TYPE Drop

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

// clang-format off
TEST(Moonlight_DropParserTest, success01)
{
    auto const query = "drop structure SomeStructure";
    auto const expected = Init::DropInit{}
        .structure_name("SomeStructure")
        .cascade(false);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_DropParserTest, success02)
{
    auto const query = "         drop structure SomeStructure    ;   ";
    auto const expected = Init::DropInit{}
        .structure_name("SomeStructure")
        .cascade(false);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_DropParserTest, success03)
{
    auto const query = "drop structure SomeStructure cascade";
    auto const expected = Init::DropInit{}
        .structure_name("SomeStructure")
        .cascade(true);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_DropParserTest, success04)
{
    auto const query = "  drop   structure   SomeStructure   cascade    ; ";
    auto const expected = Init::DropInit{}
        .structure_name("SomeStructure")
        .cascade(true);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_DropParserTest, fail01)
{
    EXPECT_FAIL("drop structure sdada cascad");
    EXPECT_FAIL("drop structur SomeStruct;");
    EXPECT_FAIL("drop structure SomeStruct cascadee  ");
    EXPECT_FAIL("drop _ structure SomeStruct ");
    EXPECT_FAIL("dropp structure cascade SomeStruct");
}
// clang-format on

} // namespace LunarDB::Moonlight::Implementation::Tests
