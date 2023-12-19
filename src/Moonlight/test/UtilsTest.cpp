#include <gtest/gtest.h>

#include "Common/Utils.hpp"

#define EXPECT_TRIM_EQ(func, trimmed, not_trimmed) { auto str = not_trimmed; func(str); EXPECT_EQ(trimmed, str); }

namespace LunarDB::Moonlight::Utils::Tests {

using namespace std::literals;

TEST(UtilsTest, ltrim)
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

TEST(UtilsTest, rtrim)
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

TEST(UtilsTest, trim)
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

TEST(UtilsTest, equalsIgnoreTest)
{
    EXPECT_TRUE(equalsIgnoreCase("", ""));
    EXPECT_TRUE(equalsIgnoreCase("qWertYUIop", "QWErtyUIOp"));
    EXPECT_TRUE(equalsIgnoreCase("some string \r :)", "some string \r :)"));

    EXPECT_FALSE(equalsIgnoreCase("qwerty", "QWERT"));
    EXPECT_FALSE(equalsIgnoreCase("somestr1", "somestr2"));
}

TEST(UtilsTest, startsWithIgnoreCase)
{
    EXPECT_TRUE(startsWithIgnoreCase("", ""));
    EXPECT_TRUE(startsWithIgnoreCase("qWertYUIopASDFGHJKL", "QWErtyUIOp"));
    EXPECT_TRUE(startsWithIgnoreCase("some string \r :) WITH SOME MORE STRINGS", "some string \r :)"));

    EXPECT_FALSE(startsWithIgnoreCase("qwerty", "qQWERT"));
    EXPECT_FALSE(startsWithIgnoreCase("somestr1", "ssomestr2"));
}

TEST(UtilsTest, splitAtComma01)
{
    const auto str = "  field1  ,  field2  ";

    const auto out = splitAtComma(str, ESplitModifier::EscapeQuotes);

    std::vector<std::string_view> expected = {
        "field1",
        "field2"
    };

    EXPECT_EQ(out, expected);
}

TEST(UtilsTest, splitAtComma02)
{
    const auto str = R"(  field1  ,  field2, "some string,q", field3  )";

    const auto out = splitAtComma(str, ESplitModifier::EscapeQuotes);

    std::vector<std::string_view> expected = {
        "field1",
        "field2",
        R"(some string,q)",
        "field3"
    };

    EXPECT_EQ(out, expected);
}

TEST(UtilsTest, splitAtComma03)
{
    const auto str = R"(  field1  ,  field2, "some string,q", field3, "some other string \"with quotes", and commas"  )";

    const auto out = splitAtComma(str, ESplitModifier::EscapeQuotes);

    std::vector<std::string_view> expected = {
        "field1",
        "field2",
        R"(some string,q)",
        "field3",
        R"(some other string \"with quotes)",
        R"(and commas")"
    };

    EXPECT_EQ(out, expected);
}

TEST(UtilsTest, splitAtComma04)
{
    const auto str = R"(  field1  ,  field2, "some string,q", field3, "some other string \"with quotes\", and commas"  )";

    const auto out = splitAtComma(str, ESplitModifier::EscapeQuotes);

    std::vector<std::string_view> expected = {
        "field1",
        "field2",
        R"(some string,q)",
        "field3",
        R"(some other string \"with quotes\", and commas)",
    };

    EXPECT_EQ(out, expected);
}

TEST(UtilsTest, splitAtComma05)
{
    const auto str = R"(  field1, field2, "", field3  )";

    const auto out = splitAtComma(str, ESplitModifier::EscapeQuotes);

    std::vector<std::string_view> expected = {
        "field1",
        "field2",
        "field3"
    };

    EXPECT_EQ(out, expected);
}

TEST(UtilsTest, splitAtComma06)
{
    const auto str = R"(  field1, field2, "", ", field3  )";

    const auto out = splitAtComma(str, ESplitModifier::EscapeQuotes);

    std::vector<std::string_view> expected = {
        "field1",
        "field2",
        R"(", field3)"
    };

    EXPECT_EQ(out, expected);
}

TEST(UtilsTest, splitAtComma07)
{
    const auto str = R"(  field1, field2, "", ", field3  )";

    const auto out = splitAtComma(str);

    std::vector<std::string_view> expected = {
        "field1",
        "field2",
        R"("")",
        R"(")",
        R"(field3)"
    };

    EXPECT_EQ(out, expected);
}

} // namespace LunarDB::Moonlight::Utils::Tests
