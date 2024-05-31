#include "QueryExecutors.hpp"

#include "LunarDB/Selenity/SystemCatalog.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)

namespace LunarDB::Astral::Implementation {

namespace name {

} // namespace name

void Drop::execute(Moonlight::API::ParsedQuery const& parsed_query)
{
    CLOG_VERBOSE("Executing 'drop' query");

    // TODO: Provide implementation
    auto const& query = parsed_query.get<Common::QueryData::Drop>();

    if (query.cascade)
    {
        // TODO: Provide implementation
        throw std::runtime_error{
            "[~/lunardb/src/Astral/src/Executors/DropExecutor.cpp:execute::cascade] Not "
            "implemented yet..."};
    }

    Selenity::API::SystemCatalog::Instance().getDatabaseInUse()->dropCollection(query.structure_name);
}

} // namespace LunarDB::Astral::Implementation
