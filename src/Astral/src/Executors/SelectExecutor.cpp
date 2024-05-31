#include "QueryExecutors.hpp"

#include "LunarDB/Selenity/SystemCatalog.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)

namespace LunarDB::Astral::Implementation {

void Select::execute(Moonlight::API::ParsedQuery const& parsed_query)
{
    CLOG_VERBOSE("Executing 'select' query");

    auto const& query = parsed_query.get<Common::QueryData::Select>();

    auto& system_catalog{Selenity::API::SystemCatalog::Instance()};
    auto const& database{system_catalog.getDatabaseInUse()};
    system_catalog.setCurrentSelection(database->getCollection(query.from)->select(query));
}

} // namespace LunarDB::Astral::Implementation
