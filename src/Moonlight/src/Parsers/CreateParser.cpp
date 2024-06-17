#include <unordered_set>

#include "Errors.hpp"
#include "LunarDB/Moonlight/QueryParsers.hpp"
#include "Utils.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_MOONLIGHT)

namespace LunarDB::Moonlight::Implementation {

namespace StringUtils = Common::CppExtensions::StringUtils;

namespace {

constexpr auto c_query_prefix{"create"};

using Binding = Common::QueryData::Create::Single::Binding;

Binding parseBinding(std::string_view str)
{
    Binding out{};

    QueryExtractor extractor{str};

    auto const [field, from, table] = extractor.extractTuple<3>();
    if (!extractor.empty())
    {
        throw Errors::buildInvalidSequenceError(str);
    }

    Errors::assertKeywordEquals(from, "from");

    out.field = Errors::assertNotEmpty(field, "field name");
    out.table = Errors::assertNotEmpty(table, "table name");

    return out;
}

///
/// @brief Parsing starting from 'StructureName'
///
Common::QueryData::Create::Single parseSingle(QueryExtractor extractor)
{
    Common::QueryData::Create::Single out{};

    auto const [structure_name, based, on, schema_name, blended_or_binding] =
        extractor.extractTuple<5>();

    Errors::assertKeywordEquals(based, "based");
    Errors::assertKeywordEquals(on, "on");

    out.structure_name = Errors::assertNotEmpty(structure_name, "structure name");
    out.schema_name = Errors::assertNotEmpty(schema_name, "schema name");

    if (!blended_or_binding.empty())
    {
        if (StringUtils::equalsIgnoreCase(blended_or_binding, "blended"))
        {
            out.blended = true;
        }
        else
        {
            Errors::assertKeywordEquals(blended_or_binding, "binding");

            out.bindings = extractor.extractList<Binding>(parseBinding);

            if (out.bindings.empty())
            {
                throw Errors::buildMissingError("bindings");
            }

            std::unordered_set<std::string_view> fields{};
            for (auto const& binding : out.bindings)
            {
                if (fields.find(binding.field) != fields.end())
                {
                    throw Errors::buildError("Found '", binding.field, "' twice");
                }
                fields.insert(binding.field);
            }

            out.blended = false;
            if (!extractor.empty())
            {
                auto const blended = extractor.extractOne();
                if (!extractor.empty())
                {
                    throw Errors::buildInvalidQueryFormatError(c_query_prefix);
                }
                Errors::assertKeywordEquals(blended, "blended");
                out.blended = true;
            }
        }

        if (!extractor.empty())
        {
            throw Errors::buildInvalidQueryFormatError(c_query_prefix);
        }
    }

    return out;
}

///
/// @brief Parsing starting from 'from'
///
Common::QueryData::Create::Multiple parseMultiple(QueryExtractor extractor)
{
    Common::QueryData::Create::Multiple out{};

    Errors::assertKeywordEquals(extractor.extractOne(), "from");

    // parse schemas
    auto const schemas = extractor.extractList();
    if (schemas.empty())
    {
        throw Errors::buildMissingError("schemas");
    }

    std::set<std::string_view> schemas_set{};
    std::copy(schemas.begin(), schemas.end(), std::inserter(schemas_set, schemas_set.begin()));

    out.schema_names = std::vector<std::string>{};
    out.schema_names.reserve(schemas_set.size());
    std::transform(
        schemas_set.begin(),
        schemas_set.end(),
        std::back_inserter(out.schema_names),
        [](std::string_view sv) -> std::string { return std::string(sv); });

    // parse name format
    if (extractor.empty())
    {
        out.structure_name_format = "%TypeName%_Structure_%Hash%";
    }
    else
    {
        auto const [using_, format_] = extractor.extractTuple<2>();

        Errors::assertKeywordEquals(using_, "using");
        Errors::assertKeywordEquals(format_, "format");

        auto format = extractor.data();
        StringUtils::trim(format);
        if (format.empty() || format.size() < 2)
        {
            throw Errors::buildMissingError("format");
        }
        if (format.front() != '"' || format.back() != '"')
        {
            throw Errors::buildMissingError("\"");
        }
        format.remove_prefix(1);
        format.remove_suffix(1);
        out.structure_name_format = Errors::assertNotEmpty(format, "format");
    }

    return out;
}

} // namespace

API::ParsedQuery Create::parse(QueryExtractor extractor)
{
    CLOG_VERBOSE("Create::parse()");

    auto out_parsed_query = API::ParsedQuery::make<Common::QueryData::Create>();
    auto& out = out_parsed_query.get<Common::QueryData::Create>();

    auto const [create, any] = extractor.extractTuple<2>();

    Errors::assertKeywordEquals(create, "create");

    if (any.empty())
    {
        throw Errors::buildInvalidQueryFormatError(c_query_prefix);
    }

    std::string_view structure_type{};
    if (StringUtils::equalsIgnoreCase(any, "volatile"))
    {
        out.is_volatile = true;
        structure_type = extractor.extractOne();
    }
    else
    {
        out.is_volatile = false;
        structure_type = any;
    }

    if (StringUtils::equalsIgnoreCase(structure_type, "table"))
    {
        out.structure_type = Common::QueryData::Primitives::EStructureType::Table;
        out.single = parseSingle(extractor);
        out.multiple = std::nullopt;
    }
    else if (StringUtils::equalsIgnoreCase(structure_type, "tables"))
    {
        out.structure_type = Common::QueryData::Primitives::EStructureType::Table;
        out.single = std::nullopt;
        out.multiple = parseMultiple(extractor);
    }
    else if (StringUtils::equalsIgnoreCase(structure_type, "collection"))
    {
        out.structure_type = Common::QueryData::Primitives::EStructureType::Collection;
        out.single = parseSingle(extractor);
        out.multiple = std::nullopt;
    }
    else if (StringUtils::equalsIgnoreCase(structure_type, "collections"))
    {
        out.structure_type = Common::QueryData::Primitives::EStructureType::Collection;
        out.single = std::nullopt;
        out.multiple = parseMultiple(extractor);
    }
    else
    {
        throw Errors::buildInvalidQueryFormatError(c_query_prefix);
    }

    return out_parsed_query;
}

} // namespace LunarDB::Moonlight::Implementation
