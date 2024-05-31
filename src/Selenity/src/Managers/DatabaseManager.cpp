#include "LunarDB/Selenity/Managers/DatabaseManager.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"

namespace LunarDB::Selenity::API::Managers {

DatabaseManager::DatabaseManager(std::shared_ptr<Configurations::DatabaseConfiguration> config)
    : CatalogManager(config)
{
    loadConfigs();
}

DatabaseManager::~DatabaseManager()
{
    saveConfigs();
}

std::filesystem::path DatabaseManager::getHomePath() const
{
    return m_catalog.config->home;
}

std::filesystem::path DatabaseManager::getDataHomePath() const
{
    auto const c_data_home_path{getHomePath() / "collections"};
    if (!std::filesystem::exists(c_data_home_path))
    {
        std::filesystem::create_directories(c_data_home_path);
    }
    return c_data_home_path;
}

std::filesystem::path DatabaseManager::getCatalogFilePath() const
{
    return getHomePath() / "database_catalog.ldb";
}

Common::CppExtensions::UniqueID const& DatabaseManager::getUID() const
{
    return m_catalog.config->uid;
}

std::string_view DatabaseManager::getName() const
{
    return m_catalog.config->name;
}

void DatabaseManager::createCollection(
    std::string const& name,
    std::string const& schema_name,
    Common::QueryData::Primitives::EStructureType type,
    std::vector<Common::QueryData::Create::Single::Binding> const& bindings)
{
    // TODO: WriteAheadLog
    if (m_catalog.name_to_config.contains(name))
    {
        throw std::runtime_error("Collection already exists");
    }

    auto catalog_entry_ptr = m_catalog.name_to_config
                                 .emplace(
                                     name,
                                     std::make_shared<Configurations::CollectionConfiguration>(
                                         name,
                                         getDataHomePath() / name,
                                         Common::CppExtensions::UniqueID::generate(),
                                         type,
                                         schema_name,
                                         bindings))
                                 .first->second;
    std::filesystem::create_directories(catalog_entry_ptr->home);

    auto uid{catalog_entry_ptr->uid};
    std::ignore = m_catalog.id_to_manager.emplace(
        std::move(uid), Collections::AbstractManager::Factory::create(catalog_entry_ptr));

    saveConfigs();
}

void DatabaseManager::dropCollection(std::string const& name)
{
    // TODO: WriteAheadLog
    auto const catalog_entry_it{m_catalog.name_to_config.find(name)};
    if (catalog_entry_it == m_catalog.name_to_config.end())
    {
        throw std::runtime_error("Collection does not exist");
    }

    std::filesystem::remove_all(catalog_entry_it->second->home);

    m_catalog.id_to_manager.erase(catalog_entry_it->second->uid);
    m_catalog.name_to_config.erase(catalog_entry_it);

    saveConfigs();
}

std::shared_ptr<Collections::AbstractManager> DatabaseManager::getCollection(std::string const& name)
{
    auto const catalog_entry_it = m_catalog.name_to_config.find(name);
    if (catalog_entry_it == m_catalog.name_to_config.end())
    {
        throw std::runtime_error("Collection does not exist");
    }

    assert(
        m_catalog.name_to_config.size() == m_catalog.id_to_manager.size() &&
        "Collection sizes differ, some data was lost");

    auto const manager_it = m_catalog.id_to_manager.find(catalog_entry_it->second->uid);

    assert(manager_it != m_catalog.id_to_manager.end() && "Collection manager not found");

    return manager_it->second;
}

} // namespace LunarDB::Selenity::API::Managers
