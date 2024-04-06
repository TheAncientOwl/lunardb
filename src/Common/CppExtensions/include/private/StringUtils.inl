#pragma once

#include "Common/CppExtensions/include/StringUtils.hpp"

namespace LunarDB::CppExtensions::StringUtils {

template<typename... Args>
[[nodiscard]] std::string stringify(Args&&... args)
{
    std::ostringstream oss{};
    ((oss << std::forward<Args>(args) << ' '), ...);
    return std::move(oss.str());
}

} // namespace LunarDB::CppExtensions::StringUtils
