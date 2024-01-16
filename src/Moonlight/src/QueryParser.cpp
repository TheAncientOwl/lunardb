#include <algorithm>
#include <array>

#include "CppExtensions/include/ItemArray.hpp"
#include "CppExtensions/include/StringUtils.hpp"
#include "Errors.hpp"
#include "QueryParser.hpp"
#include "QueryParsers.hpp"

namespace LunarDB::Moonlight::API {

ParsedQuery parseQuery(std::string query)
{
    using namespace Implementation;
    using namespace CppExtensions;

    static const DataStructures::ItemArray<ParserBundle, 20> s_parsers{
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

    std::string_view query_view = query;
    StringUtils::trim(query_view);

    const auto parser_opt = s_parsers.find_if([query_view](const ParserBundle& query_parser) {
        return StringUtils::startsWithIgnoreCase(query_view, query_parser.first);
        });


    if (!parser_opt.has_value())
    {
        throw Errors::buildError("Invalid query syntax");
    }

    return parser_opt.value()(std::move(query));
}

} // namespace LunarDB::Moonlight::API
