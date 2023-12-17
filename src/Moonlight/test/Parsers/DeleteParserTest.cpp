#include <gtest/gtest.h>

#include "QueryDataHelpers.hpp"
#include "ParsedQuery.hpp"

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

// TODO: provide unit tests
TEST(DeleteParserTest, dummy)
{
    const auto query = "delete";

    const auto out = API::ParsedQuery::from(query).get<Delete>();

    const Delete expected{};

    EXPECT_EQ(out, expected);
}

} // namespace LunarDB::Moonlight::Implementation::Tests
