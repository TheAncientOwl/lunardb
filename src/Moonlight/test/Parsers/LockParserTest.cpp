#include <gtest/gtest.h>

#include "QueryDataHelpers.hpp"
#include "ParsedQuery.hpp"

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

// TODO: provide unit tests
TEST(LockParserTest, dummy)
{
    const auto query = "lock";

    const auto out = API::ParsedQuery::from(query).get<Lock>();

    const Lock expected{};

    EXPECT_EQ(out, expected);
}

} // namespace LunarDB::Moonlight::Implementation::Tests
