#include "Errors.hpp"
#include "QueryParsers.hpp"
#include "Utils.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_MOONLIGHT)

namespace LunarDB::Moonlight::Implementation {

namespace {

constexpr auto c_query_prefix{"rollback"};

} // namespace

API::ParsedQuery Rollback::parse(QueryExtractor extractor)
{
    CLOG_VERBOSE("Parsing 'rollback' query");

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
