#pragma once

#include <string>
#include <utility>

#include "ParsedQuery.hpp"
#include "QueryExtractor.hpp"

///
/// @brief Provide makeParser() and parse(query) signatures under Specialization namespace.
///
#define PROVIDE_QUERY_PARSER(Specialization)                        \
    namespace Specialization {                                      \
    [[nodiscard]] ParserBundle makeParser();                        \
    [[nodiscard]] API::ParsedQuery parse(QueryExtractor extractor); \
    }

namespace LunarDB::Moonlight::Implementation {

using Parser = API::ParsedQuery (*)(QueryExtractor);
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
PROVIDE_QUERY_PARSER(Grant)
PROVIDE_QUERY_PARSER(Revoke)
PROVIDE_QUERY_PARSER(Commit)
PROVIDE_QUERY_PARSER(Rollback)
PROVIDE_QUERY_PARSER(SavePoint)
PROVIDE_QUERY_PARSER(Database)
PROVIDE_QUERY_PARSER(Rebind)
PROVIDE_QUERY_PARSER(Schema)
PROVIDE_QUERY_PARSER(User)

} // namespace LunarDB::Moonlight::Implementation
