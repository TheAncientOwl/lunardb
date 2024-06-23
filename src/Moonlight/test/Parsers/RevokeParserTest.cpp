#include "QueryParserTest.hpp"

#define QUERY_TYPE Revoke

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace Common::QueryData;

// clang-format off
TEST(Moonlight_RevokeParserTest, success01)
{
    auto const query = "revoke [ select,  update, insert, delete ] from UserName on SomeCollection";
    auto const expected = Init::RevokeInit{}
        .permissions({
            Primitives::EUserPermissionType::Select,
            Primitives::EUserPermissionType::Insert,
            Primitives::EUserPermissionType::Update,
            Primitives::EUserPermissionType::Delete,
            })
        .from_user("UserName")
        .structure_name("SomeCollection");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_RevokeParserTest, success02)
{
    auto const query = "revoke    [               update,      insert,    delete  ]    from         UserName    on SomeCollection;";
    auto const expected = Init::RevokeInit{}
        .permissions({
            Primitives::EUserPermissionType::Insert,
            Primitives::EUserPermissionType::Update,
            Primitives::EUserPermissionType::Delete,
            })
        .from_user("UserName")
        .structure_name("SomeCollection");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_RevokeParserTest, success03)
{
    auto const query = "revoke    [      update,               delete,    insert  ]    from         UserName    on SomeCollection;";
    auto const expected = Init::RevokeInit{}
        .permissions({
            Primitives::EUserPermissionType::Insert,
            Primitives::EUserPermissionType::Update,
            Primitives::EUserPermissionType::Delete,
            })
        .from_user("UserName")
        .structure_name("SomeCollection");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_RevokeParserTest, success04)
{
    auto const query = "revoke [ update, insert, delete ] from UserName on SomeStructure";
    auto const expected = Init::RevokeInit{}
        .permissions({
            Primitives::EUserPermissionType::Insert,
            Primitives::EUserPermissionType::Update,
            Primitives::EUserPermissionType::Delete,
            })
        .from_user("UserName")
        .structure_name("SomeStructure");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_RevokeParserTest, success05)
{
    auto const query = "revoke [  update, insert,  delete, update ] from UserName on SomeStructure";
    auto const expected = Init::RevokeInit{}
        .permissions({
            Primitives::EUserPermissionType::Insert,
            Primitives::EUserPermissionType::Update,
            Primitives::EUserPermissionType::Delete,
            })
        .from_user("UserName")
        .structure_name("SomeStructure");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_RevokeParserTest, fail01)
{
    EXPECT_FAIL("revoke select,  update, insert, delete ] from UserName on StructureName");
    EXPECT_FAIL("revoke [ select,  update, insert, delete from UserName on StructureName");
    EXPECT_FAIL("revoke select,  update, insert, delete from UserName on StructureName");
    EXPECT_FAIL("revoke [ select  update, insert, delete ] from UserName on StructureName");
    EXPECT_FAIL("revoke [ select,  update, insert, delete ] on StructureName");
    EXPECT_FAIL("revoke [ select,  update, insert, delete ] UserName on StructureName");
    EXPECT_FAIL("revoke [ select,  update, insert, delete ] from");
    EXPECT_FAIL("revoke [ select,  update, other, insert, delete ] from UserName on StructureName");
    EXPECT_FAIL("revoke [ select,  update, insert, delete ] from User Name on StructureName");
    EXPECT_FAIL("revoke [ select,  update, insert, delete ] from UserName on Structure Name");
    EXPECT_FAIL("revoke [ ] from UserName on StructureName");
    EXPECT_FAIL("revoke [ ] from UserName");
    EXPECT_FAIL("revoke select from UserName on StructureName");

    EXPECT_FAIL("revoke select,  update, insert, delete ] from UserName on StructureName;");
    EXPECT_FAIL("revoke [ select,  update, insert, delete from UserName on StructureName;");
    EXPECT_FAIL("revoke select,  update, insert, delete from UserName on StructureName;");
    EXPECT_FAIL("revoke [ select  update, insert, delete ] from UserName on StructureName;");
    EXPECT_FAIL("revoke [ select,  update, insert, delete ] on StructureName;");
    EXPECT_FAIL("revoke [ select,  update, insert, delete ] UserName on StructureName;");
    EXPECT_FAIL("revoke [ select,  update, insert, delete ] from;");
    EXPECT_FAIL("revoke [ select,  update, other, insert, delete ] from UserName on StructureName;");
    EXPECT_FAIL("revoke [ select,  update, insert, delete ] from User Name on StructureName;");
    EXPECT_FAIL("revoke [ select,  update, insert, delete ] from UserName on Structure Name;");
    EXPECT_FAIL("revoke [ ] from UserName on StructureName;");
    EXPECT_FAIL("revoke [ ] from UserName;");
    EXPECT_FAIL("revoke select from UserName on StructureName;");
}
// clang-format on

} // namespace LunarDB::Moonlight::Implementation::Tests
