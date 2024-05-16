#include "QueryExecutors.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)

namespace LunarDB::Astral::Implementation {

namespace name {

} // namespace name

void Select::execute(
    Moonlight::API::ParsedQuery const& parsed_query,
    Astral::API::SelenityDependencies const& config)
{
    CLOG_VERBOSE("Executing 'select' query");

    // TODO: Provide implementation
    auto const& query = parsed_query.get<Common::QueryData::Select>();
}

} // namespace LunarDB::Astral::Implementation
