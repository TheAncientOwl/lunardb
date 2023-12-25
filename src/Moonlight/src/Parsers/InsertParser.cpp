#include "QueryParsers.hpp"
#include "Utils.hpp"

#include "simdjson/simdjson.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "insert" };

std::vector<QueryData::Insert::Object> parseObjects(std::string_view str)
{
    std::vector<QueryData::Insert::Object> out{};

    return out;
}

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Insert, c_query_prefix)
{
    DECLARE_PARSED_QUERY(Insert);

    const auto [insert, into, structure_name, objects] = extractor.extractTuple<4>();

    Utils::checkKeywordEquals(insert, "insert");
    Utils::checkKeywordEquals(into, "into");
    Utils::checkKeywordEquals(objects, "objects");

    out.into = Utils::checkNotEmpty(structure_name, "structure name");
    out.objects = parseObjects(extractor.data());

    if (objects.empty()) { throw Utils::buildMissingError("objects"); }

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
