#include "QueryExecutors.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)

namespace LunarDB::Astral::Implementation {

namespace name {

} // namespace name

void Grant::execute(Moonlight::API::ParsedQuery const& parsed_query)
{
    CLOG_VERBOSE("Executing 'grant' query");

    // TODO: Provide implementation
    auto const& query = parsed_query.get<Common::QueryData::Grant>();
}

} // namespace LunarDB::Astral::Implementation
