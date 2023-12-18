#include <gtest/gtest.h>

#include "QueryDataHelpers/Helpers.hpp"
#include "ParsedQuery.hpp"

#define EXPECT_SUCCESS(query, expected) \
    const auto out = API::ParsedQuery::from(query).get<Commit>(); \
    EXPECT_EQ(out, expected)

#define EXPECT_FAIL(query) \
    EXPECT_THROW(API::ParsedQuery::from(query).get<Commit>(), std::runtime_error)

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

TEST(CommitParserTest, success01)
{
    const auto query = "commit";
    const auto expected = Init::CommitInit{}.hash(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(CommitParserTest, success02)
{
    const auto query = "commit;";
    const auto expected = Init::CommitInit{}.hash(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(CommitParserTest, fail01)
{
    EXPECT_FAIL("commit a591a6d40b f420404a011733cfb7b19 0d62c65bf0bcda32b57b27 7d9ad9f146e");
    EXPECT_FAIL("commit a591a6d40b f420404a011733cfb7b19 0d62c65bf0bcda32b57b27 7d9ad9f146e;");
}

} // namespace LunarDB::Moonlight::Implementation::Tests
