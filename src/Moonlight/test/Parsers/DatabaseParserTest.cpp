#include "QueryParserTest.hpp"

#define QUERY_TYPE Database

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

TEST(Moonlight_DatabaseParserTest, success01)
{
    const auto query = "database create SomeDatabase";
    const auto expected = Init::DatabaseInit{}
        .operation_type(Primitives::EDatabaseOperationType::Create)
        .name("SomeDatabase")
        .backup_path(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_DatabaseParserTest, success02)
{
    const auto query = "database create SomeDatabase;";
    const auto expected = Init::DatabaseInit{}
        .operation_type(Primitives::EDatabaseOperationType::Create)
        .name("SomeDatabase")
        .backup_path(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_DatabaseParserTest, success03)
{
    const auto query = "database drop SomeDatabase";
    const auto expected = Init::DatabaseInit{}
        .operation_type(Primitives::EDatabaseOperationType::Drop)
        .name("SomeDatabase")
        .backup_path(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_DatabaseParserTest, success04)
{
    const auto query = "database drop SomeDatabase;";
    const auto expected = Init::DatabaseInit{}
        .operation_type(Primitives::EDatabaseOperationType::Drop)
        .name("SomeDatabase")
        .backup_path(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_DatabaseParserTest, success05)
{
    const auto query = "database use SomeDatabase";
    const auto expected = Init::DatabaseInit{}
        .operation_type(Primitives::EDatabaseOperationType::Use)
        .name("SomeDatabase")
        .backup_path(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_DatabaseParserTest, success06)
{
    const auto query = "database use SomeDatabase;";
    const auto expected = Init::DatabaseInit{}
        .operation_type(Primitives::EDatabaseOperationType::Use)
        .name("SomeDatabase")
        .backup_path(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_DatabaseParserTest, success07)
{
    const auto query = R"(database backup SomeDatabase to disk "/home/user/lunardb-backup")";
    const auto expected = Init::DatabaseInit{}
        .operation_type(Primitives::EDatabaseOperationType::Backup)
        .name("SomeDatabase")
        .backup_path(R"(/home/user/lunardb-backup)");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_DatabaseParserTest, success08)
{
    const auto query = R"(database backup SomeDatabase to disk "/home/user/lunardb-backup";)";
    const auto expected = Init::DatabaseInit{}
        .operation_type(Primitives::EDatabaseOperationType::Backup)
        .name("SomeDatabase")
        .backup_path(R"(/home/user/lunardb-backup)");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_DatabaseParserTest, fail01)
{
    EXPECT_FAIL(R"(database SomeDatabase;)");

    EXPECT_FAIL(R"(database create)");
    EXPECT_FAIL(R"(database create ;)");
    EXPECT_FAIL(R"(database create SomeDatabase to disk "/home/user/lunardb-backup";)");

    EXPECT_FAIL(R"(database drop)");
    EXPECT_FAIL(R"(database drop ;)");
    EXPECT_FAIL(R"(database drop SomeDatabase to disk "/home/user/lunardb-backup";)");

    EXPECT_FAIL(R"(database use)");
    EXPECT_FAIL(R"(database use ;)");
    EXPECT_FAIL(R"(database use SomeDatabase to disk "/home/user/lunardb-backup";)");

    EXPECT_FAIL(R"(database backup)");
    EXPECT_FAIL(R"(database backup ;)");
    EXPECT_FAIL(R"(database backup SomeDatabase;)");
    EXPECT_FAIL(R"(database backup SomeDatabase)");
}

} // namespace LunarDB::Moonlight::Implementation::Tests
