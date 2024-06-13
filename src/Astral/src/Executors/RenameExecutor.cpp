#include "QueryExecutors.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)

namespace LunarDB::Astral::Implementation {

void Rename::execute(Moonlight::API::ParsedQuery const& parsed_query)
{
    CLOG_VERBOSE("Rename::execute()");

    // TODO: Provide implementation
    auto const& query = parsed_query.get<Common::QueryData::Rename>();
}

} // namespace LunarDB::Astral::Implementation
