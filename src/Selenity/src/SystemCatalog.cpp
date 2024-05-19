#include "LunarDB/Selenity/SystemCatalog.hpp"

#include <algorithm>
#include <fstream>
#include <ranges>

namespace LunarDB::Selenity::API {

LUNAR_SINGLETON_INIT_IMPL(SystemCatalog)
{
    loadCatalogFromDisk();
}

std::filesystem::path SystemCatalog::getLunarHomePath() const
{
    // TODO: Get path from config.
    // !NOTE: This is not windows compatible? config path should fix this.
    std::filesystem::path const c_lunar_home{"/tmp/lunardb"};

    if (!std::filesystem::exists(c_lunar_home))
    {
        std::filesystem::create_directories(c_lunar_home);
    }

    return c_lunar_home;
}

std::filesystem::path SystemCatalog::getDatabasesHomePath() const
{
    auto const c_databases_home_path{getLunarHomePath() / "databases"};

    if (!std::filesystem::exists(c_databases_home_path))
    {
        std::filesystem::create_directories(c_databases_home_path);
    }

    return c_databases_home_path;
}

std::filesystem::path SystemCatalog::getDatabasesCatalogFilePath() const
{
    return getDatabasesHomePath() / "catalog.ldb";
}

void SystemCatalog::saveCatalogToDisk() const
{
    // TODO: Refactor to write to other file then rename
    std::ofstream catalog_file(getDatabasesCatalogFilePath(), std::ios::trunc | std::ios::binary);
    Common::CppExtensions::BinaryIO::Serializer::serialize(catalog_file, m_databases_catalog.size());
    for (auto const& [name, catalog_entry] : m_databases_catalog)
    {
        Common::CppExtensions::BinaryIO::Serializer::serialize(catalog_file, catalog_entry);
    }
    catalog_file.close();
}

void SystemCatalog::loadCatalogFromDisk()
{
    m_databases_catalog.clear();
    m_database_managers.clear();
    m_database_in_use = std::nullopt;

    std::ifstream catalog_file(getDatabasesCatalogFilePath(), std::ios::binary);

    if (catalog_file.is_open())
    {
        decltype(m_databases_catalog)::size_type size{0};
        Common::CppExtensions::BinaryIO::Deserializer::deserialize(catalog_file, size);
        m_databases_catalog.reserve(size);
        m_database_managers.reserve(size);

        for (auto const _ : std::ranges::iota_view(0u, size))
        {
            auto entry = std::make_shared<Implementation::CatalogEntry>();
            Common::CppExtensions::BinaryIO::Deserializer::deserialize(catalog_file, entry);

            auto name{entry->name};
            auto entry_ptr =
                m_databases_catalog.emplace(std::move(name), std::move(entry)).first->second;

            m_database_managers.emplace(
                entry_ptr->uid,
                std::make_shared<Implementation::DatabaseManager>(std::move(entry_ptr)));
        }
    }
    else
    {
        // TODO: log warning
    }
}

void SystemCatalog::createDatabase(std::string const& name)
{
    // TODO: WriteAheadLog
    if (m_databases_catalog.contains(name))
    {
        throw std::runtime_error("Database already exists");
    }

    auto catalog_entry_ptr =
        m_databases_catalog
            .emplace(
                name,
                std::make_shared<Implementation::CatalogEntry>(
                    name, Common::CppExtensions::UniqueID::generate(), getDatabasesHomePath() / name))
            .first->second;

    std::filesystem::create_directories(catalog_entry_ptr->home);

    auto uid{catalog_entry_ptr->uid};
    std::ignore = m_database_managers.emplace(
        uid, std::make_shared<Implementation::DatabaseManager>(std::move(catalog_entry_ptr)));

    saveCatalogToDisk();
}

void SystemCatalog::dropDatabase(std::string const& name)
{
    // TODO: WriteAheadLog
    auto const catalog_entry_it = m_databases_catalog.find(name);
    if (catalog_entry_it == m_databases_catalog.end())
    {
        throw std::runtime_error("Database does not exist");
    }

    if (static_cast<bool>(m_database_in_use) && m_database_in_use->name == name)
    {
        m_database_in_use = std::nullopt;
    }

    std::filesystem::remove_all(catalog_entry_it->second->home);

    m_database_managers.erase(catalog_entry_it->second->uid);
    m_databases_catalog.erase(catalog_entry_it);

    saveCatalogToDisk();
}

void SystemCatalog::useDatabase(std::string name)
{
    auto const catalog_entry_it = m_databases_catalog.find(name);
    if (catalog_entry_it == m_databases_catalog.end())
    {
        throw std::runtime_error("Database does not exist");
    }

    m_database_in_use.emplace(std::move(name), catalog_entry_it->second->uid);
}

bool SystemCatalog::usingDatabase() const
{
    return static_cast<bool>(m_database_in_use);
}

SystemCatalog::~SystemCatalog()
{
    saveCatalogToDisk();
}

std::shared_ptr<Implementation::DatabaseManager> SystemCatalog::getDatabaseInUse()
{
    if (!static_cast<bool>(m_database_in_use))
    {
        throw std::runtime_error{"No database in use"};
    }

    return m_database_managers.find(m_database_in_use->uid)->second;
}

} // namespace LunarDB::Selenity::API
