#include <gtest/gtest.h>

#include "Errors.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Utils::Tests {

namespace CppExtensions = LunarDB::Common::CppExtensions;
using namespace std::literals;

// clang-format off
TEST(Moonlight_UtilsTest, split01)
{
    auto const str = "  field1  ,  field2  ";

    auto const out = split(str, ',', ESplitModifier::EscapeQuotes);

    std::vector<std::string_view> expected = {
        "field1",
        "field2"
    };

    EXPECT_EQ(out, expected);
}

TEST(Moonlight_UtilsTest, split02)
{
    auto const str = R"(  field1  ,  field2, "some string,q", field3  )";

    auto const out = split(str, ',', ESplitModifier::EscapeQuotes);

    std::vector<std::string_view> expected = {
        "field1",
        "field2",
        R"(some string,q)",
        "field3"
    };

    EXPECT_EQ(out.size(), expected.size());
    for (std::size_t index = 0; index < std::min(out.size(), expected.size()); index++)
    {
        EXPECT_EQ(out[index], expected[index]);
    }
    EXPECT_EQ(out, expected);
}

TEST(Moonlight_UtilsTest, split03)
{
    auto const str = R"(  field1  ,  field2, "some string,q", field3, "some other string \"with quotes", and commas"  )";

    auto const out = split(str, ',', ESplitModifier::EscapeQuotes);

    std::vector<std::string_view> expected = {
        "field1",
        "field2",
        R"(some string,q)",
        "field3",
        R"(some other string \"with quotes)",
        R"(and commas")"
    };

    EXPECT_EQ(out.size(), expected.size());
    for (std::size_t index = 0; index < std::min(out.size(), expected.size()); index++)
    {
        EXPECT_EQ(out[index], expected[index]);
    }
    EXPECT_EQ(out, expected);
}

TEST(Moonlight_UtilsTest, split04)
{
    auto const str = R"(  field1  ,  field2, "some string,q", field3, "some other string \"with quotes\", and commas"  )";

    auto const out = split(str, ',', ESplitModifier::EscapeQuotes);

    std::vector<std::string_view> expected = {
        "field1",
        "field2",
        R"(some string,q)",
        "field3",
        R"(some other string \"with quotes\", and commas)",
    };

    EXPECT_EQ(out.size(), expected.size());
    for (std::size_t index = 0; index < std::min(out.size(), expected.size()); index++)
    {
        EXPECT_EQ(out[index], expected[index]);
    }
    EXPECT_EQ(out, expected);
}

TEST(Moonlight_UtilsTest, split05)
{
    auto const str = R"(  field1, field2, "", field3  )";

    auto const out = split(str, ',', ESplitModifier::EscapeQuotes);

    std::vector<std::string_view> expected = {
        "field1",
        "field2",
        "field3"
    };

    EXPECT_EQ(out, expected);
}

TEST(Moonlight_UtilsTest, split06)
{
    auto const str = R"(  field1, field2, "", ", field3  )";

    auto const out = split(str, ',', ESplitModifier::EscapeQuotes);

    std::vector<std::string_view> expected = {
        "field1",
        "field2",
        R"(", field3)"
    };

    EXPECT_EQ(out, expected);
}

TEST(Moonlight_UtilsTest, split07)
{
    auto const str = R"(  field1, field2, "", ", field3  )";

    auto const out = split(str);

    std::vector<std::string_view> expected = {
        "field1",
        "field2",
        R"("")",
        R"(")",
        R"(field3)"
    };

    EXPECT_EQ(out, expected);
}

TEST(Moonlight_UtilsTest, split08)
{
    auto const str = R"(history1 => %%[{"username1":"user1","message1":"m1","time":12345}]%%, history2 => %%[{"username2":"user2","message2":"m2","time":12345}]%%)";

    auto const out = split(str, ',', ESplitModifier::EscapeQuotes, true);

    std::vector<std::string_view> expected = {
        R"(history1 => %%[{"username1":"user1","message1":"m1","time":12345}]%%)",
        R"(history2 => %%[{"username2":"user2","message2":"m2","time":12345}]%%)",
    };

    EXPECT_EQ(out, expected);
    EXPECT_EQ(out.size(), expected.size());
    for (std::size_t index = 0; index < std::min(out.size(), expected.size()); index++)
    {
        EXPECT_EQ(out[index], expected[index]);
    }
}

TEST(Moonlight_UtilsTest, parseResolutionOperator)
{
    {
        auto const [left, right] = parseResolutionOperator("String1::String2");
        EXPECT_EQ(left, "String1"sv);
        EXPECT_EQ(right, "String2"sv);
    }

    {
        auto const [left, right] = parseResolutionOperator("::String2");
        EXPECT_EQ(left, ""sv);
        EXPECT_EQ(right, "String2"sv);
    }

    {
        auto const [left, right] = parseResolutionOperator("String1::");
        EXPECT_EQ(left, "String1"sv);
        EXPECT_EQ(right, ""sv);
    }

    EXPECT_THROW({ std::ignore = parseResolutionOperator(""); }, Errors::ParserError);
    EXPECT_THROW({ std::ignore = parseResolutionOperator("String1:String2"); }, Errors::ParserError);
    EXPECT_THROW({ std::ignore = parseResolutionOperator("String1 String2"); }, Errors::ParserError);
    EXPECT_THROW({ std::ignore = parseResolutionOperator("String1:dadsd:String2"); }, Errors::ParserError);
}
// clang-format on

} // namespace LunarDB::Moonlight::Utils::Tests
