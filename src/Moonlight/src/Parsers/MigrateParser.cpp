#include "QueryParsers.hpp"
#include "Utils.hpp"

#include <unordered_set>

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "migrate" };

using Mapping = QueryData::Migrate::Mapping;

Mapping parseMapping(std::string_view str)
{
    Mapping out{};

    QueryExtractor extractor{ str };
    const auto [old_field, arrow, new_field] = extractor.extractTuple<3>();

    if (!extractor.empty()) { throw Utils::buildInvalidSequenceError(str); }

    Utils::checkKeywordEquals(arrow, "=>");

    out.old_field = Utils::checkNotEmpty(old_field, "old field");
    out.new_field = Utils::checkNotEmpty(new_field, "new field");

    return out;
}

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Migrate, c_query_prefix)
{
    DECLARE_PARSED_QUERY(Migrate);

    const auto [migrate, structure, structure_name, to, schema_name, using_] = extractor.extractTuple<6>();

    Utils::checkKeywordEquals(migrate, "migrate");
    Utils::checkKeywordEquals(structure, "structure");
    Utils::checkKeywordEquals(to, "to");

    out.structure_name = Utils::checkNotEmpty(structure_name, "structure name");
    out.new_schema_name = Utils::checkNotEmpty(schema_name, "new schema name");

    if (!using_.empty())
    {
        Utils::checkKeywordEquals(using_, "using");

        out.mappings = extractor.extractList<Mapping>(parseMapping);

        if (out.mappings->empty()) { throw Utils::buildMissingError("mappings"); }

        std::unordered_set<std::string> olds{};
        std::unordered_set<std::string> news{};
        for (const auto& mapping : *out.mappings)
        {
            const auto& handle_value = [](auto& set, const auto& value) -> void {
                if (set.find(value) != set.end())
                {
                    throw Utils::buildError("Found duplicate field '", value, "'");
                }

                set.insert(value);
                };

            handle_value(olds, mapping.old_field);
            handle_value(news, mapping.new_field);
        }
    }

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
