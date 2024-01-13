#include <regex>

#include "Errors.hpp"
#include "StringUtils.hpp"

namespace LunarDB::Moonlight::Errors {

std::runtime_error buildUnknownKeywordError(std::string_view keyword)
{
    return buildError("Unknown keyword |", keyword, "|");
}

std::runtime_error buildInvalidQueryFormatError(std::string_view query_type)
{
    return buildError("Invalid |", query_type, "' query format");
}

std::runtime_error buildUnknownSequenceError(std::string_view seq)
{
    return buildError("Unknown sequence |", seq, "|");
}

std::runtime_error buildInvalidSequenceError(std::string_view seq)
{
    return buildError("Invalid sequence |", seq, "|");
}

std::runtime_error buildParseJSONObjectError(std::string_view seq)
{
    return buildError("Cannot parse JSON: ", seq);
}

void assertKeywordEquals(std::string_view actual, std::string_view expected)
{
    if (!Utils::equalsIgnoreCase(expected, actual))
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

} // namespace LunarDB::Moonlight::Errors
