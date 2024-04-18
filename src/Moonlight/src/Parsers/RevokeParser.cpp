#include <set>

#include "Errors.hpp"
#include "QueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace CppExtensions;

namespace {

constexpr auto c_query_prefix{"revoke"};

} // namespace

API::ParsedQuery Revoke::parse(QueryExtractor extractor)
{
    auto out_parsed_query = API::ParsedQuery::make<QueryData::Revoke>();
    auto& out = out_parsed_query.get<QueryData::Revoke>();

    const auto revoke = extractor.extractOne();
    Errors::assertKeywordEquals(revoke, "revoke");

    // parse permissions
    using namespace QueryData::Primitives;
    out.permissions = extractor.extractUniqueList<EUserPermissionType>(UserPermissionType::toLiteral);
    if (out.permissions.empty())
    {
        throw Errors::buildMissingError("permissions");
    }

    // parse user and structure names
    const auto [from, user_name, on, structure_name] = extractor.extractTuple<4>();
    if (!extractor.empty())
    {
        throw Errors::buildInvalidQueryFormatError(c_query_prefix);
    }

    Errors::assertKeywordEquals(from, "from");
    out.from_user = Errors::assertNotEmpty(user_name, "user name");

    if (!on.empty())
    {
        Errors::assertKeywordEquals(on, "on");
        out.structure_name = Errors::assertNotEmpty(structure_name, "structure name");
    }

    return out_parsed_query;
}

} // namespace LunarDB::Moonlight::Implementation
