#pragma once

#include <string>
#include <utility>

#include "ParsedQuery.hpp"
#include "QueryExtractor.hpp"

#define PROVIDE_QUERY_PARSER(Specialization) \
namespace Specialization { \
[[nodiscard]] ParserBundle makeParser(); \
[[nodiscard]] API::ParsedQuery parse(QueryExtractor extractor); \
}

#define PROVIDE_QUERY_PARSER_IMPL(Specialization, QueryPrefix) \
ParserBundle Specialization::makeParser() { return std::make_pair(QueryPrefix, Specialization::parse); } \
API::ParsedQuery Specialization::parse(QueryExtractor extractor)

#define DECLARE_PARSED_QUERY(type) \
API::ParsedQuery out_parsed_query = API::ParsedQuery::make<QueryData::type>(); \
auto& out = out_parsed_query.get<QueryData::type>()

#define RETURN_PARSED_QUERY \
return out_parsed_query

namespace LunarDB::Moonlight::Implementation {

using Parser = API::ParsedQuery(*)(QueryExtractor);
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
