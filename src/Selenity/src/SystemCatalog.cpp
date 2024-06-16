#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <string_view>

#include "LunarDB/Common/CppExtensions/StringUtils.hpp"
#include "LunarDB/Common/CppExtensions/Testing/LunarTestGuard.hpp"
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
#ifdef LUNAR_ENABLE_TESTING
    std::filesystem::path lunar_home_path{LUNAR_TESTING_HOME_PATH};
#else
    auto const& lunar_home_path{m_config.home_path};
#endif

    if (!lunar_home_path.empty() && !std::filesystem::exists(lunar_home_path))
    {
        std::filesystem::create_directories(lunar_home_path);
    }

    return lunar_home_path;
}

std::filesystem::path SystemCatalog::getHomePath() const
{
    auto const c_data_home_path{getLunarHomePath() / "databases"};
    if (!m_config.home_path.empty() && !std::filesystem::exists(c_data_home_path))
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
    loadSystemConfiguration();
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

std::vector<std::unique_ptr<Managers::Collections::AbstractManager::ICollectionEntry>> const& SystemCatalog::
    getCurrentSelection() const
{
    return m_current_selection;
}

std::vector<std::unique_ptr<Managers::Collections::AbstractManager::ICollectionEntry>>&& SystemCatalog::extractCurrentSelection()
{
    return std::move(m_current_selection);
}

void SystemCatalog::setCurrentSelection(
    std::vector<std::unique_ptr<Managers::Collections::AbstractManager::ICollectionEntry>> selection)
{
    m_current_selection = std::move(selection);
}

void SystemCatalog::clearCurrentSelection()
{
    m_current_selection.clear();
}

void SystemCatalog::loadSystemConfiguration()
{
    auto const config_file_path{std::filesystem::current_path() / "lunardb.config.json"};
    if (!std::filesystem::exists(config_file_path))
    {
        m_config = Config{};
        m_config.home_path = std::filesystem::current_path() / "lunardb";

        if (!std::filesystem::exists(m_config.home_path))
        {
            std::filesystem::create_directories(m_config.home_path);
        }

        nlohmann::json config{};

        config["home_path"] = m_config.home_path;

        std::ofstream config_file(config_file_path);
        if (config_file.is_open())
        {
            config_file << config.dump(4);
            config_file.close();
        }
        else
        {
            // TODO: Log error
        }
    }
    else
    {
        std::ifstream config_file(config_file_path);
        if (config_file.is_open())
        {
            nlohmann::json config{};
            config_file >> config;
            config_file.close();

            auto const get_value_if_existing =
                [&config, &config_file_path](std::string_view key) -> std::string {
                if (config.contains(key))
                {
                    return config[key];
                }
                else
                {
                    throw std::runtime_error{Common::CppExtensions::StringUtils::stringify(
                        "\"", key, "\" key does not exist in ", config_file_path)};
                }
            };

            m_config.home_path = get_value_if_existing("home_path");
        }
        else
        {
            // TODO: Log error
        }
    }
}

} // namespace LunarDB::Selenity::API
