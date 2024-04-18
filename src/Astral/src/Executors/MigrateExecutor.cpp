#include "QueryExecutors.hpp"

namespace LunarDB::Astral::Implementation {

namespace name {

} // namespace name

void Migrate::execute(Moonlight::API::ParsedQuery const& parsed_query, Astral::API::QueryExecutorConfig const& config)
{
    // TODO: Provide implementation
    auto const& query = parsed_query.get<QueryData::Migrate>();
}

} // namespace LunarDB::Astral::Implementation
