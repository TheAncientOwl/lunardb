#include <gtest/gtest.h>

#include "ParsedQuery.hpp"
#include "QueryDataHelpers.hpp"

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

TEST(CreateParserTest, dummy)
{
    const auto query = "create";

    const auto out = API::ParsedQuery::from(query).get<Create>();

    const Create expected{};

    EXPECT_EQ(out, expected) << "Expected: " << expected << "\nActual: " << out;
}

} // namespace LunarDB::Moonlight::Implementation::Tests
