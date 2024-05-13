#include "QueryParserTest.hpp"

#define QUERY_TYPE Commit

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace Common::QueryData;

// clang-format off
TEST(Moonlight_CommitParserTest, success01)
{
    auto const query = "commit";
    auto const expected = Init::CommitInit{};

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_CommitParserTest, fail01)
{
    EXPECT_FAIL("commit a591a6d40b f420404a011733cfb7b19 0d62c65bf0bcda32b57b27 7d9ad9f146e");
    EXPECT_FAIL("commit a591a6d40b f420404a011733cfb7b19 0d62c65bf0bcda32b57b27 7d9ad9f146e;");
}
// clang-format on

} // namespace LunarDB::Moonlight::Implementation::Tests
