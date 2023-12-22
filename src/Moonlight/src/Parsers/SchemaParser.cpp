#include "QueryParsers.hpp"
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
    if (separator_pos == std::string_view::npos) { throw Utils::buildMissingError(":"); }

    auto field_name = str.substr(0, separator_pos);
    Utils::trim(field_name);
    out.name = Utils::checkNotEmpty(field_name, "field name");
    Utils::checkValidIdentifier(out.name);

    auto type = str.substr(separator_pos + 1, str.length());

    Utils::trim(type);

    Utils::checkNotEmpty(type, "type");

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
            throw Utils::buildMissingError(">");
        }
        out.array = true;
    }
    else if (type.back() == '>')
    {
        throw Utils::buildMissingError("ArrayOf<");
    }
    else
    {
        out.array = false;
    }

    Utils::trim(type);
    out.type = Utils::checkNotEmpty(type, "type");
    Utils::checkValidIdentifier(out.type);

    return out;
}

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Schema, c_query_prefix)
{
    DECLARE_PARSED_QUERY(Schema);

    const auto [schema, schema_name] = extractor.extractTuple<2>();
    if (extractor.empty()) { throw Utils::buildInvalidQueryFormatError(c_query_prefix); }

    Utils::checkKeywordEquals(schema, "schema");

    out.name = Utils::checkNotEmpty(schema_name, "schema name");
    out.fields = extractor.extractList<QueryData::Schema::Field>(parseField, ';', std::make_pair('{', '}'));

    if (!extractor.empty()) { throw Utils::buildInvalidQueryFormatError(c_query_prefix); }

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
