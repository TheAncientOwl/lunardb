#include "QueryParsers.hpp"
#include "Utils.hpp"

#include <unordered_set>

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "update" };

QueryData::Update::Modify parseModify(std::string_view str)
{
    QueryData::Update::Modify out{};

    out.field = Utils::checkNotEmpty(Utils::extractWord(str, ' '), "field name");

    const auto arrow = Utils::extractWord(str, ' ');
    Utils::checkKeywordEquals(arrow, "=>");

    Utils::trim(str);
    if (str.find("=>") != std::string_view::npos) { throw Utils::buildMissingError(","); }

    out.expression = Utils::checkNotEmpty(str, "field expression");


    return out;
}

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Update, c_query_prefix)
{
    DECLARE_PARSED_QUERY(Update);

    const auto [update, structure, structure_name] = extractor.extractTuple<3>();
    if (extractor.empty()) { throw Utils::buildInvalidQueryFormatError(c_query_prefix); }

    Utils::checkKeywordEquals(update, "update");
    Utils::checkKeywordEquals(structure, "structure");

    out.structure_name = Utils::checkNotEmpty(structure_name, "structure name");

    out.where = Utils::extractWhereClause(extractor.unsafe_data());
    Utils::ltrim(extractor.unsafe_data());
    if (extractor.empty()) { throw Utils::buildInvalidQueryFormatError(c_query_prefix); }

    const auto modify = extractor.extractOne();
    Utils::checkKeywordEquals(modify, "modify");

    out.modify = extractor.extractList<QueryData::Update::Modify>(parseModify);
    if (!extractor.empty()) { throw Utils::buildInvalidQueryFormatError(c_query_prefix); }

    std::unordered_set<std::string_view> modify_fields{};
    for (const auto modify : out.modify)
    {
        if (modify_fields.find(modify.field) != modify_fields.end())
        {
            throw Utils::buildError("Modify fields should be unique, found '", modify.field, "' twice");
        }
        modify_fields.insert(modify.field);
    }

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
