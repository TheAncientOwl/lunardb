#include "LunarDB/Selenity/SystemCatalog.hpp"

namespace LunarDB::Selenity::API {

LUNAR_SINGLETON_INIT_IMPL(SystemCatalog)
{
    loadConfiguration();
}

SystemCatalog::~SystemCatalog()
{
    saveConfigs();
}

std::filesystem::path SystemCatalog::getLunarHomePath() const
{
    // TODO: Get path from config.
    // !NOTE: Not windows compatible? config path should fix this
    std::filesystem::path const c_lunar_home{"/tmp/lunardb"};
    if (!std::filesystem::exists(c_lunar_home))
    {
        std::filesystem::create_directories(c_lunar_home);
    }
    return c_lunar_home;
}

std::filesystem::path SystemCatalog::getHomePath() const
{
    auto const c_data_home_path{getLunarHomePath() / "databases"};
    if (!std::filesystem::exists(c_data_home_path))
    {
        std::filesystem::create_directories(c_data_home_path);
    }
    return c_data_home_path;
}

std::filesystem::path SystemCatalog::getDataHomePath() const
{
    return getHomePath();
}

std::filesystem::path SystemCatalog::getCatalogFilePath() const
{
    return getHomePath() / "system_catalog.ldb";
}

void SystemCatalog::loadConfiguration()
{
    m_database_in_use = std::nullopt;
    loadConfigs();
}

void SystemCatalog::createDatabase(std::string const& name)
{
    // TODO: WriteAheadLog
    if (m_catalog.name_to_config.contains(name))
    {
        throw std::runtime_error("Database already exists");
    }

    auto catalog_entry_ptr =
        m_catalog.name_to_config
            .emplace(
                name,
                std::make_shared<Managers::Configurations::DatabaseConfiguration>(
                    name, getDataHomePath() / name, Common::CppExtensions::UniqueID::generate()))
            .first->second;
    std::filesystem::create_directories(catalog_entry_ptr->home);

    auto const uid{catalog_entry_ptr->uid};
    std::ignore = m_catalog.id_to_manager.emplace(
        uid, std::make_shared<Managers::DatabaseManager>(catalog_entry_ptr));

    saveConfigs();
}

void SystemCatalog::dropDatabase(std::string const& name)
{
    // TODO: WriteAheadLog
    auto const catalog_entry_it{m_catalog.name_to_config.find(name)};
    if (catalog_entry_it == m_catalog.name_to_config.end())
    {
        throw std::runtime_error("Database does not exist");
    }

    if (static_cast<bool>(m_database_in_use) && m_database_in_use->name == name)
    {
        m_database_in_use = std::nullopt;
    }

    std::filesystem::remove_all(catalog_entry_it->second->home);

    m_catalog.id_to_manager.erase(catalog_entry_it->second->uid);
    m_catalog.name_to_config.erase(catalog_entry_it);

    saveConfigs();
}

void SystemCatalog::useDatabase(std::string name)
{
    auto const catalog_entry_it{m_catalog.name_to_config.find(name)};
    if (catalog_entry_it == m_catalog.name_to_config.end())
    {
        throw std::runtime_error("Database does not exist");
    }

    m_database_in_use.emplace(std::move(name), catalog_entry_it->second->uid);
}

bool SystemCatalog::usingDatabase() const
{
    return static_cast<bool>(m_database_in_use);
}

std::shared_ptr<Managers::DatabaseManager> SystemCatalog::getDatabaseInUse()
{
    if (!static_cast<bool>(m_database_in_use))
    {
        throw std::runtime_error("No database in use");
    }

    return m_catalog.id_to_manager.find(m_database_in_use->uid)->second;
}

} // namespace LunarDB::Selenity::API
