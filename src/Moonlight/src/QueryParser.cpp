#include <algorithm>
#include <array>

#include "Errors.hpp"
#include "LunarDB/Common/CppExtensions/ItemArray.hpp"
#include "LunarDB/Common/CppExtensions/StringUtils.hpp"
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
        Grant::makeParser(),
        Revoke::makeParser(),
        Commit::makeParser(),
        Rollback::makeParser(),
        SavePoint::makeParser(),
        Index::makeParser(),
        Database::makeParser(),
        Rebind::makeParser(),
        Schema::makeParser()};

    auto const parser_opt = s_parsers.find_if([query](ParserBundle const& query_parser) {
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

#define PROVIDE_PARSER_BUNLDER(Specialization, QueryPrefix)        \
    ParserBundle Specialization::makeParser()                      \
    {                                                              \
        return std::make_pair(QueryPrefix, Specialization::parse); \
    }

namespace LunarDB::Moonlight::Implementation {

PROVIDE_PARSER_BUNLDER(Create, "create")
PROVIDE_PARSER_BUNLDER(Drop, "drop")
PROVIDE_PARSER_BUNLDER(Migrate, "migrate")
PROVIDE_PARSER_BUNLDER(Truncate, "truncate")
PROVIDE_PARSER_BUNLDER(Rename, "rename")
PROVIDE_PARSER_BUNLDER(Select, "select")
PROVIDE_PARSER_BUNLDER(Insert, "insert")
PROVIDE_PARSER_BUNLDER(Update, "update")
PROVIDE_PARSER_BUNLDER(Delete, "delete")
PROVIDE_PARSER_BUNLDER(Grant, "grant")
PROVIDE_PARSER_BUNLDER(Revoke, "revoke")
PROVIDE_PARSER_BUNLDER(Commit, "commit")
PROVIDE_PARSER_BUNLDER(Rollback, "rollback")
PROVIDE_PARSER_BUNLDER(SavePoint, "savepoint")
PROVIDE_PARSER_BUNLDER(Index, "index")
PROVIDE_PARSER_BUNLDER(Database, "database")
PROVIDE_PARSER_BUNLDER(Rebind, "rebind")
PROVIDE_PARSER_BUNLDER(Schema, "schema")

} // namespace LunarDB::Moonlight::Implementation
