#include <gtest/gtest.h>

#include "Common/QueryExtractor.hpp"

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace std::literals;

TEST(QueryExtractor, extractOne)
{
    auto query{ "  some \t \n words \t\t12345  " };

    QueryExtractor extractor(query);

    EXPECT_EQ(extractor.extractOne(), "some"sv);
    EXPECT_FALSE(extractor.empty());
    EXPECT_EQ(extractor.extractOne(), "words"sv);
    EXPECT_FALSE(extractor.empty());
    EXPECT_EQ(extractor.extractOne(), "12345"sv);
    EXPECT_TRUE(extractor.empty());
    EXPECT_EQ(extractor.extractOne(), ""sv);
}

TEST(QueryExtractor, extractMultiple)
{
    const auto query{ "  some \t \n words \t\t12345  " };
    QueryExtractor extractor{ query };

    EXPECT_EQ(extractor.extractMultiple(1), std::vector<std::string_view>{ "some"sv });
    EXPECT_FALSE(extractor.empty());
    EXPECT_EQ(extractor.extractMultiple(1), std::vector<std::string_view>{"words"sv});
    EXPECT_FALSE(extractor.empty());
    EXPECT_EQ(extractor.extractMultiple(1), std::vector<std::string_view> {"12345"sv});
    EXPECT_TRUE(extractor.empty());
    EXPECT_EQ(extractor.extractMultiple(1), std::vector<std::string_view>{""sv});

    extractor = QueryExtractor{ query };
    EXPECT_EQ(extractor.extractMultiple(2), (std::vector<std::string_view>{"some"sv, "words"sv}));
    EXPECT_FALSE(extractor.empty());
    EXPECT_EQ(extractor.extractMultiple(3), (std::vector<std::string_view>{"12345"sv, ""sv, ""sv}));
    EXPECT_TRUE(extractor.empty());
}

TEST(QueryExtractor, extractList)
{
    QueryExtractor extractor{ "  [ word1, word2 \t \n, word3,   word4  ]" };

    auto expected = std::vector<std::string_view>{ "word1"sv, "word2"sv, "word3"sv, "word4"sv };
    EXPECT_EQ(extractor.extractList(), expected);
    EXPECT_TRUE(extractor.empty());
    EXPECT_EQ(extractor.data(), ""sv);
    EXPECT_THROW(extractor.extractList(), std::runtime_error);

    extractor = QueryExtractor{ " [ word1, word2, ] ]" };
    expected = std::vector<std::string_view>{ "word1"sv, "word2"sv };
    EXPECT_EQ(extractor.extractList(), expected);
    EXPECT_FALSE(extractor.empty());
    EXPECT_THROW(extractor.extractList(), std::runtime_error);
}

TEST(QueryExtractor, extractTuples)
{
    const auto query{ "  some \t \n words \t\t12345  " };
    QueryExtractor extractor{ query };

    const auto& [some] = extractor.extractTuple<1>();
    EXPECT_EQ(some, "some"sv);
    EXPECT_FALSE(extractor.empty());

    const auto& [words] = extractor.extractTuple<1>();
    EXPECT_EQ(words, "words"sv);
    EXPECT_FALSE(extractor.empty());

    const auto& [number] = extractor.extractTuple<1>();
    EXPECT_EQ(number, "12345"sv);
    EXPECT_TRUE(extractor.empty());

    extractor = QueryExtractor{ query };
    const auto& [_1, _2, _3, _4] = extractor.extractTuple<4>();
    EXPECT_EQ(_1, "some"sv);
    EXPECT_EQ(_2, "words"sv);
    EXPECT_EQ(_3, "12345"sv);
    EXPECT_EQ(_4, ""sv);
    EXPECT_TRUE(extractor.empty());
}

} // namespace LunarDB::Moonlight::Implementation::Tests
