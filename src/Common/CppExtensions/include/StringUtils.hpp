#pragma once

#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "QueryData/include/QueryData.hpp"

namespace LunarDB::CppExtensions::StringUtils {

constexpr auto c_whitespace = std::string_view{ " \n\r\t\f\v" };

///
/// @brief Creates a string from given arguments
///
template<typename... Args>
[[nodiscard]] std::string stringify(Args&&... args)
{
    std::ostringstream oss{};
    ((oss << std::forward<Args>(args) << ' '), ...);
    return std::move(oss.str());
}

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

} // namespace LunarDB::CppExtensions::StringUtils
