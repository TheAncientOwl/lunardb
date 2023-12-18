#include <gtest/gtest.h>

#include "Helpers/QueryDataHelpers.hpp"
#include "ParsedQuery.hpp"

#define EXPECT_SUCCESS(query, expected) \
    const auto out = API::ParsedQuery::from(query).get<Grant>(); \
    EXPECT_EQ(out, expected)

#define EXPECT_FAIL(query) \
    EXPECT_THROW(API::ParsedQuery::from(query).get<Grant>(), std::runtime_error)

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

TEST(GrantParserTest, success01)
{
    const auto query = "grant [ select, create, update, insert, delete ] to UserName";
    const auto expected = Init::GrantInit{}
        .permissions({
            Primitives::EUserPermissionType::Create,
            Primitives::EUserPermissionType::Update,
            Primitives::EUserPermissionType::Insert,
            Primitives::EUserPermissionType::Delete,
            Primitives::EUserPermissionType::Select
            })
        .to_user("UserName")
        .structure_name(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(GrantParserTest, success02)
{
    const auto query = "grant    [      create,         update,      insert,    delete  ]    to         UserName    ;";
    const auto expected = Init::GrantInit{}
        .permissions({
            Primitives::EUserPermissionType::Create,
            Primitives::EUserPermissionType::Update,
            Primitives::EUserPermissionType::Insert,
            Primitives::EUserPermissionType::Delete
            })
        .to_user("UserName")
        .structure_name(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(GrantParserTest, success03)
{
    const auto query = "grant    [      update,         create,      delete,    insert  ]    to         UserName    ;";
    const auto expected = Init::GrantInit{}
        .permissions({
            Primitives::EUserPermissionType::Create,
            Primitives::EUserPermissionType::Update,
            Primitives::EUserPermissionType::Insert,
            Primitives::EUserPermissionType::Delete
            })
        .to_user("UserName")
        .structure_name(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(GrantParserTest, success04)
{
    const auto query = "grant [ update, insert, delete ] to UserName on SomeStructure";
    const auto expected = Init::GrantInit{}
        .permissions({
            Primitives::EUserPermissionType::Update,
            Primitives::EUserPermissionType::Insert,
            Primitives::EUserPermissionType::Delete
            })
        .to_user("UserName")
        .structure_name("SomeStructure");

    EXPECT_SUCCESS(query, expected);
}

TEST(GrantParserTest, success05)
{
    const auto query = "grant [ create, update, insert, create, delete, update ] to UserName on SomeStructure";
    const auto expected = Init::GrantInit{}
        .permissions({
            Primitives::EUserPermissionType::Create,
            Primitives::EUserPermissionType::Update,
            Primitives::EUserPermissionType::Insert,
            Primitives::EUserPermissionType::Delete
            })
        .to_user("UserName")
        .structure_name("SomeStructure");

    EXPECT_SUCCESS(query, expected);
}

TEST(GrantParserTest, fail01)
{
    EXPECT_FAIL("grant select, create, update, insert, delete ] to UserName on StructureName");
    EXPECT_FAIL("grant [ select, create, update, insert, delete to UserName on StructureName");
    EXPECT_FAIL("grant select, create, update, insert, delete to UserName on StructureName");
    EXPECT_FAIL("grant [ select create, update, insert, delete ] to UserName on StructureName");
    EXPECT_FAIL("grant [ select, create, update, insert, delete ] on StructureName");
    EXPECT_FAIL("grant [ select, create, update, insert, delete ] UserName on StructureName");
    EXPECT_FAIL("grant [ select, create, update, insert, delete ] to");
    EXPECT_FAIL("grant [ select, create, update, other, insert, delete ] to UserName on StructureName");
    EXPECT_FAIL("grant [ select, create, update, insert, delete ] to User Name on StructureName");
    EXPECT_FAIL("grant [ select, create, update, insert, delete ] to UserName on Structure Name");
    EXPECT_FAIL("grant [ ] to UserName on StructureName");
    EXPECT_FAIL("grant [ ] to UserName");
    EXPECT_FAIL("grant select to UserName on StructureName");

    EXPECT_FAIL("grant select, create, update, insert, delete ] to UserName on StructureName;");
    EXPECT_FAIL("grant [ select, create, update, insert, delete to UserName on StructureName;");
    EXPECT_FAIL("grant select, create, update, insert, delete to UserName on StructureName;");
    EXPECT_FAIL("grant [ select create, update, insert, delete ] to UserName on StructureName;");
    EXPECT_FAIL("grant [ select, create, update, insert, delete ] on StructureName;");
    EXPECT_FAIL("grant [ select, create, update, insert, delete ] UserName on StructureName;");
    EXPECT_FAIL("grant [ select, create, update, insert, delete ] to;");
    EXPECT_FAIL("grant [ select, create, update, other, insert, delete ] to UserName on StructureName;");
    EXPECT_FAIL("grant [ select, create, update, insert, delete ] to User Name on StructureName;");
    EXPECT_FAIL("grant [ select, create, update, insert, delete ] to UserName on Structure Name;");
    EXPECT_FAIL("grant [ ] to UserName on StructureName;");
    EXPECT_FAIL("grant [ ] to UserName;");
    EXPECT_FAIL("grant select to UserName on StructureName;");
}

} // namespace LunarDB::Moonlight::Implementation::Tests
