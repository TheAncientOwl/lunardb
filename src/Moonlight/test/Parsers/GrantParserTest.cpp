#include <gtest/gtest.h>

#include "QueryDataHelpers.hpp"
#include "ParsedQuery.hpp"

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

TEST(GrantParserTest, dummy)
{
    const auto query = "grant";

    const auto out = API::ParsedQuery::from(query).get<Grant>();

    const Grant expected{};

    EXPECT_EQ(out, expected) << "Expected: " << expected << "\nActual: " << out;
}

} // namespace LunarDB::Moonlight::Implementation::Tests
