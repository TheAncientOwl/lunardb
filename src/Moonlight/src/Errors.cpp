#include <regex>

#include "Errors.hpp"

namespace LunarDB::Moonlight::Errors {

namespace StringUtils = Common::CppExtensions::StringUtils;

ParserError buildUnknownKeywordError(std::string_view keyword)
{
    return ParserError{StringUtils::stringify("Unknown keyword |", keyword, "|")};
}

ParserError buildInvalidQueryFormatError(std::string_view query_type)
{
    return ParserError{StringUtils::stringify("Invalid |", query_type, "' query format")};
}

ParserError buildUnknownSequenceError(std::string_view seq)
{
    return ParserError{StringUtils::stringify("Unknown sequence |", seq, "|")};
}

ParserError buildInvalidSequenceError(std::string_view seq)
{
    return ParserError{StringUtils::stringify("Invalid sequence |", seq, "|")};
}

ParserError buildParseJSONObjectError(std::string_view seq)
{
    return ParserError{StringUtils::stringify("Cannot parse JSON: ", seq)};
}

void assertKeywordEquals(std::string_view actual, std::string_view expected)
{
    if (!StringUtils::equalsIgnoreCase(expected, actual))
    {
        throw Errors::buildError("Missing |", expected, "| keyword, found instead |", actual, "|");
    }
}

std::string_view assertNotEmpty(std::string_view src, std::string_view err)
{
    if (src.empty())
    {
        throw Errors::buildMissingError(err);
    }

    return src;
}

void assertValidIdentifier(std::string const& src)
{
    static const std::regex c_identifier_regex{R"(\w+[._(\w)]*)"};

    if (!std::regex_match(src, c_identifier_regex))
    {
        throw Errors::buildError("Invalid identifier |", src, "|");
    }
}

} // namespace LunarDB::Moonlight::Errors
