#pragma once

#include "QueryData.hpp"
#include "Errors.hpp"
#include "QueryExtractor.hpp"

#include <string_view>
#include <vector>
#include <utility>

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
/// @brief split a string at given char
/// @param str string to be splitted
/// @param sep separator
/// @param modifier EscapeQuotes if quotes should be escaped using '\'
/// @return std::vector<std::string_view> splits
/// 
std::vector<std::string_view> split(std::string_view str, char sep = ',', ESplitModifier modifier = ESplitModifier::None);

/// 
/// @brief extract first word separated by sep char
///        remove extracted word from given str
/// @param str string to be extracted from
/// @param sep separator
/// @param modifier EscapeQuotes if quotes should be escaped using '\'
/// @return extracted word
/// 
std::string_view extractWord(std::string_view& str, char sep = ' ', ESplitModifier modifier = ESplitModifier::None);

QueryData::WhereClause extractWhereClause(std::string_view& str);

std::pair<std::string_view, std::string_view> parseResolutionOperator(std::string_view str);

bool isValidIdentifier(const std::string& str);
bool isValidIdentifier(std::string_view sv);

} // namespace LunarDB::Moonlight::Utils
