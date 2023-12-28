#include "QueryParsers.hpp"
#include "Errors.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "schema" };

QueryData::Schema::Field parseField(std::string_view str)
{
    QueryData::Schema::Field out{};

    const auto separator_pos = str.find_first_of(':');
    if (separator_pos == std::string_view::npos) { throw Errors::buildMissingError(":"); }

    auto field_name = str.substr(0, separator_pos);
    Utils::trim(field_name);
    out.name = Errors::assertNotEmpty(field_name, "field name");
    Errors::assertValidIdentifier(out.name);

    auto type = str.substr(separator_pos + 1, str.length());

    Utils::trim(type);

    Errors::assertNotEmpty(type, "type");

    if (type.back() == '?')
    {
        out.nullable = true;
        type.remove_suffix(1);
        Utils::trim(type);
    }
    else
    {
        out.nullable = false;
    }

    if (Utils::startsWithIgnoreCase(type, "ArrayOf<"))
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

    Utils::trim(type);
    out.type = Errors::assertNotEmpty(type, "type");
    Errors::assertValidIdentifier(out.type);

    return out;
}

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Schema, c_query_prefix)
{
    DECLARE_PARSED_QUERY(Schema);

    const auto [schema, schema_name] = extractor.extractTuple<2>();
    if (extractor.empty()) { throw Errors::buildInvalidQueryFormatError(c_query_prefix); }

    Errors::assertKeywordEquals(schema, "schema");

    out.name = Errors::assertNotEmpty(schema_name, "schema name");
    out.fields = extractor.extractList<QueryData::Schema::Field>(parseField, ';', std::make_pair('{', '}'));

    if (!extractor.empty()) { throw Errors::buildInvalidQueryFormatError(c_query_prefix); }

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
