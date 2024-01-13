#include <gtest/gtest.h>

#include "StringUtils.hpp"

#define EXPECT_TRIM_EQ(func, trimmed, not_trimmed) { auto str = not_trimmed; func(str); EXPECT_EQ(trimmed, str); }

namespace LunarDB::CppExtensions::StringUtils::Tests {

using namespace std::literals;

TEST(StringUtilsTest, ltrim)
{
    EXPECT_TRIM_EQ(ltrim, ""sv, "\r\r\r\t\t\t       "sv);
    EXPECT_TRIM_EQ(ltrim, ""sv, ""sv);
    EXPECT_TRIM_EQ(ltrim, "somestr"sv, "somestr"sv);
    EXPECT_TRIM_EQ(ltrim, "some string"sv, "   some string"sv);
    EXPECT_TRIM_EQ(ltrim, "some string"sv, "\t\t\tsome string"sv);
    EXPECT_TRIM_EQ(ltrim, "some string"sv, "\v\v\vsome string"sv);
    EXPECT_TRIM_EQ(ltrim, "some string"sv, "\f\f\fsome string"sv);
    EXPECT_TRIM_EQ(ltrim, "some string"sv, "\v\v\vsome string"sv);
    EXPECT_TRIM_EQ(ltrim, "some string"sv, "\n\n\nsome string"sv);
    EXPECT_TRIM_EQ(ltrim, "some string"sv, "  \t  \v  \f  \t    \v     \t \rsome string"sv);
}

TEST(StringUtilsTest, rtrim)
{
    EXPECT_TRIM_EQ(rtrim, ""sv, "\r\r\r\t\t\t       "sv);
    EXPECT_TRIM_EQ(rtrim, ""sv, ""sv);
    EXPECT_TRIM_EQ(rtrim, "somestr"sv, "somestr"sv);
    EXPECT_TRIM_EQ(rtrim, "some string"sv, "some string   "sv);
    EXPECT_TRIM_EQ(rtrim, "some string"sv, "some string\t\t\t"sv);
    EXPECT_TRIM_EQ(rtrim, "some string"sv, "some string\v\v\v"sv);
    EXPECT_TRIM_EQ(rtrim, "some string"sv, "some string\f\f\f"sv);
    EXPECT_TRIM_EQ(rtrim, "some string"sv, "some string\v\v\v"sv);
    EXPECT_TRIM_EQ(rtrim, "some string"sv, "some string\n\n\n"sv);
    EXPECT_TRIM_EQ(rtrim, "some string"sv, "some string  \t  \v  \f  \t    \v     \t \r"sv);
}

TEST(StringUtilsTest, trim)
{
    EXPECT_TRIM_EQ(trim, ""sv, "\r\r\r\t\t\t       "sv);
    EXPECT_TRIM_EQ(trim, ""sv, ""sv);
    EXPECT_TRIM_EQ(trim, "somestr"sv, "somestr"sv);
    EXPECT_TRIM_EQ(trim, "some string"sv, "   some string   "sv);
    EXPECT_TRIM_EQ(trim, "some string"sv, "\t\t\tsome string\t\t\t"sv);
    EXPECT_TRIM_EQ(trim, "some string"sv, "\v\v\vsome string\v\v\v"sv);
    EXPECT_TRIM_EQ(trim, "some string"sv, "\f\f\fsome string\f\f\f"sv);
    EXPECT_TRIM_EQ(trim, "some string"sv, "\v\v\vsome string\v\v\v"sv);
    EXPECT_TRIM_EQ(trim, "some string"sv, "\n\n\nsome string\n\n\n"sv);
    EXPECT_TRIM_EQ(trim, "some string"sv, "  \t  \v  \f  \t    \v     \t \rsome string  \t  \v  \f  \t    \v     \t \r"sv);
}

TEST(StringUtilsTest, equalsIgnoreTest)
{
    EXPECT_TRUE(equalsIgnoreCase("", ""));
    EXPECT_TRUE(equalsIgnoreCase("qWertYUIop", "QWErtyUIOp"));
    EXPECT_TRUE(equalsIgnoreCase("some string \r :)", "some string \r :)"));

    EXPECT_FALSE(equalsIgnoreCase("qwerty", "QWERT"));
    EXPECT_FALSE(equalsIgnoreCase("somestr1", "somestr2"));
}

TEST(StringUtilsTest, startsWithIgnoreCase)
{
    EXPECT_TRUE(startsWithIgnoreCase("", ""));
    EXPECT_TRUE(startsWithIgnoreCase("qWertYUIopASDFGHJKL", "QWErtyUIOp"));
    EXPECT_TRUE(startsWithIgnoreCase("some string \r :) WITH SOME MORE STRINGS", "some string \r :)"));

    EXPECT_FALSE(startsWithIgnoreCase("qwerty", "qQWERT"));
    EXPECT_FALSE(startsWithIgnoreCase("somestr1", "ssomestr2"));
}

} // namespace LunarDB::CppExtensions::StringUtils::Tests
