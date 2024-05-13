#include <unordered_set>

#include "Errors.hpp"
#include "QueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

namespace CppExtensions = LunarDB::Common::CppExtensions;

namespace {

constexpr auto c_query_prefix{"migrate"};

using Mapping = Common::QueryData::Migrate::Mapping;

Mapping parseMapping(std::string_view str)
{
    Mapping out{};

    QueryExtractor extractor{str};
    auto const [old_field, arrow, new_field] = extractor.extractTuple<3>();

    if (!extractor.empty())
    {
        throw Errors::buildInvalidSequenceError(str);
    }

    Errors::assertKeywordEquals(arrow, "=>");

    out.old_field = Errors::assertNotEmpty(old_field, "old field");
    out.new_field = Errors::assertNotEmpty(new_field, "new field");

    return out;
}

} // namespace

API::ParsedQuery Migrate::parse(QueryExtractor extractor)
{
    auto out_parsed_query = API::ParsedQuery::make<Common::QueryData::Migrate>();
    auto& out = out_parsed_query.get<Common::QueryData::Migrate>();

    auto const [migrate, structure, structure_name, to, schema_name, using_] =
        extractor.extractTuple<6>();

    Errors::assertKeywordEquals(migrate, "migrate");
    Errors::assertKeywordEquals(structure, "structure");
    Errors::assertKeywordEquals(to, "to");

    out.structure_name = Errors::assertNotEmpty(structure_name, "structure name");
    out.new_schema_name = Errors::assertNotEmpty(schema_name, "new schema name");

    if (!using_.empty())
    {
        Errors::assertKeywordEquals(using_, "using");

        out.mappings = extractor.extractList<Mapping>(parseMapping);

        if (out.mappings.empty())
        {
            throw Errors::buildMissingError("mappings");
        }

        std::unordered_set<std::string_view> olds{};
        std::unordered_set<std::string_view> news{};
        for (auto const& mapping : out.mappings)
        {
            auto const& handle_value = [](auto& set, auto const& value) -> void {
                if (set.find(value) != set.end())
                {
                    throw Errors::buildError("Found duplicate field '", value, "'");
                }

                set.insert(value);
            };

            handle_value(olds, mapping.old_field);
            handle_value(news, mapping.new_field);
        }
    }

    return out_parsed_query;
}

} // namespace LunarDB::Moonlight::Implementation
