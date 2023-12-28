#include "QueryParser.hpp"

namespace LunarDB::Moonlight::Implementation {

namespace {

constexpr auto c_query_prefix{ "truncate" };

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Truncate, c_query_prefix)
{
    DECLARE_PARSED_QUERY(Truncate);

    const auto [truncate, structure, structure_name] = extractor.extractTuple<3>();
    if (!extractor.empty()) { throw Errors::buildInvalidQueryFormatError(c_query_prefix); }

    Errors::assertKeywordEquals(truncate, "truncate");
    Errors::assertKeywordEquals(structure, "structure");

    out.structure_name = Errors::assertNotEmpty(structure_name, "structure name");

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
