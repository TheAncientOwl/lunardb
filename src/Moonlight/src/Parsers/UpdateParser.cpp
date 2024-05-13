#include <unordered_set>

#include "Errors.hpp"
#include "QueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

namespace CppExtensions = LunarDB::Common::CppExtensions;
namespace StringUtils = CppExtensions::StringUtils;

namespace {

constexpr auto c_query_prefix{"update"};

Common::QueryData::Update::Modify parseModify(std::string_view str)
{
    Common::QueryData::Update::Modify out{};

    out.field = Errors::assertNotEmpty(Utils::extractWord(str, ' '), "field name");

    auto const arrow = Utils::extractWord(str, ' ');
    Errors::assertKeywordEquals(arrow, "=>");

    StringUtils::trim(str);
    if (str.find("=>") != std::string_view::npos)
    {
        throw Errors::buildMissingError(",");
    }

    out.expression = Errors::assertNotEmpty(str, "field expression");

    return out;
}

} // namespace

API::ParsedQuery Update::parse(QueryExtractor extractor)
{
    auto out_parsed_query = API::ParsedQuery::make<Common::QueryData::Update>();
    auto& out = out_parsed_query.get<Common::QueryData::Update>();

    auto const [update, structure, structure_name] = extractor.extractTuple<3>();
    if (extractor.empty())
    {
        throw Errors::buildInvalidQueryFormatError(c_query_prefix);
    }

    Errors::assertKeywordEquals(update, "update");
    Errors::assertKeywordEquals(structure, "structure");

    out.structure_name = Errors::assertNotEmpty(structure_name, "structure name");

    out.where = Utils::extractWhereClause(extractor.unsafe_data());
    StringUtils::ltrim(extractor.unsafe_data());
    if (extractor.empty())
    {
        throw Errors::buildInvalidQueryFormatError(c_query_prefix);
    }

    auto const modify = extractor.extractOne();
    Errors::assertKeywordEquals(modify, "modify");

    out.modify = extractor.extractList<Common::QueryData::Update::Modify>(parseModify);
    if (!extractor.empty())
    {
        throw Errors::buildInvalidQueryFormatError(c_query_prefix);
    }

    std::unordered_set<std::string_view> modify_fields{};
    for (auto const& modify : out.modify)
    {
        if (modify_fields.find(modify.field) != modify_fields.end())
        {
            throw Errors::buildError(
                "Modify fields should be unique, found '", modify.field, "' twice");
        }
        modify_fields.insert(modify.field);
    }

    return out_parsed_query;
}

} // namespace LunarDB::Moonlight::Implementation
