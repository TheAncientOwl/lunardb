#include "IQueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "truncate" };

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Truncate, c_query_prefix)
{
    DECLARE_PARSED_QUERY(obj, Truncate);

    // TODO: provide implementation

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
