#include "LunarDB/Astral/QueryExecutors.hpp"
#include "LunarDB/BrightMoon/WriteAheadLogger.hpp"
#include "LunarDB/Crescentum/Logger.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"

LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)

namespace LunarDB::Astral::Implementation {

void Truncate::execute(Moonlight::API::ParsedQuery const& parsed_query)
{
    CLOG_VERBOSE("Truncate::execute()");

    auto const& query = parsed_query.get<Common::QueryData::Truncate>();

    auto database_in_use{LunarDB::Selenity::API::SystemCatalog::Instance().getDatabaseInUse()};

    auto wal_data = LunarDB::BrightMoon::API::Transactions::TruncateTransactionData{};
    wal_data.structure_name = std::string{query.structure_name};
    wal_data.database = database_in_use->getName();
    LunarDB::BrightMoon::API::WriteAheadLogger::Instance().log(wal_data);

    database_in_use->getCollection(query.structure_name)->truncate();
}

} // namespace LunarDB::Astral::Implementation
