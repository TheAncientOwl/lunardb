#include "LunarDB/Selenity/Managers/Collections/TableManager.hpp"

namespace LunarDB::Selenity::API::Managers::Collections {

TableManager::TableManager(std::shared_ptr<Configurations::CollectionConfiguration> config)
    : AbstractManager(config)
{
}

} // namespace LunarDB::Selenity::API::Managers::Collections
