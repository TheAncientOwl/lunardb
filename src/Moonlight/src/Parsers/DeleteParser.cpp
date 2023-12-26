#include "QueryParsers.hpp"
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
    if (extractor.empty()) { throw Utils::buildInvalidQueryFormatError(c_query_prefix); }

    Utils::checkKeywordEquals(delete_, "delete");
    Utils::checkKeywordEquals(from, "from");
    Utils::checkKeywordEquals(structure, "structure");

    out.from = Utils::checkNotEmpty(structure_name, "structure name");
    out.where = Utils::parseWhereClause(extractor.data());

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
