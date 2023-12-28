#include "QueryParsers.hpp"
#include "Errors.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "rollback" };

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Rollback, c_query_prefix)
{
    DECLARE_PARSED_QUERY(Rollback);

    const auto [rollback, hash] = extractor.extractTuple<2>();
    if (!extractor.empty()) { throw Errors::buildInvalidQueryFormatError(c_query_prefix); }

    Errors::assertKeywordEquals(rollback, "rollback");

    if (!hash.empty())
    {
        out.hash = hash;
    }

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
