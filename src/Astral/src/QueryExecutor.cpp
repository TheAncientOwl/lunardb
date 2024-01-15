#include <algorithm>
#include <array>

#include "CppExtensions/include/ItemArray.hpp"
#include "QueryExecutor.hpp"
#include "QueryExecutors.hpp"

namespace LunarDB::Astral::API {

void executeQuery(const Moonlight::API::ParsedQuery& parsed_query, const QueryExecutorConfig& config)
{
    using namespace Implementation;
    using namespace CppExtensions;

    static const DataStructures::ItemArray<ExecutorBundle, 20> s_executors{
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

    const auto executor_opt = s_executors.find_if([&parsed_query](const ExecutorBundle& query_executor) {
        return parsed_query.type() == query_executor.first;
        });

    if (static_cast<bool>(executor_opt))
    {
        executor_opt.value()(parsed_query, config);
    }
    else
    {
        // TODO: Add throw statement...
    }
}

} // namespace LunarDB::Astral::API
