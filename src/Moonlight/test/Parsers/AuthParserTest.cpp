#include "QueryParserTest.hpp"

#define QUERY_TYPE Auth

#define EXPECT_AUTH_SUCCESS(query, expected)                                      \
    auto const parsed_query = Moonlight::Implementation::Auth::parse(query);      \
    auto const& out = parsed_query.get<LunarDB::Common::QueryData::QUERY_TYPE>(); \
    EXPECT_EQ(out, expected)

#define EXPECT_AUTH_FAIL(query)                                                          \
    EXPECT_THROW(                                                                        \
        Moonlight::API::parseQuery(query).get<LunarDB::Common::QueryData::QUERY_TYPE>(), \
        Moonlight::Errors::ParserError)

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace Common::QueryData;
using namespace std::string_view_literals;

TEST(Moonlight_AuthParserTest, success01)
{
    auto const query = "auth  someuser"sv;
    auto const expected = Init::AuthInit{}.username("someuser");

    EXPECT_AUTH_SUCCESS(query, expected);
}

TEST(Moonlight_AuthParserTest, success02)
{
    auto const query = "         auth  someuser    ;   "sv;
    auto const expected = Init::AuthInit{}.username("someuser");

    EXPECT_AUTH_SUCCESS(query, expected);
}

TEST(Moonlight_AuthParserTest, success03)
{
    auto const query = "auth  someuser "sv;
    auto const expected = Init::AuthInit{}.username("someuser");

    EXPECT_AUTH_SUCCESS(query, expected);
}

TEST(Moonlight_AuthParserTest, success04)
{
    auto const query = "  auth      someuser       ; "sv;
    auto const expected = Init::AuthInit{}.username("someuser");

    EXPECT_AUTH_SUCCESS(query, expected);
}

TEST(Moonlight_AuthParserTest, fail01)
{
    EXPECT_AUTH_FAIL("auth  sdada sdfwef");
    EXPECT_AUTH_FAIL("aauth SomeUser;");
}

} // namespace LunarDB::Moonlight::Implementation::Tests
