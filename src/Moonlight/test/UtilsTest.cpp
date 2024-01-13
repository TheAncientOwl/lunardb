#include <gtest/gtest.h>

#include "Errors.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Utils::Tests {

using namespace CppExtensions;
using namespace std::literals;

TEST(UtilsTest, split01)
{
    const auto str = "  field1  ,  field2  ";

    const auto out = split(str, ',', ESplitModifier::EscapeQuotes);

    std::vector<std::string_view> expected = {
        "field1",
        "field2"
    };

    EXPECT_EQ(out, expected);
}

TEST(UtilsTest, split02)
{
    const auto str = R"(  field1  ,  field2, "some string,q", field3  )";

    const auto out = split(str, ',', ESplitModifier::EscapeQuotes);

    std::vector<std::string_view> expected = {
        "field1",
        "field2",
        R"(some string,q)",
        "field3"
    };

    EXPECT_EQ(out, expected);
}

TEST(UtilsTest, split03)
{
    const auto str = R"(  field1  ,  field2, "some string,q", field3, "some other string \"with quotes", and commas"  )";

    const auto out = split(str, ',', ESplitModifier::EscapeQuotes);

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

TEST(UtilsTest, split04)
{
    const auto str = R"(  field1  ,  field2, "some string,q", field3, "some other string \"with quotes\", and commas"  )";

    const auto out = split(str, ',', ESplitModifier::EscapeQuotes);

    std::vector<std::string_view> expected = {
        "field1",
        "field2",
        R"(some string,q)",
        "field3",
        R"(some other string \"with quotes\", and commas)",
    };

    EXPECT_EQ(out, expected);
}

TEST(UtilsTest, split05)
{
    const auto str = R"(  field1, field2, "", field3  )";

    const auto out = split(str, ',', ESplitModifier::EscapeQuotes);

    std::vector<std::string_view> expected = {
        "field1",
        "field2",
        "field3"
    };

    EXPECT_EQ(out, expected);
}

TEST(UtilsTest, split06)
{
    const auto str = R"(  field1, field2, "", ", field3  )";

    const auto out = split(str, ',', ESplitModifier::EscapeQuotes);

    std::vector<std::string_view> expected = {
        "field1",
        "field2",
        R"(", field3)"
    };

    EXPECT_EQ(out, expected);
}

TEST(UtilsTest, split07)
{
    const auto str = R"(  field1, field2, "", ", field3  )";

    const auto out = split(str);

    std::vector<std::string_view> expected = {
        "field1",
        "field2",
        R"("")",
        R"(")",
        R"(field3)"
    };

    EXPECT_EQ(out, expected);
}

TEST(UtilsTest, parseResolutionOperator)
{
    {
        const auto [left, right] = parseResolutionOperator("String1::String2");
        EXPECT_EQ(left, "String1"sv);
        EXPECT_EQ(right, "String2"sv);
    }

    {
        const auto [left, right] = parseResolutionOperator("::String2");
        EXPECT_EQ(left, ""sv);
        EXPECT_EQ(right, "String2"sv);
    }

    {
        const auto [left, right] = parseResolutionOperator("String1::");
        EXPECT_EQ(left, "String1"sv);
        EXPECT_EQ(right, ""sv);
    }

    EXPECT_THROW({ std::ignore = parseResolutionOperator(""); }, Errors::ParserError);
    EXPECT_THROW({ std::ignore = parseResolutionOperator("String1:String2"); }, Errors::ParserError);
    EXPECT_THROW({ std::ignore = parseResolutionOperator("String1 String2"); }, Errors::ParserError);
    EXPECT_THROW({ std::ignore = parseResolutionOperator("String1:dadsd:String2"); }, Errors::ParserError);
}

} // namespace LunarDB::Moonlight::Utils::Tests
