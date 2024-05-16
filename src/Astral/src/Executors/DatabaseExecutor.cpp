#include "QueryExecutors.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)
namespace LunarDB::Astral::Implementation {

namespace {

} // namespace

void Database::execute(
    Moonlight::API::ParsedQuery const& parsed_query,
    Astral::API::SelenityDependencies const& config)
{
    CLOG_VERBOSE("Executing 'database' query");

    auto const& query = parsed_query.get<Common::QueryData::Database>();

    switch (query.operation_type)
    {
    case Common::QueryData::Primitives::EDatabaseOperationType::Create:
        config.db_catalog.createDatabase(query.name);
        config.db_catalog.saveToDisk();
        break;
    case Common::QueryData::Primitives::EDatabaseOperationType::Drop:
        config.db_catalog.dropDatabase(query.name);
        config.db_catalog.saveToDisk();
        break;
    case Common::QueryData::Primitives::EDatabaseOperationType::Use:
        config.db_catalog.useDatabase(query.name);
        break;
    case Common::QueryData::Primitives::EDatabaseOperationType::Backup:
        // TODO: Provide implementation
        throw std::runtime_error{"Not implemented yet..."};
    default:
        throw std::logic_error{"Cannot execute unknown query operation"};
    }
}

} // namespace LunarDB::Astral::Implementation
