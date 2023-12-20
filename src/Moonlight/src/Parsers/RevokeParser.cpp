#include "QueryParsers.hpp"
#include "Utils.hpp"

#include <set>

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "revoke" };

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Revoke, c_query_prefix)
{
    DECLARE_PARSED_QUERY(Revoke);

    const auto revoke = extractor.extractOne();
    Utils::checkKeywordEquals(revoke, "revoke");

    // parse permissions
    using namespace QueryData::Primitives;
    out.permissions = extractor.extractUniqueList<EUserPermissionType>(UserPermissionType::toLiteral);
    if (out.permissions.empty()) { throw Utils::buildMissingError("permissions"); }

    // parse user and structure names
    const auto [from, user_name, on, structure_name] = extractor.extractTuple<4>();
    if (!extractor.empty()) { throw Utils::buildInvalidQueryFormatError(c_query_prefix); }

    Utils::checkKeywordEquals(from, "from");
    out.from_user = Utils::checkNotEmpty(user_name, "user name");

    if (!on.empty())
    {
        Utils::checkKeywordEquals(on, "on");
        out.structure_name = Utils::checkNotEmpty(structure_name, "structure name");
    }


    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
