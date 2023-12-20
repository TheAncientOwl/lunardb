#include "QueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "savepoint" };

} // namespace

PROVIDE_QUERY_PARSER_IMPL(SavePoint, c_query_prefix)
{
    DECLARE_PARSED_QUERY(obj, SavePoint);

    QueryExtractor extractor(query);

    const auto [savepoint, hash] = extractor.extractTuple<2>();
    if (!extractor.empty()) { throw Utils::buildInvalidQueryFormatError(c_query_prefix); }

    Utils::checkKeyword(savepoint, "savepoint");

    if (!hash.empty())
    {
        obj.hash = hash;
    }

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
