#include "QueryExecutors.hpp"

#include "LunarDB/Celestial/UsersCatalog.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)

namespace LunarDB::Astral::Implementation {

void Grant::execute(Moonlight::API::ParsedQuery const& parsed_query)
{
    CLOG_VERBOSE("Executing 'grant' query");
    auto& users_catalog{Celestial::API::UsersCatalog::Instance()};
    auto database_in_use{Selenity::API::SystemCatalog::Instance().getDatabaseInUse()};

    auto const& query = parsed_query.get<Common::QueryData::Grant>();

    auto const user_uid{users_catalog.getUserUID(query.to_user)};
    auto const database_uid{database_in_use->getUID()};
    auto const collection_uid{database_in_use->getCollection(query.structure_name)->getUID()};

    std::for_each(
        query.permissions.begin(),
        query.permissions.end(),
        [&users_catalog, user_uid, database_uid, collection_uid](auto const permission) {
            users_catalog.updatePermission(
                user_uid,
                Celestial::API::Configuration::PermissionUpdate{
                    Celestial::API::Configuration::EPermissionUpdateType::Grant,
                    Celestial::API::Configuration::Permission{
                        permission, database_uid, collection_uid}});
        });
}

} // namespace LunarDB::Astral::Implementation
