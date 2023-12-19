#include "QueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "migrate" };

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Migrate, c_query_prefix)
{
    DECLARE_PARSED_QUERY(obj, Migrate);

    // TODO: provide implementation

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
