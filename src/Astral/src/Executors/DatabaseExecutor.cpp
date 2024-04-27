#include "QueryExecutors.hpp"
namespace LunarDB::Astral::Implementation {

namespace {

} // namespace

void Database::execute(
    Moonlight::API::ParsedQuery const& parsed_query,
    Astral::API::SelenityDependencies const& config)
{
    auto const& query = parsed_query.get<QueryData::Database>();

    switch (query.operation_type)
    {
    case QueryData::Primitives::EDatabaseOperationType::Create:
        config.db_catalog.createDatabase(query.name);
        config.db_catalog.saveToDisk();
        break;
    case QueryData::Primitives::EDatabaseOperationType::Drop:
        config.db_catalog.dropDatabase(query.name);
        config.db_catalog.saveToDisk();
        break;
    case QueryData::Primitives::EDatabaseOperationType::Use:
        config.db_catalog.useDatabase(query.name);
        break;
    case QueryData::Primitives::EDatabaseOperationType::Backup:
        // TODO: Provide implementation
        throw std::runtime_error{"Not implemented yet..."};
    default:
        throw std::logic_error{"Cannot execute unknown query operation"};
    }
}

} // namespace LunarDB::Astral::Implementation
