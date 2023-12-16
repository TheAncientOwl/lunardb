#include <gtest/gtest.h>

#include "QueryDataHelpers.hpp"
#include "ParsedQuery.hpp"

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

TEST(UpdateParserTest, dummy)
{
    const auto query = "update";

    const auto out = API::ParsedQuery::from(query).get<Update>();

    const Update expected{};

    EXPECT_EQ(out, expected) << "Expected: " << expected << "\nActual: " << out;
}

} // namespace LunarDB::Moonlight::Implementation::Tests
