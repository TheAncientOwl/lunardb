#include "LunarDB/Astral/QueryExecutors.hpp"

#include "LunarDB/Celestial/UsersCatalog.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)

namespace LunarDB::Astral::Implementation {

void User::execute(Moonlight::API::ParsedQuery const& parsed_query)
{
    CLOG_VERBOSE("User::execute()");

    auto& users_catalog{Celestial::API::UsersCatalog::Instance()};

    auto const& query = parsed_query.get<Common::QueryData::User>();

    switch (query.action)
    {
    case Common::QueryData::Primitives::EUserActionType::Create: {
        users_catalog.createUser(query.name, *query.password);
        break;
    }
    case Common::QueryData::Primitives::EUserActionType::Remove: {
        auto const user_uid{users_catalog.getUserUID(query.name)};
        users_catalog.removeUser(user_uid);
        break;
    }
    default:
        break;
    }
}

} // namespace LunarDB::Astral::Implementation
