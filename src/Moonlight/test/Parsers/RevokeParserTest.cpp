#include <gtest/gtest.h>

#include "QueryDataHelpers/Helpers.hpp"
#include "ParsedQuery.hpp"

#define EXPECT_SUCCESS(query, expected) \
    const auto out = API::ParsedQuery::from(query).get<Revoke>(); \
    EXPECT_EQ(out, expected)

#define EXPECT_FAIL(query) \
    EXPECT_THROW(API::ParsedQuery::from(query).get<Revoke>(), std::runtime_error)

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

TEST(RevokeParserTest, success01)
{
    const auto query = "grant [ select, create, update, insert, delete ] from UserName";
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
    const auto query = "grant    [      create,         update,      insert,    delete  ]    to         UserName    ;";
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
    const auto query = "grant    [      update,         create,      delete,    insert  ]    to         UserName    ;";
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
    const auto query = "grant [ update, insert, delete ] from UserName on SomeStructure";
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
    const auto query = "grant [ create, update, insert, create, delete, update ] from UserName on SomeStructure";
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
    EXPECT_FAIL("grant select, create, update, insert, delete ] from UserName on StructureName");
    EXPECT_FAIL("grant [ select, create, update, insert, delete from UserName on StructureName");
    EXPECT_FAIL("grant select, create, update, insert, delete from UserName on StructureName");
    EXPECT_FAIL("grant [ select create, update, insert, delete ] from UserName on StructureName");
    EXPECT_FAIL("grant [ select, create, update, insert, delete ] on StructureName");
    EXPECT_FAIL("grant [ select, create, update, insert, delete ] UserName on StructureName");
    EXPECT_FAIL("grant [ select, create, update, insert, delete ] to");
    EXPECT_FAIL("grant [ select, create, update, other, insert, delete ] from UserName on StructureName");
    EXPECT_FAIL("grant [ select, create, update, insert, delete ] to User Name on StructureName");
    EXPECT_FAIL("grant [ select, create, update, insert, delete ] from UserName on Structure Name");
    EXPECT_FAIL("grant [ ] from UserName on StructureName");
    EXPECT_FAIL("grant [ ] from UserName");
    EXPECT_FAIL("grant select from UserName on StructureName");

    EXPECT_FAIL("grant select, create, update, insert, delete ] from UserName on StructureName;");
    EXPECT_FAIL("grant [ select, create, update, insert, delete from UserName on StructureName;");
    EXPECT_FAIL("grant select, create, update, insert, delete from UserName on StructureName;");
    EXPECT_FAIL("grant [ select create, update, insert, delete ] from UserName on StructureName;");
    EXPECT_FAIL("grant [ select, create, update, insert, delete ] on StructureName;");
    EXPECT_FAIL("grant [ select, create, update, insert, delete ] UserName on StructureName;");
    EXPECT_FAIL("grant [ select, create, update, insert, delete ] to;");
    EXPECT_FAIL("grant [ select, create, update, other, insert, delete ] from UserName on StructureName;");
    EXPECT_FAIL("grant [ select, create, update, insert, delete ] to User Name on StructureName;");
    EXPECT_FAIL("grant [ select, create, update, insert, delete ] from UserName on Structure Name;");
    EXPECT_FAIL("grant [ ] from UserName on StructureName;");
    EXPECT_FAIL("grant [ ] from UserName;");
    EXPECT_FAIL("grant select from UserName on StructureName;");
}

} // namespace LunarDB::Moonlight::Implementation::Tests
