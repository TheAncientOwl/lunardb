#include "LunarDB/Astral/QueryExecutors.hpp"

#include "LunarDB/Selenity/SchemasCatalog.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)

namespace LunarDB::Astral::Implementation {

void Schema::execute(Moonlight::API::ParsedQuery const& parsed_query)
{
    CLOG_VERBOSE("Schema::execute()");

    auto& schemas_catalog{Selenity::API::SchemasCatalog::Instance()};

    auto const& query = parsed_query.get<Common::QueryData::Schema>();

    schemas_catalog.createSchema(query);
}

} // namespace LunarDB::Astral::Implementation
