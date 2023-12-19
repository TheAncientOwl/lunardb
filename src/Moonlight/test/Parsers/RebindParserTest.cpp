#include "Common/ParserTestIncludes.hpp"

#define QUERY_TYPE Rebind

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

TEST(RebindParserTest, success01)
{
    const auto query = "rebind SomeStructure::someField to SomeTable";
    const auto expected = Init::RebindInit{}
        .structure_name("SomeStructure")
        .field("someField")
        .bind_structure_name("SomeTable")
        .clean(false);

    EXPECT_SUCCESS(query, expected);
}

TEST(RebindParserTest, success02)
{
    const auto query = "rebind      SomeStructure::someField         to      SomeTable    ;   ";
    const auto expected = Init::RebindInit{}
        .structure_name("SomeStructure")
        .field("someField")
        .bind_structure_name("SomeTable")
        .clean(false);

    EXPECT_SUCCESS(query, expected);
}

TEST(RebindParserTest, success03)
{
    const auto query = "rebind SomeStructure::someField to SomeTable clean";
    const auto expected = Init::RebindInit{}
        .structure_name("SomeStructure")
        .field("someField")
        .bind_structure_name("SomeTable")
        .clean(true);

    EXPECT_SUCCESS(query, expected);
}

TEST(RebindParserTest, success04)
{
    const auto query = "rebind    SomeStructure::someField     to  SomeTable    clean    ;   ";
    const auto expected = Init::RebindInit{}
        .structure_name("SomeStructure")
        .field("someField")
        .bind_structure_name("SomeTable")
        .clean(true);

    EXPECT_SUCCESS(query, expected);
}

TEST(RebindParserTest, fail01)
{
    EXPECT_FAIL("rebind SomeStructure:: someField to SomeTable");
    EXPECT_FAIL("rebind SomeStructure someField to SomeTable");
    EXPECT_FAIL("rebind SomeStructure   ::someField to SomeTable");
    EXPECT_FAIL("rebind SomeStructure::someField to SomeTable clean");
    EXPECT_FAIL("rebind SomeStructure::someField to SomeTable;;");
    EXPECT_FAIL("rebind SomeStructure::someField");
    EXPECT_FAIL("rebind someField to SomeTable clean");
    EXPECT_FAIL("rebind SomeStructure::someField to ");
    EXPECT_FAIL("rebind SomeStructure:someField to SomeTable");
}

} // namespace LunarDB::Moonlight::Implementation::Tests
