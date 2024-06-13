#include "QueryExecutors.hpp"

#include "LunarDB/Selenity/SystemCatalog.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)

namespace LunarDB::Astral::Implementation {

void Update::execute(Moonlight::API::ParsedQuery const& parsed_query)
{
    CLOG_VERBOSE("Update::execute()");

    auto const& query = parsed_query.get<Common::QueryData::Update>();

    Selenity::API::SystemCatalog::Instance()
        .getDatabaseInUse()
        ->getCollection(query.structure_name)
        ->update(query);
}

} // namespace LunarDB::Astral::Implementation
