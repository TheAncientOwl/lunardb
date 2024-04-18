#include "Errors.hpp"
#include "QueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace CppExtensions;

namespace {

constexpr auto c_query_prefix{"rebind"};

} // namespace

API::ParsedQuery Rebind::parse(QueryExtractor extractor)
{
    auto out_parsed_query = API::ParsedQuery::make<QueryData::Rebind>();
    auto& out = out_parsed_query.get<QueryData::Rebind>();

    const auto [rebind, structure_field, to, bind_structure_name] = extractor.extractTuple<4>();

    if (!extractor.empty())
    {
        const auto clean = extractor.extractOne();
        Errors::assertKeywordEquals(clean, "clean");
        out.clean = true;
    }
    else
    {
        out.clean = false;
    }

    if (!extractor.empty())
    {
        throw Errors::buildInvalidQueryFormatError(c_query_prefix);
    }

    Errors::assertKeywordEquals(rebind, "rebind");
    Errors::assertKeywordEquals(to, "to");

    const auto [structure_name, field] = Utils::parseResolutionOperator(structure_field);

    out.structure_name = Errors::assertNotEmpty(structure_name, "structure name");
    out.field = Errors::assertNotEmpty(field, "field name");
    out.bind_structure_name = Errors::assertNotEmpty(bind_structure_name, "rebind structure name");

    return out_parsed_query;
}

} // namespace LunarDB::Moonlight::Implementation
