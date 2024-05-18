#include <set>

#include "Errors.hpp"
#include "QueryParsers.hpp"
#include "Utils.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_MOONLIGHT)

namespace LunarDB::Moonlight::Implementation {

namespace {

constexpr auto c_query_prefix{"revoke"};

} // namespace

API::ParsedQuery Revoke::parse(QueryExtractor extractor)
{
    CLOG_VERBOSE("Parsing 'revoke' query");

    auto out_parsed_query = API::ParsedQuery::make<Common::QueryData::Revoke>();
    auto& out = out_parsed_query.get<Common::QueryData::Revoke>();

    auto const revoke = extractor.extractOne();
    Errors::assertKeywordEquals(revoke, "revoke");

    // parse permissions
    using namespace Common::QueryData::Primitives;
    out.permissions = extractor.extractUniqueList<EUserPermissionType>(UserPermissionType::toLiteral);
    if (out.permissions.empty())
    {
        throw Errors::buildMissingError("permissions");
    }

    // parse user and structure names
    auto const [from, user_name, on, structure_name] = extractor.extractTuple<4>();
    if (!extractor.empty())
    {
        throw Errors::buildInvalidQueryFormatError(c_query_prefix);
    }

    Errors::assertKeywordEquals(from, "from");
    out.from_user = Errors::assertNotEmpty(user_name, "user name");

    Errors::assertKeywordEquals(on, "on");
    out.structure_name = Errors::assertNotEmpty(structure_name, "structure name");

    return out_parsed_query;
}

} // namespace LunarDB::Moonlight::Implementation
