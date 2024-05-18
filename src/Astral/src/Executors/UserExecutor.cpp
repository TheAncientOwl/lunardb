#include "QueryExecutors.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)

namespace LunarDB::Astral::Implementation {

namespace name {

} // namespace name

void User::execute(Moonlight::API::ParsedQuery const& parsed_query)
{
    CLOG_VERBOSE("Executing 'user' query");

    // TODO: Provide implementation
    auto const& query = parsed_query.get<Common::QueryData::User>();
}

} // namespace LunarDB::Astral::Implementation
