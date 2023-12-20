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

    obj.structure_name = Utils::checkNotEmpty(structure_name, "structure name");

    std::ignore = Utils::checkNotEmpty(state, "concurrency state (on/off)");
    obj.concurrency = Utils::equalsIgnoreCase(state, "on");

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
