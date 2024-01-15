#include <algorithm>
#include <array>

#include "CppExtensions/include/StringUtils.hpp"
#include "Errors.hpp"
#include "QueryParser.hpp"
#include "QueryParsers.hpp"

namespace LunarDB::Moonlight::API {

ParsedQuery parseQuery(std::string_view query)
{
    using namespace Implementation;
    using namespace CppExtensions;

    static const std::array<ParserBundle, 20> s_parsers{
        Create::makeParser(),
        Drop::makeParser(),
        Migrate::makeParser(),
        Truncate::makeParser(),
        Rename::makeParser(),
        Select::makeParser(),
        Insert::makeParser(),
        Update::makeParser(),
        Delete::makeParser(),
        Lock::makeParser(),
        Grant::makeParser(),
        Revoke::makeParser(),
        Commit::makeParser(),
        Rollback::makeParser(),
        SavePoint::makeParser(),
        Index::makeParser(),
        Database::makeParser(),
        View::makeParser(),
        Rebind::makeParser(),
        Schema::makeParser()
    };

    StringUtils::trim(query);
    const auto parser_ptr = std::find_if(std::begin(s_parsers), std::end(s_parsers),
        [query](const auto& query_parser) { return StringUtils::startsWithIgnoreCase(query, query_parser.first); });

    if (parser_ptr == std::end(s_parsers))
    {
        throw Errors::buildError("Invalid query syntax");
    }

    return parser_ptr->second(query);
}

} // namespace LunarDB::Moonlight::API
