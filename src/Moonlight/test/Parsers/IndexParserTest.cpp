#include <gtest/gtest.h>

#include "Helpers/QueryDataHelpers.hpp"
#include "ParsedQuery.hpp"

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

// TODO: provide unit tests
TEST(IndexParserTest, dummy)
{
    const auto query = "index";

    const auto out = API::ParsedQuery::from(query).get<Index>();

    const Index expected{};

    EXPECT_EQ(out, expected);
}

} // namespace LunarDB::Moonlight::Implementation::Tests
