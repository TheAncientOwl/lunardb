#include "QueryParsers.hpp"
#include "Errors.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "delete" };

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Delete, c_query_prefix)
{
    DECLARE_PARSED_QUERY(Delete);

    const auto [delete_, from, structure, structure_name] = extractor.extractTuple<4>();
    if (extractor.empty()) { throw Errors::buildInvalidQueryFormatError(c_query_prefix); }

    Errors::assertKeywordEquals(delete_, "delete");
    Errors::assertKeywordEquals(from, "from");
    Errors::assertKeywordEquals(structure, "structure");

    out.from = Errors::assertNotEmpty(structure_name, "structure name");
    out.where = Utils::extractWhereClause(extractor.unsafe_data());

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
