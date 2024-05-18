#include "QueryExecutors.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)

namespace LunarDB::Astral::Implementation {

namespace name {

} // namespace name

void Insert::execute(Moonlight::API::ParsedQuery const& parsed_query)
{
    CLOG_VERBOSE("Executing 'insert' query");

    // TODO: Provide implementation
    auto const& query = parsed_query.get<Common::QueryData::Insert>();
}

} // namespace LunarDB::Astral::Implementation
