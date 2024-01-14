#include "QueryParserTest.hpp"

#define QUERY_TYPE Index

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

TEST(Moonlight_IndexParserTest, success02)
{
    const auto query = "index StructureName as IndexName";
    const auto expected = Init::IndexInit{}
        .on_structure_name("StructureName")
        .unique(false)
        .name("IndexName")
        .using_fields({});

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_IndexParserTest, success03)
{
    const auto query = "index StructureName unique as IndexName using [ field1, field2, field3, field1 ]";
    const auto expected = Init::IndexInit{}
        .on_structure_name("StructureName")
        .unique(true)
        .name("IndexName")
        .using_fields(std::vector<std::string>{ "field1", "field2", "field3" });

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_IndexParserTest, success04)
{
    const auto query = "index StructureName unique as IndexName using [ field1, field2, field3, field1 ]";
    const auto expected = Init::IndexInit{}
        .on_structure_name("StructureName")
        .unique(true)
        .name("IndexName")
        .using_fields(std::vector<std::string>{ "field1", "field2", "field3" });

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_IndexParserTest, success05)
{
    const auto query = "index StructureName as IndexName using [ field1, field2, field3, field1 ]";
    const auto expected = Init::IndexInit{}
        .on_structure_name("StructureName")
        .unique(false)
        .name("IndexName")
        .using_fields(std::vector<std::string>{ "field1", "field2", "field3" });

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_IndexParserTest, fail01)
{
    EXPECT_FAIL("index StructureName unique");
    EXPECT_FAIL("index StructureName");
    EXPECT_FAIL("index StructureName unique as IndexName using [  ]");
    EXPECT_FAIL("index StructureName unique as IndexName using  field1, field2, field3, field1 ]");
    EXPECT_FAIL("index StructureName unique as IndexName using [ field1, field2, field3, field1 ");
    EXPECT_FAIL("index StructureName IndexName using [ field1, field2, field3, field1 ]");
    EXPECT_FAIL("index StructureName unique IndexName using [ field1, field2, field3, field1 ]");
    EXPECT_FAIL("index StructureName unique as IndexName [ field1, field2, field3, field1 ]");
    EXPECT_FAIL("index StructureName unique using field1, field2, field3, field1 ]");
    EXPECT_FAIL("index StructureName unique using [ field1, field2, field3, field1 ");
    EXPECT_FAIL("index StructureName unique as IndexName using [ field1 field2, field3, field1 ]");
}

} // namespace LunarDB::Moonlight::Implementation::Tests
