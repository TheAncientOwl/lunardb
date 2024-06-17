#include "Errors.hpp"
#include "LunarDB/Moonlight/QueryParsers.hpp"
#include "Utils.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_MOONLIGHT)

namespace LunarDB::Moonlight::Implementation {

namespace {

constexpr auto c_query_prefix{"commit"};

} // namespace

API::ParsedQuery Commit::parse(QueryExtractor extractor)
{
    CLOG_VERBOSE("Commit::parse()");

    auto out_parsed_query = API::ParsedQuery::make<Common::QueryData::Commit>();

    auto const [commit] = extractor.extractTuple<1>();
    if (!extractor.empty())
    {
        throw Errors::buildInvalidQueryFormatError(c_query_prefix);
    }

    Errors::assertKeywordEquals(commit, "commit");

    return out_parsed_query;
}

} // namespace LunarDB::Moonlight::Implementation
