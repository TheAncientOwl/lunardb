#include <unordered_set>

#include "QueryParser.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace CppExtensions;

namespace {

constexpr auto c_query_prefix{ "update" };

QueryData::Update::Modify parseModify(std::string_view str)
{
    QueryData::Update::Modify out{};

    out.field = Errors::assertNotEmpty(Utils::extractWord(str, ' '), "field name");

    const auto arrow = Utils::extractWord(str, ' ');
    Errors::assertKeywordEquals(arrow, "=>");

    StringUtils::trim(str);
    if (str.find("=>") != std::string_view::npos) { throw Errors::buildMissingError(","); }

    out.expression = Errors::assertNotEmpty(str, "field expression");


    return out;
}

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Update, c_query_prefix)
{
    DECLARE_PARSED_QUERY(Update);

    const auto [update, structure, structure_name] = extractor.extractTuple<3>();
    if (extractor.empty()) { throw Errors::buildInvalidQueryFormatError(c_query_prefix); }

    Errors::assertKeywordEquals(update, "update");
    Errors::assertKeywordEquals(structure, "structure");

    out.structure_name = Errors::assertNotEmpty(structure_name, "structure name");

    out.where = Utils::extractWhereClause(extractor.unsafe_data());
    StringUtils::ltrim(extractor.unsafe_data());
    if (extractor.empty()) { throw Errors::buildInvalidQueryFormatError(c_query_prefix); }

    const auto modify = extractor.extractOne();
    Errors::assertKeywordEquals(modify, "modify");

    out.modify = extractor.extractList<QueryData::Update::Modify>(parseModify);
    if (!extractor.empty()) { throw Errors::buildInvalidQueryFormatError(c_query_prefix); }

    std::unordered_set<std::string_view> modify_fields{};
    for (const auto& modify : out.modify)
    {
        if (modify_fields.find(modify.field) != modify_fields.end())
        {
            throw Errors::buildError("Modify fields should be unique, found '", modify.field, "' twice");
        }
        modify_fields.insert(modify.field);
    }

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
