#include "QueryExecutors.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)

namespace LunarDB::Astral::Implementation {

void Delete::execute(Moonlight::API::ParsedQuery const& parsed_query)
{
    CLOG_VERBOSE("Executing 'delete' query");

    // TODO: Provide implementation
    auto const& query = parsed_query.get<Common::QueryData::Delete>();
}

} // namespace LunarDB::Astral::Implementation
