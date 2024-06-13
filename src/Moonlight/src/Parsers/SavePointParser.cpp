#include "Errors.hpp"
#include "QueryParsers.hpp"
#include "Utils.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_MOONLIGHT)

namespace LunarDB::Moonlight::Implementation {

namespace {

constexpr auto c_query_prefix{"savepoint"};

} // namespace

API::ParsedQuery SavePoint::parse(QueryExtractor extractor)
{
    CLOG_VERBOSE("SavePoint::parse()");

    auto out_parsed_query = API::ParsedQuery::make<Common::QueryData::SavePoint>();
    auto& out = out_parsed_query.get<Common::QueryData::SavePoint>();

    auto const [savepoint, hash] = extractor.extractTuple<2>();
    if (!extractor.empty())
    {
        throw Errors::buildInvalidQueryFormatError(c_query_prefix);
    }

    Errors::assertKeywordEquals(savepoint, "savepoint");

    if (!hash.empty())
    {
        out.hash = hash;
    }

    return out_parsed_query;
}

} // namespace LunarDB::Moonlight::Implementation
