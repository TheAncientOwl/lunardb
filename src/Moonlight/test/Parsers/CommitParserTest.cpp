#include <gtest/gtest.h>

#include "QueryDataHelpers.hpp"
#include "ParsedQuery.hpp"

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

// TODO: provide unit tests
TEST(CommitParserTest, dummy)
{
    const auto query = "commit";

    const auto out = API::ParsedQuery::from(query).get<Commit>();

    const Commit expected{};

    EXPECT_EQ(out, expected);
}

} // namespace LunarDB::Moonlight::Implementation::Tests
