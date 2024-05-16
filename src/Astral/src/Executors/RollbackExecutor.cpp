#include "QueryExecutors.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)

namespace LunarDB::Astral::Implementation {

namespace name {

} // namespace name

void Rollback::execute(
    Moonlight::API::ParsedQuery const& parsed_query,
    Astral::API::SelenityDependencies const& config)
{
    CLOG_VERBOSE("Executing 'rollback' query");

    // TODO: Provide implementation
    auto const& query = parsed_query.get<Common::QueryData::Rollback>();
}

} // namespace LunarDB::Astral::Implementation
