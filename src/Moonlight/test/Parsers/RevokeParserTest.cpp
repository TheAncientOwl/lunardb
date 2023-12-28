#include "QueryParserTest.hpp"

#define QUERY_TYPE Revoke

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

TEST(RevokeParserTest, success01)
{
    const auto query = "revoke [ select, create, update, insert, delete ] from UserName";
    const auto expected = Init::RevokeInit{}
        .permissions({
            Primitives::EUserPermissionType::Create,
            Primitives::EUserPermissionType::Update,
            Primitives::EUserPermissionType::Insert,
            Primitives::EUserPermissionType::Delete,
            Primitives::EUserPermissionType::Select
            })
        .from_user("UserName")
        .structure_name(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(RevokeParserTest, success02)
{
    const auto query = "revoke    [      create,         update,      insert,    delete  ]    from         UserName    ;";
    const auto expected = Init::RevokeInit{}
        .permissions({
            Primitives::EUserPermissionType::Create,
            Primitives::EUserPermissionType::Update,
            Primitives::EUserPermissionType::Insert,
            Primitives::EUserPermissionType::Delete
            })
        .from_user("UserName")
        .structure_name(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(RevokeParserTest, success03)
{
    const auto query = "revoke    [      update,         create,      delete,    insert  ]    from         UserName    ;";
    const auto expected = Init::RevokeInit{}
        .permissions({
            Primitives::EUserPermissionType::Create,
            Primitives::EUserPermissionType::Update,
            Primitives::EUserPermissionType::Insert,
            Primitives::EUserPermissionType::Delete
            })
        .from_user("UserName")
        .structure_name(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(RevokeParserTest, success04)
{
    const auto query = "revoke [ update, insert, delete ] from UserName on SomeStructure";
    const auto expected = Init::RevokeInit{}
        .permissions({
            Primitives::EUserPermissionType::Update,
            Primitives::EUserPermissionType::Insert,
            Primitives::EUserPermissionType::Delete
            })
        .from_user("UserName")
        .structure_name("SomeStructure");

    EXPECT_SUCCESS(query, expected);
}

TEST(RevokeParserTest, success05)
{
    const auto query = "revoke [ create, update, insert, create, delete, update ] from UserName on SomeStructure";
    const auto expected = Init::RevokeInit{}
        .permissions({
            Primitives::EUserPermissionType::Create,
            Primitives::EUserPermissionType::Update,
            Primitives::EUserPermissionType::Insert,
            Primitives::EUserPermissionType::Delete
            })
        .from_user("UserName")
        .structure_name("SomeStructure");

    EXPECT_SUCCESS(query, expected);
}

TEST(RevokeParserTest, fail01)
{
    EXPECT_FAIL("revoke select, create, update, insert, delete ] from UserName on StructureName");
    EXPECT_FAIL("revoke [ select, create, update, insert, delete from UserName on StructureName");
    EXPECT_FAIL("revoke select, create, update, insert, delete from UserName on StructureName");
    EXPECT_FAIL("revoke [ select create, update, insert, delete ] from UserName on StructureName");
    EXPECT_FAIL("revoke [ select, create, update, insert, delete ] on StructureName");
    EXPECT_FAIL("revoke [ select, create, update, insert, delete ] UserName on StructureName");
    EXPECT_FAIL("revoke [ select, create, update, insert, delete ] from");
    EXPECT_FAIL("revoke [ select, create, update, other, insert, delete ] from UserName on StructureName");
    EXPECT_FAIL("revoke [ select, create, update, insert, delete ] from User Name on StructureName");
    EXPECT_FAIL("revoke [ select, create, update, insert, delete ] from UserName on Structure Name");
    EXPECT_FAIL("revoke [ ] from UserName on StructureName");
    EXPECT_FAIL("revoke [ ] from UserName");
    EXPECT_FAIL("revoke select from UserName on StructureName");

    EXPECT_FAIL("revoke select, create, update, insert, delete ] from UserName on StructureName;");
    EXPECT_FAIL("revoke [ select, create, update, insert, delete from UserName on StructureName;");
    EXPECT_FAIL("revoke select, create, update, insert, delete from UserName on StructureName;");
    EXPECT_FAIL("revoke [ select create, update, insert, delete ] from UserName on StructureName;");
    EXPECT_FAIL("revoke [ select, create, update, insert, delete ] on StructureName;");
    EXPECT_FAIL("revoke [ select, create, update, insert, delete ] UserName on StructureName;");
    EXPECT_FAIL("revoke [ select, create, update, insert, delete ] from;");
    EXPECT_FAIL("revoke [ select, create, update, other, insert, delete ] from UserName on StructureName;");
    EXPECT_FAIL("revoke [ select, create, update, insert, delete ] from User Name on StructureName;");
    EXPECT_FAIL("revoke [ select, create, update, insert, delete ] from UserName on Structure Name;");
    EXPECT_FAIL("revoke [ ] from UserName on StructureName;");
    EXPECT_FAIL("revoke [ ] from UserName;");
    EXPECT_FAIL("revoke select from UserName on StructureName;");
}

} // namespace LunarDB::Moonlight::Implementation::Tests
