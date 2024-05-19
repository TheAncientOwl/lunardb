#pragma once

#include <filesystem>
#include <memory>
#include <optional>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "LunarDB/Common/CppExtensions/BinaryIO.hpp"
#include "LunarDB/Common/CppExtensions/Singleton.hpp"
#include "LunarDB/Selenity/CatalogEntry.hpp"
#include "LunarDB/Selenity/DatabaseManager.hpp"

namespace LunarDB::Selenity::API {

class SystemCatalog : public Common::CppExtensions::DesignPatterns::Singleton<SystemCatalog>
{
public: // public API
    ///
    /// @brief Self explanatory
    /// @return LunarDB home path
    ///
    std::filesystem::path getLunarHomePath() const;

    ///
    /// @brief Create database config, store it to internal configs and save configuration to disk
    /// @param [in] name -> database name
    /// @throws std::runtime_error if such database config already exists
    ///
    void createDatabase(std::string const& name);

    ///
    /// @brief Remove database config from internal ocnfigs and save configuration to disk
    /// @param [in] name -> database name
    /// @throws std::runtime_error if such database config does not exist
    ///
    void dropDatabase(std::string const& name);

    ///
    /// @brief Choose which database config will be used as work database
    /// @param [in] name -> database name
    /// @throws std::runtime_error if such database config does not exist
    ///
    void useDatabase(std::string name);

    ///
    /// @brief Self explanatory
    /// @throw std::runtime_error if no database in use
    ///
    std::shared_ptr<Implementation::DatabaseManager> getDatabaseInUse();

    ///
    /// @return true if any database is used as work database
    ///
    bool usingDatabase() const;

public: // lifecycle
    ///
    /// @brief Self explanatory
    /// @note Save data to disk
    ///
    ~SystemCatalog();

private: // singleton
    LUNAR_SINGLETON_INIT(SystemCatalog);

private: // private API
    void saveCatalogToDisk() const;
    void loadCatalogFromDisk();

    std::filesystem::path getDatabasesHomePath() const;
    std::filesystem::path getDatabasesCatalogFilePath() const;

private: // fields
    // map db name -> db catalog entry
    std::unordered_map<std::string, std::shared_ptr<Implementation::CatalogEntry>> m_databases_catalog{};

    // map database uid -> database manager
    Common::CppExtensions::UniqueID::MapTo<std::shared_ptr<Implementation::DatabaseManager>>
        m_database_managers{};

    struct DatabaseInUse
    {
        std::string name;
        Common::CppExtensions::UniqueID uid;
    };
    std::optional<DatabaseInUse> m_database_in_use{std::nullopt};
};

} // namespace LunarDB::Selenity::API
