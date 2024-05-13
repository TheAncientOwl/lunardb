#include "QueryParserTest.hpp"

#define QUERY_TYPE Revoke

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace Common::QueryData;

// clang-format off
TEST(Moonlight_RevokeParserTest, success01)
{
    auto const query = "revoke [ select, create, update, insert, delete ] from UserName";
    auto const expected = Init::RevokeInit{}
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

TEST(Moonlight_RevokeParserTest, success02)
{
    auto const query = "revoke    [      create,         update,      insert,    delete  ]    from         UserName    ;";
    auto const expected = Init::RevokeInit{}
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

TEST(Moonlight_RevokeParserTest, success03)
{
    auto const query = "revoke    [      update,         create,      delete,    insert  ]    from         UserName    ;";
    auto const expected = Init::RevokeInit{}
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

TEST(Moonlight_RevokeParserTest, success04)
{
    auto const query = "revoke [ update, insert, delete ] from UserName on SomeStructure";
    auto const expected = Init::RevokeInit{}
        .permissions({
            Primitives::EUserPermissionType::Update,
            Primitives::EUserPermissionType::Insert,
            Primitives::EUserPermissionType::Delete
            })
        .from_user("UserName")
        .structure_name("SomeStructure");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_RevokeParserTest, success05)
{
    auto const query = "revoke [ create, update, insert, create, delete, update ] from UserName on SomeStructure";
    auto const expected = Init::RevokeInit{}
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

TEST(Moonlight_RevokeParserTest, fail01)
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
// clang-format on

} // namespace LunarDB::Moonlight::Implementation::Tests
