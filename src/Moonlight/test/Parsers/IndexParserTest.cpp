#include <gtest/gtest.h>

#include "QueryDataHelpers/Helpers.hpp"
#include "ParsedQuery.hpp"

#define EXPECT_SUCCESS(query, expected) \
    const auto out = API::ParsedQuery::from(query).get<Index>(); \
    EXPECT_EQ(out, expected)

#define EXPECT_FAIL(query) \
    EXPECT_THROW(API::ParsedQuery::from(query).get<Index>(), std::runtime_error)

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

TEST(IndexParserTest, success01)
{
    const auto query = "index StructureName";
    const auto expected = Init::IndexInit{}
        .on_structure_name("StructureName")
        .unique(false)
        .name(std::nullopt)
        .using_fields(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(IndexParserTest, success02)
{
    const auto query = "index StructureName as IndexName";
    const auto expected = Init::IndexInit{}
        .on_structure_name("StructureName")
        .unique(false)
        .name("IndexName")
        .using_fields(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(IndexParserTest, success03)
{
    const auto query = "index StructureName unique as IndexName using [ field1, field2, field3, field1 ]";
    const auto expected = Init::IndexInit{}
        .on_structure_name("StructureName")
        .unique(true)
        .name("IndexName")
        .using_fields(std::vector<std::string>{ "field1", "field2", "field3" });

    EXPECT_SUCCESS(query, expected);
}

TEST(IndexParserTest, success04)
{
    const auto query = "index StructureName unique as IndexName using [ field1, field2, field3, field1 ]";
    const auto expected = Init::IndexInit{}
        .on_structure_name("StructureName")
        .unique(true)
        .name("IndexName")
        .using_fields(std::vector<std::string>{ "field1", "field2", "field3" });

    EXPECT_SUCCESS(query, expected);
}

TEST(IndexParserTest, success05)
{
    const auto query = "index StructureName as IndexName using [ field1, field2, field3, field1 ]";
    const auto expected = Init::IndexInit{}
        .on_structure_name("StructureName")
        .unique(false)
        .name("IndexName")
        .using_fields(std::vector<std::string>{ "field1", "field2", "field3" });

    EXPECT_SUCCESS(query, expected);
}

TEST(IndexParserTest, fail01)
{
    EXPECT_FAIL("index StructureName unique as IndexName using [  ]");
    EXPECT_FAIL("index StructureName unique as IndexName using  field1, field2, field3, field1 ]");
    EXPECT_FAIL("index StructureName unique as IndexName using [ field1, field2, field3, field1 ");
    EXPECT_FAIL("index unique as IndexName using [ field1, field2, field3, field1 ]");
    EXPECT_FAIL("index StructureName IndexName using [ field1, field2, field3, field1 ]");
    EXPECT_FAIL("index StructureName unique IndexName using [ field1, field2, field3, field1 ]");
    EXPECT_FAIL("index StructureName unique as IndexName [ field1, field2, field3, field1 ]");
    EXPECT_FAIL("index StructureName unique using field1, field2, field3, field1 ]");
    EXPECT_FAIL("index StructureName unique using [ field1, field2, field3, field1 ");
    EXPECT_FAIL("index StructureName unique as IndexName using [ field1 field2, field3, field1 ]");
}

} // namespace LunarDB::Moonlight::Implementation::Tests
