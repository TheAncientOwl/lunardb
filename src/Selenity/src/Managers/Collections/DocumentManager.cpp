#include "LunarDB/Selenity/Managers/Collections/DocumentManager.hpp"

namespace LunarDB::Selenity::API::Managers::Collections {

DocumentManager::DocumentManager(std::shared_ptr<Configurations::CollectionConfiguration> config)
    : AbstractManager(config)
{
}

} // namespace LunarDB::Selenity::API::Managers::Collections
