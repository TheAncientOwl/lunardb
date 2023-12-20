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
    template<std::size_t Size>
    std::vector<std::string_view> extractMultiple();

    template<std::size_t Size>
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
    template <std::size_t Size, std::size_t Index = 0>
    struct StringViewTupleGenerator
    {
        static auto generate(const std::array<std::string_view, Size>& views)
        {
            if constexpr (Index < Size)
            {
                return std::tuple_cat(
                    std::make_tuple(views[Index]),
                    StringViewTupleGenerator<Size, Index + 1>::generate(views)
                );
            }
            else
            {
                return std::make_tuple();
            }
        }
    };
};

template<std::size_t Size>
inline std::vector<std::string_view> QueryExtractor::extractMultiple()
{
    std::vector<std::string_view> multiple{};
    multiple.reserve(Size);

    for (std::size_t i = 0; i < Size; ++i)
    {
        multiple.emplace_back(extractOne());
    }

    return multiple;
}

template<std::size_t Size>
inline decltype(auto) QueryExtractor::extractTuple()
{
    std::array<std::string_view, Size> parts{};

    for (std::size_t i = 0; i < Size; ++i)
    {
        parts[i] = extractOne();
    }

    return StringViewTupleGenerator<Size>::generate(parts);
}

} // namespace LunarDB::Moonlight::Implementation
