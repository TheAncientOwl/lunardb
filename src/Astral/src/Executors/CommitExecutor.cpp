#include "QueryExecutors.hpp"

namespace LunarDB::Astral::Implementation {

namespace name {

} // namespace name

void Commit::execute(
    Moonlight::API::ParsedQuery const& parsed_query,
    Astral::API::SelenityDependencies const& config)
{
    // TODO: Provide implementation
    auto const& query = parsed_query.get<QueryData::Commit>();
}

} // namespace LunarDB::Astral::Implementation
