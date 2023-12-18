#include <gtest/gtest.h>

#include "QueryDataHelpers/Helpers.hpp"
#include "ParsedQuery.hpp"

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

// TODO: provide unit tests
TEST(SelectParserTest, dummy)
{
    const auto query = "select";

    const auto out = API::ParsedQuery::from(query).get<Select>();

    const Select expected{};

    EXPECT_EQ(out, expected);
}

} // namespace LunarDB::Moonlight::Implementation::Tests
