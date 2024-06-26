#include "LunarDB/Astral/QueryExecutors.hpp"
#include "LunarDB/Crescentum/Logger.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"

LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)

namespace LunarDB::Astral::Implementation {

void Insert::execute(Moonlight::API::ParsedQuery const& parsed_query)
{
    CLOG_VERBOSE("Insert::execute()");

    auto const& query = parsed_query.get<Common::QueryData::Insert>();

    Selenity::API::SystemCatalog::Instance()
        .getDatabaseInUse()
        ->getCollection(query.into)
        ->insert(query.objects);
}

} // namespace LunarDB::Astral::Implementation
