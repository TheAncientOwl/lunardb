#include <gtest/gtest.h>

#include "ParsedQuery.hpp"

#define EXPECT_MAKE_PARSED_QUERY_SUCCESS(Type)                    \
    EXPECT_EQ(                                                    \
        API::ParsedQuery::make<Common::QueryData::Type>().type(), \
        Common::QueryData::Primitives::EQueryType::Type)

namespace LunarDB::Moonlight::API::Tests {

// clang-format off
TEST(Moonlight_ParsedQueryTest, makeParsedQueries)
{
    EXPECT_MAKE_PARSED_QUERY_SUCCESS(Create);
    EXPECT_MAKE_PARSED_QUERY_SUCCESS(Drop);
    EXPECT_MAKE_PARSED_QUERY_SUCCESS(Migrate);
    EXPECT_MAKE_PARSED_QUERY_SUCCESS(Truncate);
    EXPECT_MAKE_PARSED_QUERY_SUCCESS(Rename);
    EXPECT_MAKE_PARSED_QUERY_SUCCESS(Select);
    EXPECT_MAKE_PARSED_QUERY_SUCCESS(Insert);
    EXPECT_MAKE_PARSED_QUERY_SUCCESS(Update);
    EXPECT_MAKE_PARSED_QUERY_SUCCESS(Delete);
    EXPECT_MAKE_PARSED_QUERY_SUCCESS(Grant);
    EXPECT_MAKE_PARSED_QUERY_SUCCESS(Revoke);
    EXPECT_MAKE_PARSED_QUERY_SUCCESS(Commit);
    EXPECT_MAKE_PARSED_QUERY_SUCCESS(Rollback);
    EXPECT_MAKE_PARSED_QUERY_SUCCESS(SavePoint);
    EXPECT_MAKE_PARSED_QUERY_SUCCESS(Database);
    EXPECT_MAKE_PARSED_QUERY_SUCCESS(Rebind);
    EXPECT_MAKE_PARSED_QUERY_SUCCESS(Schema);
    EXPECT_MAKE_PARSED_QUERY_SUCCESS(User);
    EXPECT_MAKE_PARSED_QUERY_SUCCESS(Auth);
}
// clang-format on

} // namespace LunarDB::Moonlight::API::Tests
