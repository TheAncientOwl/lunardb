#include "Errors.hpp"
#include "QueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

namespace CppExtensions = LunarDB::Common::CppExtensions;

namespace {

constexpr auto c_query_prefix{"rollback"};

} // namespace

API::ParsedQuery Rollback::parse(QueryExtractor extractor)
{
    auto out_parsed_query = API::ParsedQuery::make<Common::QueryData::Rollback>();
    auto& out = out_parsed_query.get<Common::QueryData::Rollback>();

    auto const [rollback, hash] = extractor.extractTuple<2>();
    if (!extractor.empty())
    {
        throw Errors::buildInvalidQueryFormatError(c_query_prefix);
    }

    Errors::assertKeywordEquals(rollback, "rollback");

    if (!hash.empty())
    {
        out.hash = hash;
    }

    return out_parsed_query;
}

} // namespace LunarDB::Moonlight::Implementation
