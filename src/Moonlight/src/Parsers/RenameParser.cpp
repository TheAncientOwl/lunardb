#include "QueryParser.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace CppExtensions;

namespace {

constexpr auto c_query_prefix{ "rename" };

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Rename, c_query_prefix)
{
    DECLARE_PARSED_QUERY(Rename);

    const auto [rename, type, from, old_name, to, new_name] = extractor.extractTuple<6>();
    if (!extractor.empty()) { throw Errors::buildInvalidQueryFormatError(c_query_prefix); };

    Errors::assertKeywordEquals(rename, "rename");
    Errors::assertKeywordEquals(from, "from");
    Errors::assertKeywordEquals(to, "to");

    out.type = QueryData::Primitives::RenameType::toLiteral(Errors::assertNotEmpty(type, "rename type"));
    out.old_name = Errors::assertNotEmpty(old_name, "old name");
    out.new_name = Errors::assertNotEmpty(new_name, "new name");

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
