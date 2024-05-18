#include "QueryParserTest.hpp"

#define QUERY_TYPE User

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace Common::QueryData;

// clang-format off
TEST(Moonlight_UserParserTest, success01)
{
    auto const query = "user create PopescuIon password pwd1234;";
    auto const expected = Init::UserInit{}.name("PopescuIon").action(Primitives::EUserActionType::Create).password("pwd1234");

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_UserParserTest, success02)
{
    auto const query = "user remove PopescuIon";
    auto const expected = Init::UserInit{}.name("PopescuIon").action(Primitives::EUserActionType::Remove).password(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_UserParserTest, fail01)
{
    EXPECT_FAIL("user create PopescuIon password");
    EXPECT_FAIL("user create PopescuIon pwd1234");
    EXPECT_FAIL("create PopescuIon");
    EXPECT_FAIL("create PopescuIon password pwd1234");
    EXPECT_FAIL("user PopescuIon");
    EXPECT_FAIL("user create");
    EXPECT_FAIL("user createsss PopescuIon");
    EXPECT_FAIL("user crt PopescuIon");
    EXPECT_FAIL("user crt Popescu Ion");
    EXPECT_FAIL("user Idk PopescuIon");

    EXPECT_FAIL("remove PopescuIon");
    EXPECT_FAIL("user PopescuIon");
    EXPECT_FAIL("user remove");
    EXPECT_FAIL("user removesss PopescuIon");
    EXPECT_FAIL("user rmv PopescuIon");
    EXPECT_FAIL("user rmv Popescu Ion");
    EXPECT_FAIL("user Idk PopescuIon");
}
// clang-format on

} // namespace LunarDB::Moonlight::Implementation::Tests
