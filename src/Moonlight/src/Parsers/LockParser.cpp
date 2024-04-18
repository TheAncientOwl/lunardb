#include "Errors.hpp"
#include "QueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace CppExtensions;

namespace {

constexpr auto c_query_prefix{"set"};

} // namespace

API::ParsedQuery Lock::parse(QueryExtractor extractor)
{
    auto out_parsed_query = API::ParsedQuery::make<QueryData::Lock>();
    auto& out = out_parsed_query.get<QueryData::Lock>();

    const auto [set, concurrency, on, structure, structure_name, state] = extractor.extractTuple<6>();
    if (!extractor.empty())
    {
        throw Errors::buildInvalidQueryFormatError(c_query_prefix);
    }

    Errors::assertKeywordEquals(set, "set");
    Errors::assertKeywordEquals(concurrency, "concurrency");
    Errors::assertKeywordEquals(on, "on");
    Errors::assertKeywordEquals(structure, "structure");

    out.structure_name = Errors::assertNotEmpty(structure_name, "structure name");

    std::ignore = Errors::assertNotEmpty(state, "concurrency state (on/off)");
    if (StringUtils::equalsIgnoreCase(state, "on"))
    {
        out.concurrency = true;
    }
    else if (StringUtils::equalsIgnoreCase(state, "off"))
    {
        out.concurrency = false;
    }
    else
    {
        throw Errors::buildUnknownKeywordError(state);
    }

    return out_parsed_query;
}

} // namespace LunarDB::Moonlight::Implementation
