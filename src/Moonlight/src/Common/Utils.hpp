#pragma once

#include "QueryData.hpp"

#include <string_view>
#include <vector>

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

} // namespace LunarDB::Moonlight::Utils
