#include "QueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "set" };

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Lock, c_query_prefix)
{
    DECLARE_PARSED_QUERY(obj, Lock);

    const auto [set, concurrency, on, structure, structure_name, state] = extractor.extractTuple<6>();
    if (!extractor.empty()) { throw Utils::buildInvalidQueryFormatError(c_query_prefix); }

    Utils::checkKeywordEquals(set, "set");
    Utils::checkKeywordEquals(concurrency, "concurrency");
    Utils::checkKeywordEquals(on, "on");
    Utils::checkKeywordEquals(structure, "structure");

    obj.structure_name = Utils::checkNotEmpty(structure_name, "structure name");

    std::ignore = Utils::checkNotEmpty(state, "concurrency state (on/off)");
    if (Utils::equalsIgnoreCase(state, "on"))
    {
        obj.concurrency = true;
    }
    else if (Utils::equalsIgnoreCase(state, "off"))
    {
        obj.concurrency = false;
    }
    else
    {
        throw Utils::buildUnknownKeywordError(state);
    }

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
