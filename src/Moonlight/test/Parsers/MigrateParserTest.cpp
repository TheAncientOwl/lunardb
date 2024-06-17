#include "QueryParserTest.hpp"

#define QUERY_TYPE Migrate

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace Common::QueryData;

// clang-format off
TEST(Moonlight_MigrateParserTest, success01)
{
    auto const query = "migrate structure SomeStructure to NewSchema";
    auto const expected = Init::MigrateInit{}
        .structure_name("SomeStructure")
        .new_schema_name("NewSchema")
        .mappings({});

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_MigrateParserTest, success02)
{
    auto const query = "migrate structure SomeStructure to NewSchema;";
    auto const expected = Init::MigrateInit{}
        .structure_name("SomeStructure")
        .new_schema_name("NewSchema")
        .mappings({});

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_MigrateParserTest, success03)
{
    auto const query =
        "migrate structure SomeStructure to NewSchema using ["
        "   old_field1 => new_field1,"
        "   old_field2 => new_field2,"
        "   old_field3 => new_field3,"
        "   old_field4 => new_field4,"
        "   old_field5 => new_field5"
        "]";
    auto const expected = Init::MigrateInit{}
        .structure_name("SomeStructure")
        .new_schema_name("NewSchema")
        .mappings(std::vector<Common::QueryData::Migrate::Mapping>{
            { "old_field1", "new_field1" },
            { "old_field2", "new_field2" },
            { "old_field3", "new_field3" },
            { "old_field4", "new_field4" },
            { "old_field5", "new_field5" }});

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_MigrateParserTest, success04)
{
    auto const query =
        "migrate structure SomeStructure to NewSchema using ["
        "   old_field1 => new_field1,"
        "   old_field2 => new_field2,"
        "   old_field3 => new_field3"
        "];";
    auto const expected = Init::MigrateInit{}
        .structure_name("SomeStructure")
        .new_schema_name("NewSchema")
        .mappings(std::vector<Common::QueryData::Migrate::Mapping>{
            { "old_field1", "new_field1" },
            { "old_field2", "new_field2" },
            { "old_field3", "new_field3" }});

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_MigrateParserTest, fail01)
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

    EXPECT_FAIL("migrate structure SomeStructure to NewSchema using ["
        "   old_field1 => new_field1,"
        "   old_field2 => new_field2,"
        "   old_field3 => new_field3,"
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
// clang-format on

} // namespace LunarDB::Moonlight::Implementation::Tests
