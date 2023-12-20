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
    DECLARE_PARSED_QUERY(obj, Grant);

    const auto grant = extractor.extractOne();
    Utils::checkKeywordEquals(grant, "grant");

    // parse permissions
    const auto permissions = extractor.extractList();
    if (permissions.empty()) { throw Utils::buildMissingError("permissions"); }

    using namespace QueryData::Primitives;
    obj.permissions = Utils::parseUnique<EUserPermissionType>(permissions, UserPermissionType::toLiteral);

    // parse user and structure names
    const auto [to, user_name, on, structure_name] = extractor.extractTuple<4>();
    if (!extractor.empty()) { throw Utils::buildInvalidQueryFormatError(c_query_prefix); }

    Utils::checkKeywordEquals(to, "to");
    obj.to_user = Utils::checkNotEmpty(user_name, "user name");

    if (!on.empty())
    {
        Utils::checkKeywordEquals(on, "on");
        obj.structure_name = Utils::checkNotEmpty(structure_name, "structure name");
    }


    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
