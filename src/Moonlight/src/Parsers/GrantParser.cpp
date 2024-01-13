#include <set>

#include "CppExtensions/include/Errors.hpp"
#include "QueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace CppExtensions;

namespace {

constexpr auto c_query_prefix{ "grant" };

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Grant, c_query_prefix)
{
    DECLARE_PARSED_QUERY(Grant);

    const auto grant = extractor.extractOne();
    Errors::assertKeywordEquals(grant, "grant");

    // parse permissions
    using namespace QueryData::Primitives;
    out.permissions = extractor.extractUniqueList<EUserPermissionType>(UserPermissionType::toLiteral);
    if (out.permissions.empty()) { throw Errors::buildMissingError("permissions"); }

    // parse user and structure names
    const auto [to, user_name, on, structure_name] = extractor.extractTuple<4>();
    if (!extractor.empty()) { throw Errors::buildInvalidQueryFormatError(c_query_prefix); }

    Errors::assertKeywordEquals(to, "to");
    out.to_user = Errors::assertNotEmpty(user_name, "user name");

    if (!on.empty())
    {
        Errors::assertKeywordEquals(on, "on");
        out.structure_name = Errors::assertNotEmpty(structure_name, "structure name");
    }


    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
