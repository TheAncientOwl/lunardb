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

    QueryExtractor extractor{ query };

    const auto grant = extractor.extractOne();
    Utils::checkKeywordEquals(grant, "grant");

    // parse permissions
    if (extractor.data().front() != '[') { throw Utils::buildMissingError("["); }

    const auto list_end = extractor.data().find_last_of(']');
    if (list_end == std::string_view::npos) { throw Utils::buildError("]"); }

    const auto permissions = Utils::splitAtComma(extractor.data().substr(1, list_end - 1));

    if (permissions.empty()) { throw Utils::buildMissingError("permissions"); }

    std::set<QueryData::Primitives::EUserPermissionType> permissions_set{};
    std::transform(
        permissions.begin(), permissions.end(),
        std::inserter(permissions_set, permissions_set.begin()),
        [](auto permission) {return QueryData::Primitives::UserPermissionType::toLiteral(permission);}
    );

    obj.permissions = std::vector<QueryData::Primitives::EUserPermissionType>{};
    std::copy(permissions_set.begin(), permissions_set.end(), std::back_inserter(obj.permissions));

    // parse user and structure names
    extractor.remove_prefix(list_end + 1);
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
