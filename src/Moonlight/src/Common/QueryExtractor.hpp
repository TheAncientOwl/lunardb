#pragma once

#include <string_view>
#include <vector>
#include <array>
#include <tuple>

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

    template<std::size_t N>
    decltype(auto) extractTuple();

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

private:
    template <std::size_t N, std::size_t Index = 0>
    struct StringViewTupleGenerator
    {
        static auto generate(const std::array<std::string_view, N>& views)
        {
            if constexpr (Index < N)
            {
                return std::tuple_cat(
                    std::make_tuple(views[Index]),
                    StringViewTupleGenerator<N, Index + 1>::generate(views)
                );
            }
            else
            {
                return std::make_tuple();
            }
        }
    };
};

template<std::size_t N>
inline decltype(auto) QueryExtractor::extractTuple()
{
    std::array<std::string_view, N> parts{};

    for (std::size_t i = 0; i < N; ++i)
    {
        parts[i] = extractOne();
    }

    return StringViewTupleGenerator<N>::generate(parts);
}

} // namespace LunarDB::Moonlight::Implementation
