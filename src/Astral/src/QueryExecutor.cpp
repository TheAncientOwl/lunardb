#include <algorithm>
#include <array>

#include "QueryExecutor.hpp"
#include "QueryExecutors.hpp"

namespace LunarDB::Astral::API::QueryExecutor {

void executeQuery(const Moonlight::API::ParsedQuery& parsed_query, const Config& config)
{
    using namespace Implementation;

    static const std::array<ExecutorBundle, 20> s_executors{
        Create::makeExecutor(),
        Drop::makeExecutor(),
        Migrate::makeExecutor(),
        Truncate::makeExecutor(),
        Rename::makeExecutor(),
        Select::makeExecutor(),
        Insert::makeExecutor(),
        Update::makeExecutor(),
        Delete::makeExecutor(),
        Lock::makeExecutor(),
        Grant::makeExecutor(),
        Revoke::makeExecutor(),
        Commit::makeExecutor(),
        Rollback::makeExecutor(),
        SavePoint::makeExecutor(),
        Index::makeExecutor(),
        Database::makeExecutor(),
        View::makeExecutor(),
        Rebind::makeExecutor(),
        Schema::makeExecutor()
    };

    const auto executor_ptr = std::find_if(std::begin(s_executors), std::end(s_executors),
        [&parsed_query](const auto& query_executor) {return query_executor.first == parsed_query.type();});

    if (executor_ptr == std::end(s_executors))
    {
        // TODO: Add throw statement...
    }

    executor_ptr->second(parsed_query, config);
}

} // namespace LunarDB::Astral::API::QueryExecutor
