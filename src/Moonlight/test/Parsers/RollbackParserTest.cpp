#include <gtest/gtest.h>

#include "QueryDataHelpers.hpp"
#include "ParsedQuery.hpp"

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

TEST(RollbackParserTest, dummy)
{
    const auto query = "rollback";

    const auto out = API::ParsedQuery::from(query).get<Rollback>();

    const Rollback expected{};

    EXPECT_EQ(out, expected) << "Expected: " << expected << "\nActual: " << out;
}

} // namespace LunarDB::Moonlight::Implementation::Tests
