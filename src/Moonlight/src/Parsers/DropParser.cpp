#include "QueryParsers.hpp"
#include "QueryExtractor.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "drop" };

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Drop, c_query_prefix)
{
    DECLARE_PARSED_QUERY(obj, Drop);
    QueryExtractor extractor{ query };

    const auto [drop, structure, structure_name, cascade] = extractor.extractTuple<4>();
    if (!extractor.empty()) { throw Utils::buildInvalidQueryFormatError(c_query_prefix); }

    Utils::checkKeyword(drop, "drop");
    Utils::checkKeyword(structure, "structure");

    if (structure_name.empty())
    {
        throw Utils::buildMissingError("structure name");
    }
    else
    {
        obj.structure_name = structure_name;
    }

    if (cascade.empty())
    {
        obj.cascade = false;
    }
    else if (Utils::equalsIgnoreCase(cascade, "cascade"))
    {
        obj.cascade = true;
    }
    else
    {
        throw Utils::buildUnknownKeywordError(cascade);
    }

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
