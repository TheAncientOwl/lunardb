#include <gtest/gtest.h>

#include "ParsedQuery.hpp"
#include "QueryDataHelpers/Init.hpp"
#include "QueryDataHelpers/Operators.hpp"

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

// TODO: provide unit tests
TEST(CreateParserTest, dummy)
{
    const auto query = "create";

    const auto out = API::ParsedQuery::from(query).get<Create>();

    const Create expected{};

    EXPECT_EQ(out, expected);
}

} // namespace LunarDB::Moonlight::Implementation::Tests
