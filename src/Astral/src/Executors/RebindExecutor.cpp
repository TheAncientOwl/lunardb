#include "LunarDB/Astral/QueryExecutors.hpp"

#include "LunarDB/Selenity/SystemCatalog.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)

namespace LunarDB::Astral::Implementation {

void Rebind::execute(Moonlight::API::ParsedQuery const& parsed_query)
{
    CLOG_VERBOSE("Rebind::execute()");

    auto const& query = parsed_query.get<Common::QueryData::Rebind>();

    if (static_cast<bool>(query.clean))
    {
        // TODO: Provide implementation
        // throw std::runtime_error{
        //     "[~/lunardb/src/Astral/src/Executors/RebindExecutor.cpp:clean_rebind] Not implemented
        //     " "yet..."};
    }

    Selenity::API::SystemCatalog::Instance().getDatabaseInUse()->rebind(
        query.structure_name, query.field, query.bind_structure_name);
}

} // namespace LunarDB::Astral::Implementation
