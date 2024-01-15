#include <algorithm>
#include <array>

#include "CppExtensions/include/ItemArray.hpp"
#include "CppExtensions/include/StringUtils.hpp"
#include "Errors.hpp"
#include "QueryParser.hpp"
#include "QueryParsers.hpp"

namespace LunarDB::Moonlight::API {

ParsedQuery parseQuery(std::string_view query)
{
    using namespace Implementation;
    using namespace CppExtensions;

    StringUtils::trim(query);

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

    const auto parser_opt = s_parsers.find_if([query](const ParserBundle& query_parser) {
        return StringUtils::startsWithIgnoreCase(query, query_parser.first);
        });

    if (static_cast<bool>(parser_opt))
    {
        return parser_opt.value()(query);
    }
    else
    {
        throw Errors::buildError("Invalid query syntax");
    }
}

} // namespace LunarDB::Moonlight::API
