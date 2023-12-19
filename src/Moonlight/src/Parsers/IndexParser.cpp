#include "QueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "index" };

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Index, c_query_prefix)
{
    DECLARE_PARSED_QUERY(obj, Index);

    // TODO: provide implementation

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
