#include "QueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "view" };

} // namespace

PROVIDE_QUERY_PARSER_IMPL(View, c_query_prefix)
{
    DECLARE_PARSED_QUERY(View);

    const auto [view, view_name, as] = extractor.extractTuple<3>();

    Utils::checkKeywordEquals(view, "view");
    Utils::checkKeywordEquals(as, "as");

    out.name = Utils::checkNotEmpty(view_name, "view name");

    out.as_select = Select::parse(extractor).get<QueryData::Select>();

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
