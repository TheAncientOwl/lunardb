#include "../IQueryParsers.hpp"
#include "../Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "lock" };

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Lock, c_query_prefix)
{
    DECLARE_PARSED_QUERY(obj, Lock);

    // TODO: provide implementation

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
