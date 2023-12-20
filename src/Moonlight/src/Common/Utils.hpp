#pragma once

#include "QueryData.hpp"
#include "Errors.hpp"
#include "QueryExtractor.hpp"

#include <string_view>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <functional>

namespace LunarDB::Moonlight::Utils {

using namespace std::literals;

constexpr auto c_whitespace = " \n\r\t\f\v"sv;

void ltrim(std::string_view& str);
void rtrim(std::string_view& str);
void trim(std::string_view& str);

bool equalsIgnoreCase(std::string_view s1, std::string_view s2);
bool startsWithIgnoreCase(std::string_view src, std::string_view what);

enum class ESplitModifier
{
    None = 0,
    EscapeQuotes = 1
};

/// 
/// @brief split a string at ','
/// @param str string to be splitted
/// @param modifier EscapeQuotes if quotes should be escaped using '\'
/// @return std::vector<std::string_view> splits
/// 
std::vector<std::string_view> splitAtComma(std::string_view str, ESplitModifier modifier = ESplitModifier::None);

QueryData::WhereClause parseWhereClause(std::string_view where);

std::pair<std::string_view, std::string_view> parseResolutionOperator(std::string_view str);

template<typename T>
std::vector<T> parseUnique(const std::vector<std::string_view>& values, std::function<T(std::string_view)> parser)
{
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

} // namespace LunarDB::Moonlight::Utils
