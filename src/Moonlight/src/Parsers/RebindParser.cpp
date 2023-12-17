#include "../IQueryParsers.hpp"
#include "../Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "rebind" };

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Rebind, c_query_prefix)
{
    DECLARE_PARSED_QUERY(obj, Rebind);

    // TODO: provide implementation

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
