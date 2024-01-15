#include <algorithm>
#include <array>

#include "ParsedQuery.hpp"

#define MAP_QUERY_DATA_TO_TYPE(Entry) \
template<> const QueryData::Primitives::EQueryType \
ParsedQuery::QueryDataToTypeMap<QueryData::Entry>::value = QueryData::Primitives::EQueryType::Entry;

namespace LunarDB::Moonlight::API {

QueryData::Primitives::EQueryType ParsedQuery::type() const
{
    return m_type;
}

template<typename T>
const QueryData::Primitives::EQueryType ParsedQuery::QueryDataToTypeMap<T>::value = QueryData::Primitives::EQueryType::None;

MAP_QUERY_DATA_TO_TYPE(Create)
MAP_QUERY_DATA_TO_TYPE(Drop)
MAP_QUERY_DATA_TO_TYPE(Migrate)
MAP_QUERY_DATA_TO_TYPE(Truncate)
MAP_QUERY_DATA_TO_TYPE(Rename)
MAP_QUERY_DATA_TO_TYPE(Select)
MAP_QUERY_DATA_TO_TYPE(Insert)
MAP_QUERY_DATA_TO_TYPE(Update)
MAP_QUERY_DATA_TO_TYPE(Delete)
MAP_QUERY_DATA_TO_TYPE(Lock)
MAP_QUERY_DATA_TO_TYPE(Grant)
MAP_QUERY_DATA_TO_TYPE(Revoke)
MAP_QUERY_DATA_TO_TYPE(Commit)
MAP_QUERY_DATA_TO_TYPE(Rollback)
MAP_QUERY_DATA_TO_TYPE(SavePoint)
MAP_QUERY_DATA_TO_TYPE(Index)
MAP_QUERY_DATA_TO_TYPE(Database)
MAP_QUERY_DATA_TO_TYPE(View)
MAP_QUERY_DATA_TO_TYPE(Rebind)
MAP_QUERY_DATA_TO_TYPE(Schema)

} // namespace LunarDB::Moonlight::API
