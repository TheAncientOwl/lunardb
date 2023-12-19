#pragma once

#include <stdexcept>
#include <sstream>

namespace LunarDB::Moonlight::Utils {

template<typename... Args>
std::runtime_error buildError(Args&&... args)
{
    std::ostringstream oss{};
    ((oss << std::forward<Args>(args) << ' '), ...);
    return std::runtime_error(std::move(oss.str()));
}

std::runtime_error buildUnknownKeywordError(std::string_view keyword);
std::runtime_error buildInvalidQueryFormatError(std::string_view query_type);
std::runtime_error buildMissingError(std::string_view what);

void checkKeyword(std::string_view actual, std::string_view expected);

} // namespace LunarDB::Moonlight::Utils
