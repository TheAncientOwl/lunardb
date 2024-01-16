#pragma once

#include <string>
#include <utility>

#include "ParsedQuery.hpp"
#include "QueryExtractor.hpp"

#define PROVIDE_QUERY_PARSER(Specialization) \
namespace Specialization { \
[[nodiscard]] ParserBundle makeParser(); \
[[nodiscard]] API::ParsedQuery parse(std::string query); \
}

#define PROVIDE_QUERY_PARSER_IMPL(Specialization, QueryPrefix) \
ParserBundle Specialization::makeParser() { return std::make_pair(QueryPrefix, Specialization::parse); } \
API::ParsedQuery Specialization::parse(std::string query)

#define DECLARE_PARSED_QUERY(Type) \
API::ParsedQuery out_parsed_query = API::ParsedQuery::make<QueryData::Type>(std::move(query)); \
auto query_view = out_parsed_query.query(); \
StringUtils::trim(query_view); \
QueryExtractor extractor{ query_view }; \
auto& out = out_parsed_query.get<QueryData::Type>()

#define RETURN_PARSED_QUERY \
return out_parsed_query

namespace LunarDB::Moonlight::Implementation {

using Parser = API::ParsedQuery(*)(std::string);
using ParserBundle = std::pair<std::string, Parser>;

PROVIDE_QUERY_PARSER(Create)
PROVIDE_QUERY_PARSER(Drop)
PROVIDE_QUERY_PARSER(Migrate)
PROVIDE_QUERY_PARSER(Truncate)
PROVIDE_QUERY_PARSER(Rename)
PROVIDE_QUERY_PARSER(Select)
PROVIDE_QUERY_PARSER(Insert)
PROVIDE_QUERY_PARSER(Update)
PROVIDE_QUERY_PARSER(Delete)
PROVIDE_QUERY_PARSER(Lock)
PROVIDE_QUERY_PARSER(Grant)
PROVIDE_QUERY_PARSER(Revoke)
PROVIDE_QUERY_PARSER(Commit)
PROVIDE_QUERY_PARSER(Rollback)
PROVIDE_QUERY_PARSER(SavePoint)
PROVIDE_QUERY_PARSER(Index)
PROVIDE_QUERY_PARSER(Database)
PROVIDE_QUERY_PARSER(View)
PROVIDE_QUERY_PARSER(Rebind)
PROVIDE_QUERY_PARSER(Schema)

} // namespace LunarDB::Moonlight::Implementation
