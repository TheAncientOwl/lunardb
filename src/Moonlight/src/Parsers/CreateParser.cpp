#include "QueryParsers.hpp"
#include "Utils.hpp"

#include <unordered_set>

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "create" };

using Binding = QueryData::Create::Single::Binding;

Binding parseBinding(std::string_view str)
{
    Binding out{};

    QueryExtractor extractor{ str };

    const auto [field, from, table] = extractor.extractTuple<3>();
    if (!extractor.empty()) { throw Utils::buildInvalidSequenceError(str); }

    Utils::checkKeywordEquals(from, "from");

    out.field = Utils::checkNotEmpty(field, "field name");
    out.table = Utils::checkNotEmpty(table, "table name");

    return out;
}

///
/// @brief Parsing starting from 'StructureName'
///
QueryData::Create::Single parseSingle(QueryExtractor extractor)
{
    QueryData::Create::Single out{};

    const auto [structure_name, based, on, schema_name, blended_or_binding] = extractor.extractTuple<5>();

    Utils::checkKeywordEquals(based, "based");
    Utils::checkKeywordEquals(on, "on");

    out.structure_name = Utils::checkNotEmpty(structure_name, "structure name");
    out.schema_name = Utils::checkNotEmpty(schema_name, "schema name");

    if (!blended_or_binding.empty())
    {
        if (Utils::equalsIgnoreCase(blended_or_binding, "blended"))
        {
            out.blended = true;
        }
        else
        {
            Utils::checkKeywordEquals(blended_or_binding, "binding");

            out.bindings = extractor.extractList<Binding>(parseBinding);

            if (out.bindings.empty()) { throw Utils::buildMissingError("bindings"); }

            std::unordered_set<std::string_view> fields{};
            for (const auto& binding : out.bindings)
            {
                if (fields.find(binding.field) != fields.end())
                {
                    throw Utils::buildError("Found '", binding.field, "' twice");
                }
                fields.insert(binding.field);
            }

            out.blended = false;
            if (!extractor.empty())
            {
                const auto blended = extractor.extractOne();
                if (!extractor.empty()) { throw Utils::buildInvalidQueryFormatError(c_query_prefix); }
                Utils::checkKeywordEquals(blended, "blended");
                out.blended = true;
            }
        }

        if (!extractor.empty()) { throw Utils::buildInvalidQueryFormatError(c_query_prefix); }
    }

    return out;
}

///
/// @brief Parsing starting from 'from'
///
QueryData::Create::Multiple parseMultiple(QueryExtractor extractor)
{
    QueryData::Create::Multiple out{};

    Utils::checkKeywordEquals(extractor.extractOne(), "from");

    // parse schemas
    const auto schemas = extractor.extractList();
    if (schemas.empty()) { throw Utils::buildMissingError("schemas"); }

    std::set<std::string_view> schemas_set{};
    std::copy(schemas.begin(), schemas.end(), std::inserter(schemas_set, schemas_set.begin()));

    out.schema_names = std::vector<std::string>{};
    out.schema_names.reserve(schemas_set.size());
    std::transform(schemas_set.begin(), schemas_set.end(),
        std::back_inserter(out.schema_names),
        [](std::string_view sv) -> std::string { return std::string(sv); }
    );

    // parse name format
    if (extractor.empty())
    {
        out.structure_name_format = "%TypeName%_Structure_%Hash%";
    }
    else
    {
        const auto [using_, format_] = extractor.extractTuple<2>();

        Utils::checkKeywordEquals(using_, "using");
        Utils::checkKeywordEquals(format_, "format");

        auto format = extractor.data();
        Utils::trim(format);
        if (format.empty() || format.size() < 2) { throw Utils::buildMissingError("format"); }
        if (format.front() != '"' || format.back() != '"') { throw Utils::buildMissingError("\""); }
        format.remove_prefix(1);
        format.remove_suffix(1);
        out.structure_name_format = Utils::checkNotEmpty(format, "format");
    }

    return out;
}

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Create, c_query_prefix)
{
    DECLARE_PARSED_QUERY(Create);

    const auto [create, any] = extractor.extractTuple<2>();

    Utils::checkKeywordEquals(create, "create");

    if (any.empty()) { throw Utils::buildInvalidQueryFormatError(c_query_prefix); }

    std::string_view structure_type{};
    if (Utils::equalsIgnoreCase(any, "volatile"))
    {
        out.is_volatile = true;
        structure_type = extractor.extractOne();
    }
    else
    {
        out.is_volatile = false;
        structure_type = any;
    }

    if (Utils::equalsIgnoreCase(structure_type, "table"))
    {
        out.structure_type = QueryData::Primitives::EStructureType::Table;
        out.single = parseSingle(extractor);
        out.multiple = std::nullopt;
    }
    else if (Utils::equalsIgnoreCase(structure_type, "tables"))
    {
        out.structure_type = QueryData::Primitives::EStructureType::Table;
        out.single = std::nullopt;
        out.multiple = parseMultiple(extractor);
    }
    else if (Utils::equalsIgnoreCase(structure_type, "collection"))
    {
        out.structure_type = QueryData::Primitives::EStructureType::Collection;
        out.single = parseSingle(extractor);
        out.multiple = std::nullopt;
    }
    else if (Utils::equalsIgnoreCase(structure_type, "collections"))
    {
        out.structure_type = QueryData::Primitives::EStructureType::Collection;
        out.single = std::nullopt;
        out.multiple = parseMultiple(extractor);
    }
    else { throw Utils::buildInvalidQueryFormatError(c_query_prefix); }

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
