#include "QueryExecutors.hpp"

#include "LunarDB/Selenity/SystemCatalog.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)

namespace LunarDB::Astral::Implementation {

void Truncate::execute(Moonlight::API::ParsedQuery const& parsed_query)
{
    CLOG_VERBOSE("Executing 'truncate' query");

    auto const& query = parsed_query.get<Common::QueryData::Truncate>();

    Selenity::API::SystemCatalog::Instance().getDatabaseInUse()->getCollection(query.structure_name)->truncate();
}

} // namespace LunarDB::Astral::Implementation
