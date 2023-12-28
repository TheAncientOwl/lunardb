#include "QueryParsers.hpp"
#include "Errors.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

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
