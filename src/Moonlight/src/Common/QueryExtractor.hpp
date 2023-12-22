#pragma once

#include <algorithm>
#include <array>
#include <functional>
#include <ranges>
#include <set>
#include <string_view>
#include <tuple>
#include <utility>
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
    /// @brief Removes Size words from left part of query
    /// @return Tuple of Size string_views
    ///
    template<std::size_t Size>
    decltype(auto) extractTuple();

    ///
    /// @brief Removes list sequence like [ word1, word2, ..., word3 ].
    /// @param sep List elements separator, default ','
    /// @param bound_chars Characters that define the list, Ex. { '[', ']' }
    /// @return List of words as string_views
    ///
    std::vector<std::string_view> extractList(char sep = ',', std::pair<char, char> bound_chars = { '[', ']' });

    ///
    /// @brief Removes list sequence like [ word1, word2, ..., word3 ].
    /// @tparam T Final type of list returned elements
    /// @param parser Function string_view -> T
    /// @param sep List elements separator, default ','
    /// @param bound_chars Characters that define the list, Ex. { '[', ']' }
    /// @return List of parsed words to T
    ///
    template<typename T>
    std::vector<T> extractList(std::function<T(std::string_view)> parser, char sep = ',', std::pair<char, char> bound_chars = { '[', ']' });

    ///
    /// @brief Removes list sequence like [ word1, word2, ..., word3 ].
    /// @tparam T Final type of list returned elements
    /// @param parser Function string_view -> T
    /// @param sep List elements separator, default ','
    /// @param bound_chars Characters that define the list, Ex. { '[', ']' }
    /// @return List of unique parsed words to T
    ///
    template<typename T>
    std::vector<T> extractUniqueList(std::function<T(std::string_view)> parser, char sep = ',', std::pair<char, char> bound_chars = { '[', ']' });

    ///
    /// @brief Self explanatory
    ///
    std::string_view data() const;

    ///
    /// @brief Self explanatory
    ///
    bool empty() const;

    ///
    /// @brief Self explanatory
    ///
    void remove_prefix(std::size_t size);

private:
    std::string_view m_data;

private:
    template <std::size_t Size, std::size_t Index = 0>
    auto makeTuple(const std::array<std::string_view, Size>& views)
    {
        if constexpr (Index < Size)
        {
            return std::tuple_cat(
                std::make_tuple(views[Index]),
                makeTuple<Size, Index + 1>(views)
            );
        }
        else
        {
            return std::make_tuple();
        }
    }
};

template<std::size_t Size>
inline decltype(auto) QueryExtractor::extractTuple()
{
    std::array<std::string_view, Size> arr{};

    for (const auto i : std::ranges::iota_view<std::size_t, std::size_t>(0, Size))
    {
        arr[i] = extractOne();
    }

    return makeTuple<Size>(arr);
}

template<typename T>
inline std::vector<T> QueryExtractor::extractList(std::function<T(std::string_view)> parser, char sep, std::pair<char, char> bound_chars)
{
    const auto values = extractList(sep, bound_chars);

    std::vector<T> out{};
    out.reserve(values.size());
    std::transform(values.begin(), values.end(), std::back_inserter(out), parser);

    return out;
}

template<typename T>
inline std::vector<T> QueryExtractor::extractUniqueList(std::function<T(std::string_view)> parser, char sep, std::pair<char, char> bound_chars)
{
    const auto values = extractList(sep, bound_chars);

    std::set<T> set{};
    std::transform(values.begin(), values.end(), std::inserter(set, set.begin()), parser);

    std::vector<T> out{};
    out.reserve(set.size());
    for (auto it = set.begin(); it != set.end();)
    {
        out.push_back(std::move(set.extract(it++).value()));
    }

    return out;
}

} // namespace LunarDB::Moonlight::Implementation
