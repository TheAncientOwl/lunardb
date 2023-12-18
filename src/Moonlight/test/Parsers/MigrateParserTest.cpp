#include <gtest/gtest.h>

#include "Helpers/QueryDataHelpers.hpp"
#include "ParsedQuery.hpp"

#define EXPECT_SUCCESS(query, expected) \
    const auto out = API::ParsedQuery::from(query).get<Migrate>(); \
    EXPECT_EQ(out, expected)

#define EXPECT_FAIL(query) \
    EXPECT_THROW(API::ParsedQuery::from(query).get<Migrate>(), std::runtime_error)

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

TEST(MigrateParserTest, success01)
{
    const auto query = "migrate structure SomeStructure to NewSchema";
    const auto expected = Init::MigrateInit{}
        .structure_name("SomeStructure")
        .new_schema_name("NewSchema")
        .mappings(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(MigrateParserTest, success02)
{
    const auto query = "migrate structure SomeStructure to NewSchema;";
    const auto expected = Init::MigrateInit{}
        .structure_name("SomeStructure")
        .new_schema_name("NewSchema")
        .mappings(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(MigrateParserTest, success03)
{
    const auto query =
        "migrate structure SomeStructure to NewSchema using ["
        "   old_field1 => new_field1,"
        "   old_field2 => new_field2,"
        "   old_field1 => new_field1,"
        "   old_field3 => new_field3,"
        "   old_field2 => new_field2"
        "]";
    const auto expected = Init::MigrateInit{}
        .structure_name("SomeStructure")
        .new_schema_name("NewSchema")
        .mappings(std::vector<Migrate::Mapping>{
            { "old_field1", "new_field1" },
            { "old_field2", "new_field2" },
            { "old_field3", "new_field3" }});

    EXPECT_SUCCESS(query, expected);
}

TEST(MigrateParserTest, success04)
{
    const auto query =
        "migrate structure SomeStructure to NewSchema using ["
        "   old_field1 => new_field1,"
        "   old_field2 => new_field2,"
        "   old_field3 => new_field3"
        "];";
    const auto expected = Init::MigrateInit{}
        .structure_name("SomeStructure")
        .new_schema_name("NewSchema")
        .mappings(std::vector<Migrate::Mapping>{
            { "old_field1", "new_field1" },
            { "old_field2", "new_field2" },
            { "old_field3", "new_field3" }});

    EXPECT_SUCCESS(query, expected);
}

TEST(MigrateParserTest, fail01)
{
    EXPECT_FAIL("migrate SomeStructure to NewSchema");
    EXPECT_FAIL("migrate structure to NewSchema");
    EXPECT_FAIL("migrate structure SomeStructure NewSchema");
    EXPECT_FAIL("migrate structure SomeStructure to");

    EXPECT_FAIL("migrate structure SomeStructure to NewSchema  ["
        "   old_field1 => new_field1,"
        "   old_field2 => new_field2,"
        "   old_field3 => new_field3"
        "];");

    EXPECT_FAIL("migrate structure SomeStructure to NewSchema using "
        "   old_field1 => new_field1,"
        "   old_field2 => new_field2,"
        "   old_field3 => new_field3"
        "];");

    EXPECT_FAIL("migrate structure SomeStructure to NewSchema using ["
        "   old_field1 => new_field1,"
        "   old_field2 => new_field2,"
        "   old_field3 => new_field3"
        ";");

    EXPECT_FAIL("migrate structure SomeStructure to NewSchema using ["
        "   old_field1 => new_field1,"
        "   old_field2 => new_field2"
        "   old_field3 => new_field3"
        "];");

    EXPECT_FAIL("migrate structure SomeStructure to NewSchema using ["
        "];");

    EXPECT_FAIL("migrate structure SomeStructure to NewSchema using ["
        "   old_field1 => new_field1,"
        "   old_field2 new_field2,"
        "   old_field3 => new_field3"
        "];");

    EXPECT_FAIL("migrate structure SomeStructure to NewSchema using ["
        "   old_field1 => new_field1,"
        "   old_field2 = new_field2,"
        "   old_field3 => new_field3"
        "];");

    EXPECT_FAIL("migrate structure SomeStructure to NewSchema using ["
        "   old_field1 => new_field1,"
        "   old_field2 > new_field2,"
        "   old_field3 => new_field3"
        "];");
}

} // namespace LunarDB::Moonlight::Implementation::Tests
