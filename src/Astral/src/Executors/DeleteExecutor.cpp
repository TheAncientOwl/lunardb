#include "LunarDB/Astral/QueryExecutors.hpp"

#include "LunarDB/Selenity/SystemCatalog.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)

namespace LunarDB::Astral::Implementation {

void Delete::execute(Moonlight::API::ParsedQuery const& parsed_query)
{
    CLOG_VERBOSE("Delete::execute()");

    auto const& query = parsed_query.get<Common::QueryData::Delete>();

    Selenity::API::SystemCatalog::Instance()
        .getDatabaseInUse()
        ->getCollection(query.from)
        ->deleteWhere(query.where);
}

} // namespace LunarDB::Astral::Implementation
