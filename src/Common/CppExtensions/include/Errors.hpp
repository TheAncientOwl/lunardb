#pragma once

#include <sstream>
#include <stdexcept>

namespace LunarDB::CppExtensions::Errors {

using LunarError = std::runtime_error;

template<typename... Args>
[[nodiscard]] LunarError buildError(Args&&... args)
{
    std::ostringstream oss{};
    ((oss << std::forward<Args>(args) << ' '), ...);
    return LunarError(std::move(oss.str()));
}

[[nodiscard]] LunarError buildUnknownKeywordError(std::string_view keyword);
[[nodiscard]] LunarError buildInvalidQueryFormatError(std::string_view query_type);

template<typename... Args>
[[nodiscard]] LunarError buildMissingError(Args&&... args)
{
    return buildError("Missing ", std::forward<Args>(args)...);
}

[[nodiscard]] LunarError buildUnknownSequenceError(std::string_view seq);
[[nodiscard]] LunarError buildInvalidSequenceError(std::string_view seq);
[[nodiscard]] LunarError buildParseJSONObjectError(std::string_view seq);

void assertKeywordEquals(std::string_view actual, std::string_view expected);
std::string_view assertNotEmpty(std::string_view src, std::string_view err);
void assertValidIdentifier(const std::string& src);

} // namespace LunarDB::CppExtensions::Errors
