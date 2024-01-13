#include <regex>

#include "Errors.hpp"
#include "StringUtils.hpp"

namespace LunarDB::CppExtensions::Errors {

LunarError buildUnknownKeywordError(std::string_view keyword)
{
    return buildError("Unknown keyword |", keyword, "|");
}

LunarError buildInvalidQueryFormatError(std::string_view query_type)
{
    return buildError("Invalid |", query_type, "' query format");
}

LunarError buildUnknownSequenceError(std::string_view seq)
{
    return buildError("Unknown sequence |", seq, "|");
}

LunarError buildInvalidSequenceError(std::string_view seq)
{
    return buildError("Invalid sequence |", seq, "|");
}

LunarError buildParseJSONObjectError(std::string_view seq)
{
    return buildError("Cannot parse JSON: ", seq);
}

void assertKeywordEquals(std::string_view actual, std::string_view expected)
{
    if (!StringUtils::equalsIgnoreCase(expected, actual))
    {
        throw buildError("Missing |", expected, "| keyword, found instead |", actual, "|");
    }
}

std::string_view assertNotEmpty(std::string_view src, std::string_view err)
{
    if (src.empty())
    {
        throw buildMissingError(err);
    }

    return src;
}

void assertValidIdentifier(const std::string& src)
{
    static const std::regex c_identifier_regex{ R"(\w+)" };

    if (!std::regex_match(src, c_identifier_regex))
    {
        throw buildError("Invalid identifier |", src, "|");
    }
}

} // namespace LunarDB::CppExtensions::Errors
