#include "Errors.hpp"
#include "QueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

namespace CppExtensions = LunarDB::Common::CppExtensions;
namespace StringUtils = CppExtensions::StringUtils;

namespace {

constexpr auto c_query_prefix{"schema"};

// TODO: Add types validation
Common::QueryData::Schema::Field parseField(std::string_view str)
{
    using namespace std::literals;

    Common::QueryData::Schema::Field out{};

    auto const separator_pos = str.find_first_of(':');
    if (separator_pos == std::string_view::npos)
    {
        throw Errors::buildMissingError(":");
    }

    auto field_name = str.substr(0, separator_pos);
    StringUtils::trim(field_name);
    out.name = Errors::assertNotEmpty(field_name, "field name");
    Errors::assertValidIdentifier(out.name);

    auto type = str.substr(separator_pos + 1, str.length());

    StringUtils::trim(type);

    Errors::assertNotEmpty(type, "type");

    if (type.back() == '?')
    {
        out.nullable = true;
        type.remove_suffix(1);
        StringUtils::trim(type);
    }
    else
    {
        out.nullable = false;
    }

    if (StringUtils::startsWithIgnoreCase(type, "ArrayOf<"))
    {
        if (type.back() == '>')
        {
            type.remove_suffix(1);
            type.remove_prefix("ArrayOf<"sv.length());
        }
        else
        {
            throw Errors::buildMissingError(">");
        }
        out.array = true;
    }
    else if (type.back() == '>')
    {
        throw Errors::buildMissingError("ArrayOf<");
    }
    else
    {
        out.array = false;
    }

    StringUtils::trim(type);
    out.type = Errors::assertNotEmpty(type, "type");
    Errors::assertValidIdentifier(out.type);

    return out;
}

} // namespace

API::ParsedQuery Schema::parse(QueryExtractor extractor)
{
    auto out_parsed_query = API::ParsedQuery::make<Common::QueryData::Schema>();
    auto& out = out_parsed_query.get<Common::QueryData::Schema>();

    auto const [schema, schema_name] = extractor.extractTuple<2>();
    if (extractor.empty())
    {
        throw Errors::buildInvalidQueryFormatError(c_query_prefix);
    }

    Errors::assertKeywordEquals(schema, "schema");

    out.name = Errors::assertNotEmpty(schema_name, "schema name");
    out.fields = extractor.extractList<Common::QueryData::Schema::Field>(
        parseField, ';', std::make_pair('{', '}'));

    if (!extractor.empty())
    {
        throw Errors::buildInvalidQueryFormatError(c_query_prefix);
    }

    return out_parsed_query;
}

} // namespace LunarDB::Moonlight::Implementation
