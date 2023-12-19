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

void checkKeyword(std::string_view actual, std::string_view expected)
{
    if (!equalsIgnoreCase(expected, actual))
    {
        throw buildError("Missing '", expected, "' keyword, found instead '", actual, "'");
    }
}

} // namespace LunarDB::Moonlight::Utils
