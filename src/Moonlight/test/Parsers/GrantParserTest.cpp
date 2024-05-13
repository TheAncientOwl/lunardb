#include "QueryParserTest.hpp"

#define QUERY_TYPE Grant

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace Common::QueryData;

// clang-format off
TEST(Moonlight_GrantParserTest, success01)
{
    auto const query = "grant [ select, create, update, insert, delete ] to UserName";
    auto const expected = Init::GrantInit{}
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

TEST(Moonlight_GrantParserTest, success02)
{
    auto const query = "grant    [      create,         update,      insert,    delete  ]    to         UserName    ;";
    auto const expected = Init::GrantInit{}
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

TEST(Moonlight_GrantParserTest, success03)
{
    auto const query = "grant    [      update,         create,      delete,    insert  ]    to         UserName    ;";
    auto const expected = Init::GrantInit{}
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

TEST(Moonlight_GrantParserTest, success04)
{
    auto const query = "grant [ update, insert, delete ] to UserName on SomeStructure";
    auto const expected = Init::GrantInit{}
        .permissions({
            Primitives::EUserPermissionType::Update,
            Primitives::EUserPermissionType::Insert,
            Primitives::EUserPermissionType::Delete
            })
        .to_user("UserName")
        .structure_name("SomeStructure");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_GrantParserTest, success05)
{
    auto const query = "grant [ create, update, insert, create, delete, update ] to UserName on SomeStructure";
    auto const expected = Init::GrantInit{}
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

TEST(Moonlight_GrantParserTest, fail01)
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
// clang-format on

} // namespace LunarDB::Moonlight::Implementation::Tests
