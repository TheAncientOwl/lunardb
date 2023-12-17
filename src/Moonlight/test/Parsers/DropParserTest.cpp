#include <gtest/gtest.h>

#include "QueryDataHelpers.hpp"
#include "ParsedQuery.hpp"

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

// TODO: provide unit tests
TEST(DropParserTest, dummy)
{
    const auto query = "drop";

    const auto out = API::ParsedQuery::from(query).get<Drop>();

    const Drop expected{};

    EXPECT_EQ(out, expected);
}

} // namespace LunarDB::Moonlight::Implementation::Tests
