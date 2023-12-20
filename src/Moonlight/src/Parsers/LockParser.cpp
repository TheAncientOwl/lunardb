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

    QueryExtractor extractor{ query };

    const auto [set, concurrency, on, structure, structure_name, state] = extractor.extractTuple<6>();
    if (!extractor.empty()) { throw Utils::buildInvalidQueryFormatError(c_query_prefix); }

    Utils::checkKeyword(set, "set");
    Utils::checkKeyword(concurrency, "concurrency");
    Utils::checkKeyword(on, "on");
    Utils::checkKeyword(structure, "structure");

    if (structure_name.empty())
    {
        throw Utils::buildMissingError("structure name");
    }
    else
    {
        obj.structure_name = structure_name;
    }

    if (state.empty())
    {
        throw Utils::buildMissingError("concurrency state (on/off)");
    }
    else if (Utils::equalsIgnoreCase(state, "on"))
    {
        obj.concurrency = true;
    }
    else
    {
        obj.concurrency = false;
    }

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
