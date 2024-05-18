#include <algorithm>
#include <array>

#include "LunarDB/Common/CppExtensions/ItemArray.hpp"
#include "QueryExecutor.hpp"
#include "QueryExecutors.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)

namespace LunarDB::Astral::API {

void executeQuery(Moonlight::API::ParsedQuery const& parsed_query)
{
    CLOG_VERBOSE(
        "Executing query: ",
        LunarDB::Common::QueryData::Primitives::QueryType::toString(parsed_query.type()));

    namespace DataStructures = LunarDB::Common::CppExtensions::DataStructures;

    static const DataStructures::ItemArray<Implementation::ExecutorBundle, 20> s_executors{
        Implementation::Create::makeExecutor(),
        Implementation::Drop::makeExecutor(),
        Implementation::Migrate::makeExecutor(),
        Implementation::Truncate::makeExecutor(),
        Implementation::Rename::makeExecutor(),
        Implementation::Select::makeExecutor(),
        Implementation::Insert::makeExecutor(),
        Implementation::Update::makeExecutor(),
        Implementation::Delete::makeExecutor(),
        Implementation::Grant::makeExecutor(),
        Implementation::Revoke::makeExecutor(),
        Implementation::Commit::makeExecutor(),
        Implementation::Rollback::makeExecutor(),
        Implementation::SavePoint::makeExecutor(),
        Implementation::Database::makeExecutor(),
        Implementation::Rebind::makeExecutor(),
        Implementation::Schema::makeExecutor()};

    auto const executor_opt =
        s_executors.find_if([&parsed_query](Implementation::ExecutorBundle const& query_executor) {
            return parsed_query.type() == query_executor.first;
        });

    if (static_cast<bool>(executor_opt))
    {
        executor_opt.value()(parsed_query);
        CLOG_VERBOSE(
            LunarDB::Common::QueryData::Primitives::QueryType::toString(parsed_query.type()),
            "Query executed successfully");
    }
    else
    {
        CLOG_CRITICAL("Unknown query type: ", static_cast<std::uint64_t>(parsed_query.type()));
        // TODO: Add throw statement...
    }
}

} // namespace LunarDB::Astral::API

#define PROVIDE_EXECUTOR_BUNDLER(Specialization)                                                 \
    ExecutorBundle Specialization::makeExecutor()                                                \
    {                                                                                            \
        return std::make_pair(                                                                   \
            Common::QueryData::Primitives::EQueryType::Specialization, Specialization::execute); \
    }

namespace LunarDB::Astral::Implementation {

PROVIDE_EXECUTOR_BUNDLER(Create)
PROVIDE_EXECUTOR_BUNDLER(Drop)
PROVIDE_EXECUTOR_BUNDLER(Migrate)
PROVIDE_EXECUTOR_BUNDLER(Truncate)
PROVIDE_EXECUTOR_BUNDLER(Rename)
PROVIDE_EXECUTOR_BUNDLER(Select)
PROVIDE_EXECUTOR_BUNDLER(Insert)
PROVIDE_EXECUTOR_BUNDLER(Update)
PROVIDE_EXECUTOR_BUNDLER(Delete)
PROVIDE_EXECUTOR_BUNDLER(Grant)
PROVIDE_EXECUTOR_BUNDLER(Revoke)
PROVIDE_EXECUTOR_BUNDLER(Commit)
PROVIDE_EXECUTOR_BUNDLER(Rollback)
PROVIDE_EXECUTOR_BUNDLER(SavePoint)
PROVIDE_EXECUTOR_BUNDLER(Database)
PROVIDE_EXECUTOR_BUNDLER(Rebind)
PROVIDE_EXECUTOR_BUNDLER(Schema)

} // namespace LunarDB::Astral::Implementation
