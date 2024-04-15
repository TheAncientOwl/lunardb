#pragma once

#include "Moonlight/ParsedQuery.hpp"
#include "Astral/QueryExecutorConfig.hpp"

#define PROVIDE_QUERY_EXECUTOR(Specialization) \
namespace Specialization { \
[[nodiscard]] ExecutorBundle makeExecutor(); \
void execute(const Moonlight::API::ParsedQuery& parsed_query, const Astral::API::QueryExecutorConfig& config); \
}

namespace LunarDB::Astral::Implementation {

using Executor = void(*)(const Moonlight::API::ParsedQuery&, const Astral::API::QueryExecutorConfig&);
using ExecutorBundle = std::pair<QueryData::Primitives::EQueryType, Executor>;

PROVIDE_QUERY_EXECUTOR(Create)
PROVIDE_QUERY_EXECUTOR(Drop)
PROVIDE_QUERY_EXECUTOR(Migrate)
PROVIDE_QUERY_EXECUTOR(Truncate)
PROVIDE_QUERY_EXECUTOR(Rename)
PROVIDE_QUERY_EXECUTOR(Select)
PROVIDE_QUERY_EXECUTOR(Insert)
PROVIDE_QUERY_EXECUTOR(Update)
PROVIDE_QUERY_EXECUTOR(Delete)
PROVIDE_QUERY_EXECUTOR(Lock)
PROVIDE_QUERY_EXECUTOR(Grant)
PROVIDE_QUERY_EXECUTOR(Revoke)
PROVIDE_QUERY_EXECUTOR(Commit)
PROVIDE_QUERY_EXECUTOR(Rollback)
PROVIDE_QUERY_EXECUTOR(SavePoint)
PROVIDE_QUERY_EXECUTOR(Index)
PROVIDE_QUERY_EXECUTOR(Database)
PROVIDE_QUERY_EXECUTOR(View)
PROVIDE_QUERY_EXECUTOR(Rebind)
PROVIDE_QUERY_EXECUTOR(Schema)

} // namespace LunarDB::Astral::Implementation
