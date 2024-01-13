#include "QueryParser.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace CppExtensions;

namespace {

constexpr auto c_query_prefix{ "commit" };

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Commit, c_query_prefix)
{

    DECLARE_PARSED_QUERY(Commit);

    const auto [commit] = extractor.extractTuple<1>();
    if (!extractor.empty()) { throw Errors::buildInvalidQueryFormatError(c_query_prefix); }

    Errors::assertKeywordEquals(commit, "commit");

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
