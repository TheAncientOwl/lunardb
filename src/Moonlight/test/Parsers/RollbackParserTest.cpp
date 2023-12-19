#include "Common/ParserTestIncludes.hpp"

#define QUERY_TYPE Rollback

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

TEST(RollbackParserTest, success01)
{
    const auto query = "rollback";
    const auto expected = Init::RollbackInit{}.hash(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(RollbackParserTest, success02)
{
    const auto query = "rollback;";
    const auto expected = Init::RollbackInit{}.hash(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(RollbackParserTest, success03)
{
    const auto query = "rollback a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e";
    const auto expected = Init::RollbackInit{}.hash("a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e");

    EXPECT_SUCCESS(query, expected);
}

TEST(RollbackParserTest, success04)
{
    const auto query = "rollback a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e;";
    const auto expected = Init::RollbackInit{}.hash("a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e");

    EXPECT_SUCCESS(query, expected);
}

TEST(RollbackParserTest, fail01)
{
    EXPECT_FAIL("rollback a591a6d40b f420404a011733cfb7b19 0d62c65bf0bcda32b57b27 7d9ad9f146e");
    EXPECT_FAIL("rollback a591a6d40b f420404a011733cfb7b19 0d62c65bf0bcda32b57b27 7d9ad9f146e;");
}

} // namespace LunarDB::Moonlight::Implementation::Tests
