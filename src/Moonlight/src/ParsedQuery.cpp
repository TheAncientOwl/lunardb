#include <algorithm>

#include "ParsedQuery.hpp"
#include "QueryData.hpp"
#include "QueryParsers.hpp"
#include "Utils.hpp"

#define MAP_QUERY_DATA_TO_TYPE(Entry) \
template<> const EQueryType \
ParsedQuery::QueryDataToTypeMap<QueryData::Entry>::value = EQueryType::Entry;

namespace LunarDB::Moonlight::API {

ParsedQuery ParsedQuery::from(std::string_view query)
{
    using namespace Implementation;

    static const std::array<ParserBundle, 20> s_parsers{
        Create::makeParser(),
        Drop::makeParser(),
        Migrate::makeParser(),
        Truncate::makeParser(),
        Rename::makeParser(),
        Select::makeParser(),
        Insert::makeParser(),
        Update::makeParser(),
        Delete::makeParser(),
        Lock::makeParser(),
        Grant::makeParser(),
        Revoke::makeParser(),
        Commit::makeParser(),
        Rollback::makeParser(),
        SavePoint::makeParser(),
        Index::makeParser(),
        Database::makeParser(),
        View::makeParser(),
        Rebind::makeParser(),
        Schema::makeParser()
    };

    Utils::trim(query);
    const auto parser_ptr = std::find_if(std::begin(s_parsers), std::end(s_parsers),
        [query](const auto& query_parser) { return query_parser.first(query); });

    if (parser_ptr == std::end(s_parsers))
    {
        throw std::runtime_error("Invalid query syntax");
    }

    return parser_ptr->second(query);
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
MAP_QUERY_DATA_TO_TYPE(Schema)

} // namespace LunarDB::Moonlight::API
