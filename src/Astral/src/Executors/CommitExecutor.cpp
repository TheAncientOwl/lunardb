#include "LunarDB/Astral/QueryExecutors.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)

namespace LunarDB::Astral::Implementation {

void Commit::execute(Moonlight::API::ParsedQuery const& parsed_query)
{
    CLOG_VERBOSE("Commit::execute()");

    // TODO: Provide implementation
    auto const& query = parsed_query.get<Common::QueryData::Commit>();
}

} // namespace LunarDB::Astral::Implementation
