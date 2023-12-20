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
std::runtime_error buildUnknownSequenceError(std::string_view seq);
std::runtime_error buildInvalidSequenceError(std::string_view seq);

void checkKeywordEquals(std::string_view actual, std::string_view expected);
std::string_view checkNotEmpty(std::string_view src, std::string_view err);

} // namespace LunarDB::Moonlight::Utils
