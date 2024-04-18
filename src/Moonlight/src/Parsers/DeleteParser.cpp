#include "Errors.hpp"
#include "QueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace CppExtensions;

namespace {

constexpr auto c_query_prefix{"delete"};

} // namespace

API::ParsedQuery Delete::parse(QueryExtractor extractor)
{
    auto out_parsed_query = API::ParsedQuery::make<QueryData::Delete>();
    auto& out = out_parsed_query.get<QueryData::Delete>();

    const auto [delete_, from, structure, structure_name] = extractor.extractTuple<4>();
    if (extractor.empty())
    {
        throw Errors::buildInvalidQueryFormatError(c_query_prefix);
    }

    Errors::assertKeywordEquals(delete_, "delete");
    Errors::assertKeywordEquals(from, "from");
    Errors::assertKeywordEquals(structure, "structure");

    out.from = Errors::assertNotEmpty(structure_name, "structure name");
    out.where = Utils::extractWhereClause(extractor.unsafe_data());

    return out_parsed_query;
}

} // namespace LunarDB::Moonlight::Implementation
