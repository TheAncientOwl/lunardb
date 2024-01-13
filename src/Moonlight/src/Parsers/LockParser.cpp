#include "CppExtensions/include/Errors.hpp"
#include "QueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace CppExtensions;

namespace {

constexpr auto c_query_prefix{ "set" };

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Lock, c_query_prefix)
{
    DECLARE_PARSED_QUERY(Lock);

    const auto [set, concurrency, on, structure, structure_name, state] = extractor.extractTuple<6>();
    if (!extractor.empty()) { throw Errors::buildInvalidQueryFormatError(c_query_prefix); }

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

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
