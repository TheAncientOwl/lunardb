#include "QueryExecutors.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)

namespace LunarDB::Astral::Implementation {

namespace name {

} // namespace name

void Schema::execute(Moonlight::API::ParsedQuery const& parsed_query)
{
    CLOG_VERBOSE("Executing 'schema' query");

    // TODO: Provide implementation
    auto const& query = parsed_query.get<Common::QueryData::Schema>();
}

} // namespace LunarDB::Astral::Implementation
