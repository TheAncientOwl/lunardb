#include <algorithm>
#include <array>

#include "Errors.hpp"
#include "LunarDB/Common/CppExtensions/StringUtils.hpp"
#include "LunarDB/Moonlight/QueryParsers.hpp"
#include "QueryParser.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_MOONLIGHT)

namespace LunarDB::Moonlight::API {

LUNAR_SINGLETON_INIT_IMPL(QueryParsersManager)
{
}

void QueryParsersManager::addParser(Implementation::ParserBundle bundle)
{
    m_parsers.emplace(std::move(bundle));
}

ParsedQuery parseQuery(std::string_view query)
{
    namespace CppExtensions = LunarDB::Common::CppExtensions;
    namespace DataStructures = CppExtensions::DataStructures;
    namespace StringUtils = CppExtensions::StringUtils;

    CLOG_VERBOSE("parseQuery(): Parsing query ->", query);

    StringUtils::trim(query);

    auto const& parsers{QueryParsersManager::Instance()};

    auto const parser_opt = parsers.find_if([query](Implementation::ParserBundle const& query_parser) {
        return StringUtils::startsWithIgnoreCase(query, query_parser.first);
    });

    if (static_cast<bool>(parser_opt))
    {
        auto const parsed_query{parser_opt.value()(query)};
        CLOG_VERBOSE("parseQuery(): Query parsed successfully ->", query);
        return parsed_query;
    }
    else
    {
        CLOG_VERBOSE("parseQuery(): Invalid query syntax ->", query);
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
PROVIDE_PARSER_BUNLDER(Database, "database")
PROVIDE_PARSER_BUNLDER(Rebind, "rebind")
PROVIDE_PARSER_BUNLDER(Schema, "schema")
PROVIDE_PARSER_BUNLDER(User, "user")
PROVIDE_PARSER_BUNLDER(Auth, "auth")

} // namespace LunarDB::Moonlight::Implementation
