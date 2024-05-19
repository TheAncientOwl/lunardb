#include <fstream>
#include <ranges>
#include <stdexcept>

#include "LunarDB/Selenity/DatabaseManager.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"

namespace LunarDB::Selenity::Implementation {

DatabaseManager::DatabaseManager(std::shared_ptr<CatalogEntry> catalog_entry)
    : m_catalog_info{std::move(catalog_entry)}
{
    loadCatalogFromDisk();
}

Common::CppExtensions::UniqueID DatabaseManager::getUID() const
{
    return m_catalog_info->uid;
}

std::filesystem::path const& DatabaseManager::getHomePath() const
{
    return m_catalog_info->home;
}

std::string_view DatabaseManager::getName() const
{
    return m_catalog_info->name;
}

std::filesystem::path DatabaseManager::getCollectionsHomePath() const
{
    auto const c_collections_home_path{m_catalog_info->home / "collections"};

    if (!std::filesystem::exists(c_collections_home_path))
    {
        std::filesystem::create_directories(c_collections_home_path);
    }

    return c_collections_home_path;
}

std::filesystem::path DatabaseManager::getCollectionsCatalogFilePath() const
{
    return m_catalog_info->home / "catalog.ldb";
}

void DatabaseManager::createCollection(std::string const& collection_name)
{
    // TODO: WriteAheadLog
    if (m_collections_catalog.contains(collection_name))
    {
        throw std::runtime_error("Collection already exists");
    }

    auto catalog_entry_ptr = m_collections_catalog
                                 .emplace(
                                     collection_name,
                                     std::make_shared<Implementation::CatalogEntry>(
                                         collection_name,
                                         Common::CppExtensions::UniqueID::generate(),
                                         getCollectionsHomePath() / collection_name))
                                 .first->second;

    std::filesystem::create_directories(catalog_entry_ptr->home);

    auto uid{catalog_entry_ptr->uid};
    std::ignore = m_collection_managers.emplace(
        uid, std::make_shared<Collections::BaseManager>(std::move(catalog_entry_ptr)));

    saveCatalogToDisk();
}

void DatabaseManager::dropCollection(std::string const& collection_name)
{
    // TODO: WriteAheadLog
    auto const catalog_entry_it = m_collections_catalog.find(collection_name);
    if (catalog_entry_it == m_collections_catalog.end())
    {
        throw std::runtime_error("Collection does not exist");
    }

    std::filesystem::remove_all(catalog_entry_it->second->home);

    m_collection_managers.erase(catalog_entry_it->second->uid);
    m_collections_catalog.erase(catalog_entry_it);

    saveCatalogToDisk();
}

std::shared_ptr<Collections::BaseManager> DatabaseManager::getCollectionManager(
    std::string const& collection_name)
{
    auto const catalog_entry_it = m_collections_catalog.find(collection_name);
    if (catalog_entry_it == m_collections_catalog.end())
    {
        throw std::runtime_error("Collection does not exist");
    }

    return m_collection_managers.find(catalog_entry_it->second->uid)->second;
}

void DatabaseManager::saveCatalogToDisk() const
{
    // TODO: Refactor to write to other file then rename
    std::ofstream catalog_file(getCollectionsCatalogFilePath(), std::ios::trunc | std::ios::binary);
    Common::CppExtensions::BinaryIO::Serializer::serialize(catalog_file, m_collections_catalog.size());
    for (auto const& [name, catalog_entry] : m_collections_catalog)
    {
        Common::CppExtensions::BinaryIO::Serializer::serialize(catalog_file, catalog_entry);
    }
    catalog_file.close();
}

void DatabaseManager::loadCatalogFromDisk()
{
    m_collections_catalog.clear();
    m_collection_managers.clear();

    std::ifstream catalog_file(getCollectionsCatalogFilePath(), std::ios::binary);

    if (catalog_file.is_open())
    {
        decltype(m_collections_catalog)::size_type size{0};
        Common::CppExtensions::BinaryIO::Deserializer::deserialize(catalog_file, size);
        m_collections_catalog.reserve(size);
        m_collection_managers.reserve(size);

        for (auto const _ : std::ranges::iota_view(0u, size))
        {
            auto entry = std::make_shared<Implementation::CatalogEntry>();
            Common::CppExtensions::BinaryIO::Deserializer::deserialize(catalog_file, entry);

            auto name{entry->name};
            auto entry_ptr =
                m_collections_catalog.emplace(std::move(name), std::move(entry)).first->second;
        }
    }
    else
    {
        // TODO: log warning
    }
}

} // namespace LunarDB::Selenity::Implementation
