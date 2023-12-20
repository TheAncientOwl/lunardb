#include "QueryParsers.hpp"
#include "Utils.hpp"

#include <set>

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "grant" };

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Grant, c_query_prefix)
{
    DECLARE_PARSED_QUERY(Grant);

    const auto grant = extractor.extractOne();
    Utils::checkKeywordEquals(grant, "grant");

    // parse permissions
    using namespace QueryData::Primitives;
    out.permissions = extractor.extractUniqueList<EUserPermissionType>(UserPermissionType::toLiteral);
    if (out.permissions.empty()) { throw Utils::buildMissingError("permissions"); }

    // parse user and structure names
    const auto [to, user_name, on, structure_name] = extractor.extractTuple<4>();
    if (!extractor.empty()) { throw Utils::buildInvalidQueryFormatError(c_query_prefix); }

    Utils::checkKeywordEquals(to, "to");
    out.to_user = Utils::checkNotEmpty(user_name, "user name");

    if (!on.empty())
    {
        Utils::checkKeywordEquals(on, "on");
        out.structure_name = Utils::checkNotEmpty(structure_name, "structure name");
    }


    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
