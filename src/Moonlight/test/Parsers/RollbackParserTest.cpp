#include "QueryParserTest.hpp"

#define QUERY_TYPE Rollback

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace Common::QueryData;

// clang-format off
TEST(Moonlight_RollbackParserTest, success01)
{
    auto const query = "rollback";
    auto const expected = Init::RollbackInit{}.hash(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_RollbackParserTest, success02)
{
    auto const query = "rollback;";
    auto const expected = Init::RollbackInit{}.hash(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_RollbackParserTest, success03)
{
    auto const query = "rollback a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e";
    auto const expected = Init::RollbackInit{}.hash("a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_RollbackParserTest, success04)
{
    auto const query = "rollback a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e;";
    auto const expected = Init::RollbackInit{}.hash("a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_RollbackParserTest, fail01)
{
    EXPECT_FAIL("rollback a591a6d40b f420404a011733cfb7b19 0d62c65bf0bcda32b57b27 7d9ad9f146e");
    EXPECT_FAIL("rollback a591a6d40b f420404a011733cfb7b19 0d62c65bf0bcda32b57b27 7d9ad9f146e;");
}
// clang-format on

} // namespace LunarDB::Moonlight::Implementation::Tests
