#pragma once

#include <string_view>
#include <utility>
#include <vector>

#include "LunarDB/Common/QueryData/QueryData.hpp"

namespace LunarDB::Moonlight::Utils {

///
/// @brief Flag used signal escaping quoted strings.
///
enum class ESplitModifier
{
    None = 0,
    EscapeQuotes = 1
};

///
/// @brief Split a string at given char.
/// @param [in] str -> String to be splitted
/// @param [in] sep -> Separator
/// @param [in] modifier -> EscapeQuotes if quotes should be escaped using '\'
/// @return std::vector<std::string_view> splits
///
[[nodiscard]] std::vector<std::string_view> split(
    std::string_view str,
    char sep = ',',
    ESplitModifier modifier = ESplitModifier::None);

///
/// @brief Extract first word separated by sep char.
///        Remove extracted word from given str.
/// @param [in] str -> String to be extracted from
/// @param [in] sep -> Separator
/// @param [in] modifier -> EscapeQuotes if quotes should be escaped using '\'
/// @return extracted word
///
[[nodiscard]] std::string_view extractWord(
    std::string_view& str,
    char sep = ' ',
    ESplitModifier modifier = ESplitModifier::None);

///
/// @brief Self explanatory.
/// @see QueryData::WhereClause
///
[[nodiscard]] QueryData::WhereClause extractWhereClause(std::string_view& str);

///
/// @brief Self explanatory.
/// @param [in] str -> In format "str1::str2"
/// @return pair<str1, str2>
///
[[nodiscard]] std::pair<std::string_view, std::string_view> parseResolutionOperator(std::string_view str);

} // namespace LunarDB::Moonlight::Utils
