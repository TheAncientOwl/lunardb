#include "QueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "rebind" };

///
/// @param str format StructureName::FieldName
/// @return pair<StructureName, FieldName>
std::pair<std::string_view, std::string_view> parseStructureFieldNames(std::string_view str)
{
    const auto first_sep_pos{ str.find_first_of(':') };
    const auto last_sep_pos{ str.find_last_of(':') };

    if (first_sep_pos == std::string_view::npos || last_sep_pos == std::string_view::npos ||
        first_sep_pos == last_sep_pos)
    {
        throw Utils::buildMissingError("':' separator on StructureName::FieldName");
    }

    if (last_sep_pos - first_sep_pos > 1)
    {
        throw Utils::buildUnknownSequenceError(str.substr(last_sep_pos, first_sep_pos - last_sep_pos + 1));
    }

    return std::make_pair(str.substr(0, first_sep_pos), str.substr(last_sep_pos + 1, str.length() - last_sep_pos));
}

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Rebind, c_query_prefix)
{
    DECLARE_PARSED_QUERY(obj, Rebind);

    QueryExtractor extractor{ query };
    const auto [rebind, structure_field, to, bind_structure_name] = extractor.extractTuple<4>();

    if (!extractor.empty())
    {
        const auto clean = extractor.extractOne();
        Utils::checkKeyword(clean, "clean");
        obj.clean = true;
    }
    else
    {
        obj.clean = false;
    }

    if (!extractor.empty()) { throw Utils::buildInvalidQueryFormatError(c_query_prefix); }

    Utils::checkKeyword(rebind, "rebind");
    Utils::checkKeyword(to, "to");

    const auto [structure_name, field] = parseStructureFieldNames(structure_field);

    if (structure_name.empty()) { throw Utils::buildMissingError("structure name"); }
    if (field.empty()) { throw Utils::buildMissingError("field name"); }
    if (bind_structure_name.empty()) { throw Utils::buildMissingError("rebind structure name"); }

    obj.structure_name = structure_name;
    obj.field = field;
    obj.bind_structure_name = bind_structure_name;

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
