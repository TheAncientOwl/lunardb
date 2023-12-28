#include "QueryParserTest.hpp"

#define QUERY_TYPE Rename

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

TEST(RenameParserTest, success01)
{
    const auto query = "rename structure from SomeStructure to SomeStructureNew";
    const auto expected = Init::RenameInit{}
        .type(Primitives::ERenameType::Structure)
        .old_name("SomeStructure")
        .new_name("SomeStructureNew");

    EXPECT_SUCCESS(query, expected);
}

TEST(RenameParserTest, success02)
{
    const auto query = "rename structure from SomeStructure to SomeStructureNew;";
    const auto expected = Init::RenameInit{}
        .type(Primitives::ERenameType::Structure)
        .old_name("SomeStructure")
        .new_name("SomeStructureNew");

    EXPECT_SUCCESS(query, expected);
}

TEST(RenameParserTest, success03)
{
    const auto query = "    rename      structure    from     SomeStructure         to      SomeStructureNew     ;   ";
    const auto expected = Init::RenameInit{}
        .type(Primitives::ERenameType::Structure)
        .old_name("SomeStructure")
        .new_name("SomeStructureNew");

    EXPECT_SUCCESS(query, expected);
}

TEST(RenameParserTest, success04)
{
    const auto query = "rename database from SomeDatabase to SomeDatabaseNew";
    const auto expected = Init::RenameInit{}
        .type(Primitives::ERenameType::Database)
        .old_name("SomeDatabase")
        .new_name("SomeDatabaseNew");

    EXPECT_SUCCESS(query, expected);
}

TEST(RenameParserTest, success05)
{
    const auto query = "    rename      database    from     SomeDatabase         to      SomeDatabaseNew     ;   ";
    const auto expected = Init::RenameInit{}
        .type(Primitives::ERenameType::Database)
        .old_name("SomeDatabase")
        .new_name("SomeDatabaseNew");

    EXPECT_SUCCESS(query, expected);
}

TEST(RenameParserTest, success06)
{
    const auto query = "rename field from SomeStructure::SomeField to SomeStructure::SomeFieldNew";
    const auto expected = Init::RenameInit{}
        .type(Primitives::ERenameType::Field)
        .old_name("SomeStructure::SomeField")
        .new_name("SomeStructure::SomeFieldNew");

    EXPECT_SUCCESS(query, expected);
}

TEST(RenameParserTest, success07)
{
    const auto query = "    rename      field        from       SomeStructure::SomeField   to        SomeStructure::SomeFieldNew     ;";
    const auto expected = Init::RenameInit{}
        .type(Primitives::ERenameType::Field)
        .old_name("SomeStructure::SomeField")
        .new_name("SomeStructure::SomeFieldNew");

    EXPECT_SUCCESS(query, expected);
}

TEST(RenameParserTest, fail01)
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

} // namespace LunarDB::Moonlight::Implementation::Tests
