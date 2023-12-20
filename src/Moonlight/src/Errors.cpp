#include "Utils.hpp"

namespace LunarDB::Moonlight::Utils {

std::runtime_error buildUnknownKeywordError(std::string_view keyword)
{
    return buildError("Unknown keyword '", keyword, "'");
}

std::runtime_error buildInvalidQueryFormatError(std::string_view query_type)
{
    return buildError("Invalid '", query_type, "' query format");
}

std::runtime_error buildMissingError(std::string_view what)
{
    return buildError("Missing ", what);
}

std::runtime_error buildUnknownSequenceError(std::string_view seq)
{
    return buildError("Unknown sequence '", seq, "'");
}

void checkKeywordEquals(std::string_view actual, std::string_view expected)
{
    if (!equalsIgnoreCase(expected, actual))
    {
        throw buildError("Missing '", expected, "' keyword, found instead '", actual, "'");
    }
}

std::string_view checkNotEmpty(std::string_view src, std::string_view err)
{
    if (src.empty())
    {
        throw buildMissingError(err);
    }

    return src;
}

} // namespace LunarDB::Moonlight::Utils
