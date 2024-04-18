#include "QueryParserTest.hpp"

#define QUERY_TYPE Rebind

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

// clang-format off
TEST(Moonlight_RebindParserTest, success01)
{
    auto const query = "rebind SomeStructure::someField to SomeTable";
    auto const expected = Init::RebindInit{}
        .structure_name("SomeStructure")
        .field("someField")
        .bind_structure_name("SomeTable")
        .clean(false);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_RebindParserTest, success02)
{
    auto const query = "rebind      SomeStructure::someField         to      SomeTable    ;   ";
    auto const expected = Init::RebindInit{}
        .structure_name("SomeStructure")
        .field("someField")
        .bind_structure_name("SomeTable")
        .clean(false);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_RebindParserTest, success03)
{
    auto const query = "rebind SomeStructure::someField to SomeTable clean";
    auto const expected = Init::RebindInit{}
        .structure_name("SomeStructure")
        .field("someField")
        .bind_structure_name("SomeTable")
        .clean(true);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_RebindParserTest, success04)
{
    auto const query = "rebind    SomeStructure::someField     to  SomeTable    clean    ;   ";
    auto const expected = Init::RebindInit{}
        .structure_name("SomeStructure")
        .field("someField")
        .bind_structure_name("SomeTable")
        .clean(true);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_RebindParserTest, fail01)
{
    EXPECT_FAIL("rebind SomeStructure:: someField to SomeTable");
    EXPECT_FAIL("rebind SomeStructure:: to SomeTable");
    EXPECT_FAIL("rebind ::someField to SomeTable");
    EXPECT_FAIL("rebind SomeStructure someField to SomeTable");
    EXPECT_FAIL("rebind SomeStructure   ::someField to SomeTable");
    EXPECT_FAIL("rebind SomeStructure::someField");
    EXPECT_FAIL("rebind someField to SomeTable clean");
    EXPECT_FAIL("rebind SomeStructure::someField to ");
    EXPECT_FAIL("rebind SomeStructure:someField to SomeTable");
}
// clang-format on

} // namespace LunarDB::Moonlight::Implementation::Tests
