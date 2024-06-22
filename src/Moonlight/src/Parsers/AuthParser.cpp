#include "Errors.hpp"
#include "LunarDB/Moonlight/QueryParsers.hpp"
#include "Utils.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_MOONLIGHT)

namespace LunarDB::Moonlight::Implementation {

namespace {

constexpr auto c_query_prefix{"auth"};

} // namespace

API::ParsedQuery Auth::parse(QueryExtractor extractor)
{
    CLOG_VERBOSE("Auth::parse()");

    auto out_parsed_query = API::ParsedQuery::make<Common::QueryData::Auth>();
    auto& out = out_parsed_query.get<Common::QueryData::Auth>();

    auto const [auth, username] = extractor.extractTuple<2>();
    if (!extractor.empty())
    {
        throw Errors::buildInvalidQueryFormatError(c_query_prefix);
    }

    Errors::assertKeywordEquals(auth, "auth");

    out.username = Errors::assertNotEmpty(username, "username");

    return out_parsed_query;
}

} // namespace LunarDB::Moonlight::Implementation
