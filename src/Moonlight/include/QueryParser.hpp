#pragma once

#include "LunarDB/Common/CppExtensions/DynamicFlatMap.hpp"
#include "LunarDB/Common/CppExtensions/Singleton.hpp"
#include "LunarDB/Moonlight/ParsedQuery.hpp"
#include "LunarDB/Moonlight/QueryParsers.hpp"

namespace LunarDB::Moonlight::API {

class QueryParsersManager
    : public Common::CppExtensions::DesignPatterns::Singleton<QueryParsersManager>
{
public:
    template <typename Callable>
    inline std::optional<Implementation::ParserBundle::second_type> find_if(Callable&& callable) const
    {
        return m_parsers.find_if(std::forward<Callable>(callable));
    }

    void addParser(Implementation::ParserBundle bundle);

private: // singleton
    LUNAR_SINGLETON_INIT(QueryParsersManager);

private: // fields
    Common::CppExtensions::DataStructures::DynamicFlatMap<Implementation::ParserBundle> m_parsers{
        Implementation::Create::makeParser(),
        Implementation::Drop::makeParser(),
        Implementation::Migrate::makeParser(),
        Implementation::Truncate::makeParser(),
        Implementation::Rename::makeParser(),
        Implementation::Select::makeParser(),
        Implementation::Insert::makeParser(),
        Implementation::Update::makeParser(),
        Implementation::Delete::makeParser(),
        Implementation::Grant::makeParser(),
        Implementation::Revoke::makeParser(),
        Implementation::Commit::makeParser(),
        Implementation::Rollback::makeParser(),
        Implementation::SavePoint::makeParser(),
        Implementation::Database::makeParser(),
        Implementation::Rebind::makeParser(),
        Implementation::Schema::makeParser(),
        Implementation::User::makeParser()};
};

///
/// @brief Self explanatory.
/// @param [in] query -> String representation of a query
/// @return @c Moonlight::API::ParsedQuery
///
ParsedQuery parseQuery(std::string_view query);

} // namespace LunarDB::Moonlight::API
