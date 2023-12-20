#include "QueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "update" };

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Update, c_query_prefix)
{
    DECLARE_PARSED_QUERY(Update);

    // TODO: provide implementation

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
