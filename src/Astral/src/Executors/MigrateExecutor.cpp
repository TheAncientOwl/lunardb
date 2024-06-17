#include "LunarDB/Astral/QueryExecutors.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)

namespace LunarDB::Astral::Implementation {

void Migrate::execute(Moonlight::API::ParsedQuery const& parsed_query)
{
    CLOG_VERBOSE("Migrate::execute()");

    // TODO: Provide implementation
    auto const& query = parsed_query.get<Common::QueryData::Migrate>();
}

} // namespace LunarDB::Astral::Implementation
