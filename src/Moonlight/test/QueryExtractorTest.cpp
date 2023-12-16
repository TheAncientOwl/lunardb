#include <gtest/gtest.h>

#include "QueryExtractor.hpp"

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
    auto query{ "  some \t \n words \t\t12345  " };

    QueryExtractor extractor(query);

    EXPECT_EQ(extractor.extractMultiple(1), std::vector<std::string_view>{ "some"sv });
    EXPECT_FALSE(extractor.empty());
    EXPECT_EQ(extractor.extractMultiple(1), std::vector<std::string_view>{"words"sv});
    EXPECT_FALSE(extractor.empty());
    EXPECT_EQ(extractor.extractMultiple(1), std::vector<std::string_view> {"12345"sv});
    EXPECT_TRUE(extractor.empty());
    EXPECT_EQ(extractor.extractMultiple(1), std::vector<std::string_view>{""sv});

    extractor = QueryExtractor(query);
    EXPECT_EQ(extractor.extractMultiple(2), (std::vector<std::string_view>{"some"sv, "words"sv}));
    EXPECT_FALSE(extractor.empty());
    EXPECT_EQ(extractor.extractMultiple(3), (std::vector<std::string_view>{"12345"sv, ""sv, ""sv}));
    EXPECT_TRUE(extractor.empty());
}

} // namespace LunarDB::Moonlight::Implementation::Tests
