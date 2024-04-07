#pragma once

#include "Common/CppExtensions/StringUtils.hpp"

namespace LunarDB::CppExtensions::StringUtils {

constexpr std::string_view whitespace() noexcept
{
    return " \n\r\t\f\v";
}

template<typename... Args>
[[nodiscard]] std::string stringify(Args&&... args)
{
    std::ostringstream oss{};
    ((oss << std::forward<Args>(args) << ' '), ...);
    return std::move(oss.str());
}

} // namespace LunarDB::CppExtensions::StringUtils
