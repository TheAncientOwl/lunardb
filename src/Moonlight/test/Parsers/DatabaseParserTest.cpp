#include "QueryParserTest.hpp"

#define QUERY_TYPE Database

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace Common::QueryData;

// clang-format off
TEST(Moonlight_DatabaseParserTest, success01)
{
    auto const query = "database create SomeDatabase";
    auto const expected = Init::DatabaseInit{}
        .operation_type(Primitives::EDatabaseOperationType::Create)
        .name("SomeDatabase")
        .backup_path(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_DatabaseParserTest, success02)
{
    auto const query = "database create SomeDatabase;";
    auto const expected = Init::DatabaseInit{}
        .operation_type(Primitives::EDatabaseOperationType::Create)
        .name("SomeDatabase")
        .backup_path(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_DatabaseParserTest, success03)
{
    auto const query = "database drop SomeDatabase";
    auto const expected = Init::DatabaseInit{}
        .operation_type(Primitives::EDatabaseOperationType::Drop)
        .name("SomeDatabase")
        .backup_path(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_DatabaseParserTest, success04)
{
    auto const query = "database drop SomeDatabase;";
    auto const expected = Init::DatabaseInit{}
        .operation_type(Primitives::EDatabaseOperationType::Drop)
        .name("SomeDatabase")
        .backup_path(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_DatabaseParserTest, success05)
{
    auto const query = "database use SomeDatabase";
    auto const expected = Init::DatabaseInit{}
        .operation_type(Primitives::EDatabaseOperationType::Use)
        .name("SomeDatabase")
        .backup_path(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_DatabaseParserTest, success06)
{
    auto const query = "database use SomeDatabase;";
    auto const expected = Init::DatabaseInit{}
        .operation_type(Primitives::EDatabaseOperationType::Use)
        .name("SomeDatabase")
        .backup_path(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_DatabaseParserTest, success07)
{
    auto const query = R"(database backup SomeDatabase to disk "/home/user/lunardb-backup")";
    auto const expected = Init::DatabaseInit{}
        .operation_type(Primitives::EDatabaseOperationType::Backup)
        .name("SomeDatabase")
        .backup_path(R"(/home/user/lunardb-backup)");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_DatabaseParserTest, success08)
{
    auto const query = R"(database backup SomeDatabase to disk "/home/user/lunardb-backup";)";
    auto const expected = Init::DatabaseInit{}
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
// clang-format on

} // namespace LunarDB::Moonlight::Implementation::Tests
