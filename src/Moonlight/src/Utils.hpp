#pragma once

#include <string_view>

namespace LunarDB::Moonlight::Utils {

using namespace std::literals;

constexpr auto c_whitespace = " \n\r\t\f\v"sv;

void ltrim(std::string_view& str);
void rtrim(std::string_view& str);
void trim(std::string_view& str);

bool equalsIgnoreCase(std::string_view s1, std::string_view s2);
bool startsWithIgnoreCase(std::string_view src, std::string_view what);

} // namespace LunarDB::Moonlight::Utils
