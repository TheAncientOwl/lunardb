#include <algorithm>
#include <array>

#include "LunarDB/Astral/QueryExecutor.hpp"
#include "LunarDB/Astral/QueryExecutors.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)

namespace LunarDB::Astral::API {

LUNAR_SINGLETON_INIT_IMPL(QueryExecutorsManager)
{
}

void QueryExecutorsManager::addExecutor(Implementation::ExecutorBundle bundle)
{
    m_parsers.emplace(std::move(bundle));
}

void executeQuery(Moonlight::API::ParsedQuery const& parsed_query)
{
    CLOG_VERBOSE(
        "executeQuery(): Executing query ->",
        LunarDB::Common::QueryData::Primitives::QueryType::toString(parsed_query.type()));

    namespace DataStructures = LunarDB::Common::CppExtensions::DataStructures;

    auto const& executors{QueryExecutorsManager::Instance()};

    auto const executor_opt =
        executors.find_if([&parsed_query](Implementation::ExecutorBundle const& query_executor) {
            return parsed_query.type() == query_executor.first;
        });

    if (static_cast<bool>(executor_opt))
    {
        executor_opt.value()(parsed_query);
        CLOG_VERBOSE(
            "executeQuery(): ",
            LunarDB::Common::QueryData::Primitives::QueryType::toString(parsed_query.type()),
            "Query executed successfully");
    }
    else
    {
        CLOG_CRITICAL(
            "parseQuery(): Unknown query type: ", static_cast<std::uint64_t>(parsed_query.type()));
        throw std::runtime_error{"Invalid query type"};
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
PROVIDE_EXECUTOR_BUNDLER(User)
PROVIDE_EXECUTOR_BUNDLER(Auth)

} // namespace LunarDB::Astral::Implementation
