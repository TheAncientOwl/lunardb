#include "QueryParserTest.hpp"

#define QUERY_TYPE SavePoint

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

// clang-format off
TEST(Moonlight_SavePointParserTest, success01)
{
    auto const query = "savepoint";
    auto const expected = Init::SavePointInit{}.hash(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_SavePointParserTest, success02)
{
    auto const query = "savepoint;";
    auto const expected = Init::SavePointInit{}.hash(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_SavePointParserTest, success03)
{
    auto const query = "savepoint a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e";
    auto const expected = Init::SavePointInit{}.hash("a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_SavePointParserTest, success04)
{
    auto const query = "savepoint a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e;";
    auto const expected = Init::SavePointInit{}.hash("a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_SavePointParserTest, fail01)
{
    EXPECT_FAIL("savepoint a591a6d40b f420404a011733cfb7b19 0d62c65bf0bcda32b57b27 7d9ad9f146e");
    EXPECT_FAIL("savepoint a591a6d40b f420404a011733cfb7b19 0d62c65bf0bcda32b57b27 7d9ad9f146e;");
}
// clang-format on

} // namespace LunarDB::Moonlight::Implementation::Tests
