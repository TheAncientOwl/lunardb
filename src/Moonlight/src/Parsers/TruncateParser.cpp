#include "Errors.hpp"
#include "QueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace CppExtensions;

namespace {

constexpr auto c_query_prefix{"truncate"};

} // namespace

API::ParsedQuery Truncate::parse(QueryExtractor extractor)
{
    auto out_parsed_query = API::ParsedQuery::make<QueryData::Truncate>();
    auto& out = out_parsed_query.get<QueryData::Truncate>();

    auto const [truncate, structure, structure_name] = extractor.extractTuple<3>();
    if (!extractor.empty())
    {
        throw Errors::buildInvalidQueryFormatError(c_query_prefix);
    }

    Errors::assertKeywordEquals(truncate, "truncate");
    Errors::assertKeywordEquals(structure, "structure");

    out.structure_name = Errors::assertNotEmpty(structure_name, "structure name");

    return out_parsed_query;
}

} // namespace LunarDB::Moonlight::Implementation
