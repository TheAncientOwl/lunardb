#include "QueryParserTest.hpp"

#define QUERY_TYPE Rename

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace Common::QueryData;

// clang-format off
TEST(Moonlight_RenameParserTest, success01)
{
    auto const query = "rename structure from SomeStructure to SomeStructureNew";
    auto const expected = Init::RenameInit{}
        .type(Primitives::ERenameType::Structure)
        .old_name("SomeStructure")
        .new_name("SomeStructureNew");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_RenameParserTest, success02)
{
    auto const query = "rename structure from SomeStructure to SomeStructureNew;";
    auto const expected = Init::RenameInit{}
        .type(Primitives::ERenameType::Structure)
        .old_name("SomeStructure")
        .new_name("SomeStructureNew");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_RenameParserTest, success03)
{
    auto const query = "    rename      structure    from     SomeStructure         to      SomeStructureNew     ;   ";
    auto const expected = Init::RenameInit{}
        .type(Primitives::ERenameType::Structure)
        .old_name("SomeStructure")
        .new_name("SomeStructureNew");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_RenameParserTest, success04)
{
    auto const query = "rename database from SomeDatabase to SomeDatabaseNew";
    auto const expected = Init::RenameInit{}
        .type(Primitives::ERenameType::Database)
        .old_name("SomeDatabase")
        .new_name("SomeDatabaseNew");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_RenameParserTest, success05)
{
    auto const query = "    rename      database    from     SomeDatabase         to      SomeDatabaseNew     ;   ";
    auto const expected = Init::RenameInit{}
        .type(Primitives::ERenameType::Database)
        .old_name("SomeDatabase")
        .new_name("SomeDatabaseNew");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_RenameParserTest, success06)
{
    auto const query = "rename field from SomeStructure::SomeField to SomeStructure::SomeFieldNew";
    auto const expected = Init::RenameInit{}
        .type(Primitives::ERenameType::Field)
        .old_name("SomeStructure::SomeField")
        .new_name("SomeStructure::SomeFieldNew");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_RenameParserTest, success07)
{
    auto const query = "    rename      field        from       SomeStructure::SomeField   to        SomeStructure::SomeFieldNew     ;";
    auto const expected = Init::RenameInit{}
        .type(Primitives::ERenameType::Field)
        .old_name("SomeStructure::SomeField")
        .new_name("SomeStructure::SomeFieldNew");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_RenameParserTest, fail01)
{
    EXPECT_FAIL("rename structure from SomeStructure to Some StructureNew");
    EXPECT_FAIL("rename structure from Some Structure to SomeStructureNew");
    EXPECT_FAIL("rename structure SomeStructure to SomeStructureNew");
    EXPECT_FAIL("rename from SomeStructure to SomeStructureNew");

    EXPECT_FAIL("rename database from SomeDatabase to Some DatabaseNew");
    EXPECT_FAIL("rename database from Some Database to SomeDatabaseNew");
    EXPECT_FAIL("rename database SomeDatabase to SomeDatabaseNew");

    EXPECT_FAIL("rename field from SomeField to Some FieldNew");
    EXPECT_FAIL("rename field from SomeStructure SomeField to SomeStructure::SomeFieldNew");
    EXPECT_FAIL("rename field from SomeStructure::SomeField to SomeStructure SomeFieldNew");
    EXPECT_FAIL("rename field SomeStructure::SomeField to SomeStructure::SomeFieldNew");
}
// clang-format on

} // namespace LunarDB::Moonlight::Implementation::Tests
