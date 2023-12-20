#include "QueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "drop" };

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Drop, c_query_prefix)
{
    DECLARE_PARSED_QUERY(Drop);

    const auto [drop, structure, structure_name, cascade] = extractor.extractTuple<4>();
    if (!extractor.empty()) { throw Utils::buildInvalidQueryFormatError(c_query_prefix); }

    Utils::checkKeywordEquals(drop, "drop");
    Utils::checkKeywordEquals(structure, "structure");

    out.structure_name = Utils::checkNotEmpty(structure_name, "structure name");

    if (cascade.empty())
    {
        out.cascade = false;
    }
    else
    {
        Utils::checkKeywordEquals(cascade, "cascade");
        out.cascade = true;
    }

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
