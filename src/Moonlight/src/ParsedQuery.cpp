#include "QueryData.hpp"
#include "ParsedQuery.hpp"
#include "HierarchySet.hpp"
#include "IQueryParsers.hpp"
#include "Utils.hpp"

#define MAP_QUERY_DATA_TO_TYPE(Entry) \
template<> const EQueryType \
ParsedQuery::QueryDataToTypeMap<QueryData::Entry>::value = EQueryType::Entry;

namespace LunarDB::Moonlight::API {

ParsedQuery ParsedQuery::from(std::string_view query)
{
    using namespace Implementation;

    static const HierarchySet<IQueryParser, QUERY_PARSERS> s_parsers{};

    Utils::trim(query);
    const auto parser_ptr = s_parsers.findIf([query](const auto& parser) -> bool {
        return Utils::startsWithIgnoreCase(query, parser.queryPrefix());
        });

    if (!parser_ptr)
    {
        throw std::runtime_error("Invalid query syntax");
    }

    return parser_ptr->parse(query);
}

EQueryType ParsedQuery::type() const
{
    return m_type;
}

template<typename T>
const EQueryType ParsedQuery::QueryDataToTypeMap<T>::value = EQueryType::None;

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

} // namespace LunarDB::Moonlight::API
