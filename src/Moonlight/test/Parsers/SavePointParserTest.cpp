#include <gtest/gtest.h>

#include "QueryDataHelpers/Init.hpp"
#include "QueryDataHelpers/Operators.hpp"
#include "ParsedQuery.hpp"

#define EXPECT_SUCCESS(query, expected) \
    const auto out = API::ParsedQuery::from(query).get<SavePoint>(); \
    EXPECT_EQ(out, expected)

#define EXPECT_FAIL(query) \
    EXPECT_THROW(API::ParsedQuery::from(query).get<SavePoint>(), std::runtime_error)

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

TEST(SavePointParserTest, success01)
{
    const auto query = "savepoint";
    const auto expected = Init::SavePointInit{}.hash(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(SavePointParserTest, success02)
{
    const auto query = "savepoint;";
    const auto expected = Init::SavePointInit{}.hash(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(SavePointParserTest, success03)
{
    const auto query = "savepoint a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e";
    const auto expected = Init::SavePointInit{}.hash("a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e");

    EXPECT_SUCCESS(query, expected);
}

TEST(SavePointParserTest, success04)
{
    const auto query = "savepoint a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e;";
    const auto expected = Init::SavePointInit{}.hash("a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e");

    EXPECT_SUCCESS(query, expected);
}

TEST(SavePointParserTest, fail01)
{
    EXPECT_FAIL("savepoint a591a6d40b f420404a011733cfb7b19 0d62c65bf0bcda32b57b27 7d9ad9f146e");
    EXPECT_FAIL("savepoint a591a6d40b f420404a011733cfb7b19 0d62c65bf0bcda32b57b27 7d9ad9f146e;");
}

} // namespace LunarDB::Moonlight::Implementation::Tests
