#include "Errors.hpp"
#include "QueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace CppExtensions;

namespace {

constexpr auto c_query_prefix{ "view" };

} // namespace

API::ParsedQuery View::parse(QueryExtractor extractor)
{
    auto out_parsed_query = API::ParsedQuery::make<QueryData::View>();
    auto& out = out_parsed_query.get<QueryData::View>();

    const auto [view, view_name, as] = extractor.extractTuple<3>();

    Errors::assertKeywordEquals(view, "view");
    Errors::assertKeywordEquals(as, "as");

    out.name = Errors::assertNotEmpty(view_name, "view name");

    out.as_select = Select::parse(extractor).get<QueryData::Select>();

    return out_parsed_query;
}

} // namespace LunarDB::Moonlight::Implementation
