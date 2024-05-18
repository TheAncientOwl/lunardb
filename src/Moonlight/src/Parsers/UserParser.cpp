#include "Errors.hpp"
#include "QueryParsers.hpp"
#include "Utils.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_MOONLIGHT)

namespace LunarDB::Moonlight::Implementation {

namespace {

constexpr auto c_query_prefix{"user"};

} // namespace

API::ParsedQuery User::parse(QueryExtractor extractor)
{
    CLOG_VERBOSE("Parsing 'user' query");

    auto out_parsed_query = API::ParsedQuery::make<Common::QueryData::User>();
    auto& out = out_parsed_query.get<Common::QueryData::User>();

    auto const [user, action, name] = extractor.extractTuple<3>();
    if (!extractor.empty())
    {
        throw Errors::buildInvalidQueryFormatError(c_query_prefix);
    }

    Errors::assertKeywordEquals(user, "user");

    out.action = Common::QueryData::Primitives::UserActionType::toLiteral(
        Errors::assertNotEmpty(action, "action type"));
    out.name = Errors::assertNotEmpty(name, "username");

    return out_parsed_query;
}

} // namespace LunarDB::Moonlight::Implementation
