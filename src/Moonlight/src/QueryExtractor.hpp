#pragma once

#include <string_view>
#include <vector>

namespace LunarDB::Moonlight::Implementation {

///
/// @brief Utility class to help parsing queries.
/// @note Each extract operation trims left the internal data.
///
class QueryExtractor
{
private:

public:
    ///
    /// @brief Trims query before storing.
    ///        Also remove semicolon at the end if existing.
    ///
    QueryExtractor(std::string_view query);

    ///
    /// @brief Removes the word from left part of query.
    ///        Breaks at whitespaces.
    /// @return Word form left part of query.
    ///
    std::string_view extractOne();

    ///
    /// @see QueryExtractor::extractOne, but multiple 
    ///
    std::vector<std::string_view> extractMultiple(std::size_t count);

    ///
    /// @brief Removes list sequence like [ word1, word2, ..., word3 ].
    ///
    std::vector<std::string_view> extractList();

    ///
    /// @brief Self explanatory
    ///
    std::string_view extractIfCondition();

    ///
    /// @brief Self explanatory
    ///
    std::string_view data() const;

    ///
    /// @brief Self explanatory
    ///
    bool empty() const;

private:
    std::string_view m_data;
};

} // namespace LunarDB::Moonlight::Implementation
