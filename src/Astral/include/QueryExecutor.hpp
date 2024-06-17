#pragma once

#include "LunarDB/Astral/QueryExecutors.hpp"
#include "LunarDB/Common/CppExtensions/DynamicFlatMap.hpp"
#include "LunarDB/Common/CppExtensions/Singleton.hpp"
#include "LunarDB/Moonlight/ParsedQuery.hpp"

namespace LunarDB::Astral::API {

class QueryExecutorsManager
    : public Common::CppExtensions::DesignPatterns::Singleton<QueryExecutorsManager>
{
public:
    template <typename Callable>
    inline std::optional<Implementation::ExecutorBundle::second_type> find_if(Callable&& callable) const
    {
        return m_parsers.find_if(std::forward<Callable>(callable));
    }

    void addExecutor(Implementation::ExecutorBundle bundle);

private: // singleton
    LUNAR_SINGLETON_INIT(QueryExecutorsManager);

private: // fields
    Common::CppExtensions::DataStructures::DynamicFlatMap<Implementation::ExecutorBundle> m_parsers{
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
        Implementation::Schema::makeExecutor(),
        Implementation::User::makeExecutor()};
};

///
/// @brief Executes parsed query
/// @param [in] parsed_query
/// @param [in] config
///
void executeQuery(Moonlight::API::ParsedQuery const& parsed_query);

} // namespace LunarDB::Astral::API
