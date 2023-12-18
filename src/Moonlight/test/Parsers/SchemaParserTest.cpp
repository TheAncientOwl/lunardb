#include <gtest/gtest.h>

#include "Helpers/QueryDataHelpers.hpp"
#include "ParsedQuery.hpp"

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

// TODO: provide unit tests
TEST(SchemaParserTest, dummy)
{
    const auto query = "schema";

    const auto out = API::ParsedQuery::from(query).get<Schema>();

    const Schema expected{};

    EXPECT_EQ(out, expected);
}

} // namespace LunarDB::Moonlight::Implementation::Tests
