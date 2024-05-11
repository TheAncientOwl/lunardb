#pragma once

#include "LunarDB/Astral/SelenityDependencies.hpp"
#include "LunarDB/Moonlight/ParsedQuery.hpp"

///
/// @brief Provide makeExecutor() and execute(query, deps) signatures under Specialization namespace.
///
#define PROVIDE_QUERY_EXECUTOR(Specialization)           \
    namespace Specialization {                           \
    [[nodiscard]] ExecutorBundle makeExecutor();         \
    void execute(                                        \
        Moonlight::API::ParsedQuery const& parsed_query, \
        Astral::API::SelenityDependencies const& deps);  \
    }

namespace LunarDB::Astral::Implementation {

using Executor = void (*)(Moonlight::API::ParsedQuery const&, Astral::API::SelenityDependencies const&);
using ExecutorBundle = std::pair<Common::QueryData::Primitives::EQueryType, Executor>;

PROVIDE_QUERY_EXECUTOR(Create)
PROVIDE_QUERY_EXECUTOR(Drop)
PROVIDE_QUERY_EXECUTOR(Migrate)
PROVIDE_QUERY_EXECUTOR(Truncate)
PROVIDE_QUERY_EXECUTOR(Rename)
PROVIDE_QUERY_EXECUTOR(Select)
PROVIDE_QUERY_EXECUTOR(Insert)
PROVIDE_QUERY_EXECUTOR(Update)
PROVIDE_QUERY_EXECUTOR(Delete)
PROVIDE_QUERY_EXECUTOR(Grant)
PROVIDE_QUERY_EXECUTOR(Revoke)
PROVIDE_QUERY_EXECUTOR(Commit)
PROVIDE_QUERY_EXECUTOR(Rollback)
PROVIDE_QUERY_EXECUTOR(SavePoint)
PROVIDE_QUERY_EXECUTOR(Database)
PROVIDE_QUERY_EXECUTOR(Rebind)
PROVIDE_QUERY_EXECUTOR(Schema)

} // namespace LunarDB::Astral::Implementation
