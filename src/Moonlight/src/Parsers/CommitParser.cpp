#include "Errors.hpp"
#include "QueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

namespace CppExtensions = LunarDB::Common::CppExtensions;

namespace {

constexpr auto c_query_prefix{"commit"};

} // namespace

API::ParsedQuery Commit::parse(QueryExtractor extractor)
{
    auto out_parsed_query = API::ParsedQuery::make<Common::QueryData::Commit>();

    auto const [commit] = extractor.extractTuple<1>();
    if (!extractor.empty())
    {
        throw Errors::buildInvalidQueryFormatError(c_query_prefix);
    }

    Errors::assertKeywordEquals(commit, "commit");

    return out_parsed_query;
}

} // namespace LunarDB::Moonlight::Implementation
