#include <gtest/gtest.h>

#include "QueryDataHelpers.hpp"
#include "ParsedQuery.hpp"

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

TEST(MigrateParserTest, dummy)
{
    const auto query = "migrate";

    const auto out = API::ParsedQuery::from(query).get<Migrate>();

    const Migrate expected{};

    EXPECT_EQ(out, expected) << "Expected: " << expected << "\nActual: " << out;
}

} // namespace LunarDB::Moonlight::Implementation::Tests
