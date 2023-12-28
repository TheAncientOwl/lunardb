#pragma once

#include <string_view>
#include <utility>
#include <vector>

#include "QueryData.hpp"

namespace LunarDB::Moonlight::Utils {

constexpr auto c_whitespace = std::string_view{ " \n\r\t\f\v" };

///
/// @brief Left trim whitespaces from given string view
///
void ltrim(std::string_view& str);

///
/// @brief Right trim whitespaces from given string view
///
void rtrim(std::string_view& str);

///
/// @brief Fully trim whitespaces from given string view (left & right)
///
void trim(std::string_view& str);

///
/// @brief Check if 's1' is the same as 's2', case insensitive
/// 
[[nodiscard]] bool equalsIgnoreCase(std::string_view s1, std::string_view s2);

///
/// @brief Check if 'src' starts with 'what', case insensitive
///
[[nodiscard]] bool startsWithIgnoreCase(std::string_view src, std::string_view what);

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
[[nodiscard]] std::vector<std::string_view> split(std::string_view str,
    char sep = ',', ESplitModifier modifier = ESplitModifier::None);

/// 
/// @brief extract first word separated by sep char
///        remove extracted word from given str
/// @param str string to be extracted from
/// @param sep separator
/// @param modifier EscapeQuotes if quotes should be escaped using '\'
/// @return extracted word
/// 
[[nodiscard]] std::string_view extractWord(std::string_view& str,
    char sep = ' ', ESplitModifier modifier = ESplitModifier::None);

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
