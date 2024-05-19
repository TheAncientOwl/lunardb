#include "LunarDB/Selenity/Collections/BaseManager.hpp"

namespace LunarDB::Selenity::Collections {

BaseManager::BaseManager(std::shared_ptr<Implementation::CatalogEntry> catalog_entry)
    : m_catalog_info{std::move(catalog_entry)}
{
}

Common::CppExtensions::UniqueID BaseManager::getUID() const
{
    return m_catalog_info->uid;
}

std::filesystem::path const& BaseManager::getHomePath() const
{
    return m_catalog_info->home;
}

std::string_view BaseManager::getName() const
{
    return m_catalog_info->name;
}

} // namespace LunarDB::Selenity::Collections
