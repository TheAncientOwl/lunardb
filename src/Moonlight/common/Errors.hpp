#pragma once

#include <stdexcept>
#include <sstream>

namespace LunarDB::Moonlight::Errors {

template<typename... Args>
[[nodiscard]] std::runtime_error buildError(Args&&... args)
{
    std::ostringstream oss{};
    ((oss << std::forward<Args>(args) << ' '), ...);
    return std::runtime_error(std::move(oss.str()));
}

[[nodiscard]] std::runtime_error buildUnknownKeywordError(std::string_view keyword);
[[nodiscard]] std::runtime_error buildInvalidQueryFormatError(std::string_view query_type);

template<typename... Args>
[[nodiscard]] std::runtime_error buildMissingError(Args&&... args)
{
    return buildError("Missing ", std::forward<Args>(args)...);
}

[[nodiscard]] std::runtime_error buildUnknownSequenceError(std::string_view seq);
[[nodiscard]] std::runtime_error buildInvalidSequenceError(std::string_view seq);
[[nodiscard]] std::runtime_error buildParseJSONObjectError(std::string_view seq);

void assertKeywordEquals(std::string_view actual, std::string_view expected);
std::string_view assertNotEmpty(std::string_view src, std::string_view err);
void assertValidIdentifier(const std::string& src);

} // namespace LunarDB::Moonlight::Errors
