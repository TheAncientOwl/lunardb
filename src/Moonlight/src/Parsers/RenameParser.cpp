#include "QueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "rename" };

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Rename, c_query_prefix)
{
    DECLARE_PARSED_QUERY(obj, Rename);

    const auto [rename, type, from, old_name, to, new_name] = extractor.extractTuple<6>();
    if (!extractor.empty()) { throw Utils::buildInvalidQueryFormatError(c_query_prefix); };

    Utils::checkKeywordEquals(rename, "rename");
    Utils::checkKeywordEquals(from, "from");
    Utils::checkKeywordEquals(to, "to");

    obj.type = QueryData::Primitives::RenameType::toLiteral(Utils::checkNotEmpty(type, "rename type"));
    obj.old_name = Utils::checkNotEmpty(old_name, "old name");
    obj.new_name = Utils::checkNotEmpty(new_name, "new name");

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
