#include "LunarDB/Selenity/Managers/Collections/TableManager.hpp"

namespace LunarDB::Selenity::API::Managers::Collections {

TableManager::TableManager(std::shared_ptr<Configurations::CollectionConfiguration> config)
    : AbstractManager(config)
{
}

void TableManager::insert(std::vector<Common::QueryData::Insert::Object> const& objects)
{
    // TODO: Provide implementation
    throw std::runtime_error{
        "[~/lunardb/src/Selenity/src/Managers/Collections/TableManager.cpp:insert] Not implemented "
        "yet..."};
}

} // namespace LunarDB::Selenity::API::Managers::Collections
