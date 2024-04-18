#pragma once

#include <string_view>
#include <utility>
#include <vector>

#include "Common/QueryData/QueryData.hpp"

namespace LunarDB::Moonlight::Utils {

///
/// @brief Flag used signal escaping quoted strings
///
enum class ESplitModifier
{
    None = 0,
    EscapeQuotes = 1
};

///
/// @brief split a string at given char
/// @param str string to be splitted
/// @param sep separator
/// @param modifier EscapeQuotes if quotes should be escaped using '\'
/// @return std::vector<std::string_view> splits
///
[[nodiscard]] std::vector<std::string_view> split(
    std::string_view str,
    char sep = ',',
    ESplitModifier modifier = ESplitModifier::None);

///
/// @brief extract first word separated by sep char
///        remove extracted word from given str
/// @param str string to be extracted from
/// @param sep separator
/// @param modifier EscapeQuotes if quotes should be escaped using '\'
/// @return extracted word
///
[[nodiscard]] std::string_view extractWord(std::string_view& str, char sep = ' ', ESplitModifier modifier = ESplitModifier::None);

///
/// @brief Self explanatory
/// @see QueryData::WhereClause
///
[[nodiscard]] QueryData::WhereClause extractWhereClause(std::string_view& str);

///
/// @brief Self explanatory
/// @param str in format "str1::str2"
/// @return pair<str1, str2>
///
[[nodiscard]] std::pair<std::string_view, std::string_view> parseResolutionOperator(std::string_view str);

} // namespace LunarDB::Moonlight::Utils
