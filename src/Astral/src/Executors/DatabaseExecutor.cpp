#include "QueryExecutors.hpp"

#include "LunarDB/Selenity/SystemCatalog.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)
namespace LunarDB::Astral::Implementation {

void Database::execute(Moonlight::API::ParsedQuery const& parsed_query)
{
    CLOG_VERBOSE("Executing 'database' query");

    auto const& query = parsed_query.get<Common::QueryData::Database>();

    auto& system_catalog{Selenity::API::SystemCatalog::Instance()};

    switch (query.operation_type)
    {
    case Common::QueryData::Primitives::EDatabaseOperationType::Create: {
        system_catalog.createDatabase(query.name);
        break;
    }
    case Common::QueryData::Primitives::EDatabaseOperationType::Drop: {
        system_catalog.dropDatabase(query.name);
        break;
    }
    case Common::QueryData::Primitives::EDatabaseOperationType::Use: {
        system_catalog.useDatabase(query.name);
        break;
    }
    case Common::QueryData::Primitives::EDatabaseOperationType::Backup: {
        // TODO: Provide implementation
        throw std::runtime_error{
            "[~/lunardb/src/Astral/src/Executors/DatabaseExecutor.cpp:backup] Not implemented "
            "yet..."};
    }
    default:
        throw std::logic_error{"Cannot execute unknown query operation"};
    }
}

} // namespace LunarDB::Astral::Implementation
