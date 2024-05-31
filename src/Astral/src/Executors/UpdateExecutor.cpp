#include "QueryExecutors.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)

namespace LunarDB::Astral::Implementation {

void Update::execute(Moonlight::API::ParsedQuery const& parsed_query)
{
    CLOG_VERBOSE("Executing 'update' query");

    // TODO: Provide implementation
    auto const& query = parsed_query.get<Common::QueryData::Update>();
}

} // namespace LunarDB::Astral::Implementation
