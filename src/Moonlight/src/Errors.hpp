#pragma once

#include <stdexcept>
#include "Common/CppExtensions/StringUtils.hpp"

namespace LunarDB::Moonlight::Errors {

using ParserError = std::runtime_error;

template<typename... Args>
[[nodiscard]] ParserError buildError(Args&&... args)
{
    return std::runtime_error{ CppExtensions::StringUtils::stringify("Missing ", std::forward<Args>(args)...) };
}

[[nodiscard]] ParserError buildUnknownKeywordError(std::string_view keyword);
[[nodiscard]] ParserError buildInvalidQueryFormatError(std::string_view query_type);

template<typename... Args>
[[nodiscard]] ParserError buildMissingError(Args&&... args)
{
    return buildError("Missing ", std::forward<Args>(args)...);
}

[[nodiscard]] ParserError buildUnknownSequenceError(std::string_view seq);
[[nodiscard]] ParserError buildInvalidSequenceError(std::string_view seq);
[[nodiscard]] ParserError buildParseJSONObjectError(std::string_view seq);

void assertKeywordEquals(std::string_view actual, std::string_view expected);
std::string_view assertNotEmpty(std::string_view src, std::string_view err);
void assertValidIdentifier(const std::string& src);

} // namespace LunarDB::Moonlight::Errors
