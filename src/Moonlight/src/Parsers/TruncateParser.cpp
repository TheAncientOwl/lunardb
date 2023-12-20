#include "QueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "truncate" };

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Truncate, c_query_prefix)
{
    DECLARE_PARSED_QUERY(obj, Truncate);

    const auto [truncate, structure, structure_name] = extractor.extractTuple<3>();
    if (!extractor.empty()) { throw Utils::buildInvalidQueryFormatError(c_query_prefix); }

    Utils::checkKeywordEquals(truncate, "truncate");
    Utils::checkKeywordEquals(structure, "structure");

    obj.structure_name = Utils::checkNotEmpty(structure_name, "structure name");

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
