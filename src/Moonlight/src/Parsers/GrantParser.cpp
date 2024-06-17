#include <set>

#include "Errors.hpp"
#include "LunarDB/Moonlight/QueryParsers.hpp"
#include "Utils.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_MOONLIGHT)

namespace LunarDB::Moonlight::Implementation {

namespace {

constexpr auto c_query_prefix{"grant"};

} // namespace

API::ParsedQuery Grant::parse(QueryExtractor extractor)
{
    CLOG_VERBOSE("Grant::parse()");

    auto out_parsed_query = API::ParsedQuery::make<Common::QueryData::Grant>();
    auto& out = out_parsed_query.get<Common::QueryData::Grant>();

    auto const grant = extractor.extractOne();
    Errors::assertKeywordEquals(grant, "grant");

    // parse permissions
    using namespace Common::QueryData::Primitives;
    out.permissions = extractor.extractUniqueList<EUserPermissionType>(UserPermissionType::toLiteral);
    if (out.permissions.empty())
    {
        throw Errors::buildMissingError("permissions");
    }

    // parse user and structure names
    auto const [to, user_name, on, structure_name] = extractor.extractTuple<4>();
    if (!extractor.empty())
    {
        throw Errors::buildInvalidQueryFormatError(c_query_prefix);
    }

    Errors::assertKeywordEquals(to, "to");
    out.to_user = Errors::assertNotEmpty(user_name, "user name");

    Errors::assertKeywordEquals(on, "on");
    Errors::assertKeywordEquals(on, "on");
    out.structure_name = Errors::assertNotEmpty(structure_name, "structure name");

    return out_parsed_query;
}

} // namespace LunarDB::Moonlight::Implementation
