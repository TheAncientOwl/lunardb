#pragma once

#include <filesystem>
#include <vector>

#include "Common/CppExtensions/BinaryIO.hpp"
#include "Selenity/private/SystemCatalog/DatabaseConfig.hpp"

namespace LunarDB::Selenity::API {

class SystemCatalog
{
public: // lifecycle
    SystemCatalog(std::filesystem::path lunar_home);

public: // public API
    ///
    /// @brief Create database config, store it to internal configs and save configuration to disk
    /// @param [in] name -> database name
    /// @throws std::runtime_error if such database config already exists
    ///
    void createDatabase(std::string name);

    ///
    /// @brief Remove database config from internal ocnfigs and save configuration to disk
    /// @param [in] name -> database name
    /// @throws std::runtime_error if such database config does not exist
    ///
    void dropDatabase(std::string_view name);

    ///
    /// @brief Choose which database config will be used as work database
    /// @param [in] name -> database name
    /// @throws std::runtime_error if such database config does not exist
    ///
    void useDatabase(std::string_view name);

    ///
    /// @return true if any database is used as work database
    ///
    bool usingDatabase() const;

    ///
    /// @brief Saves configuration data to disk
    ///
    void saveToDisk() const;

    ///
    /// @brief Loads configuration data to disk
    ///
    void loadFromDisk();

public: // basic encapsulation
    LUNAR_PROVIDE_CONST_GETTER(lunar_home);
    LUNAR_PROVIDE_CONST_GETTER(configs);
    LUNAR_PROVIDE_DEFAULT_EQUALITY_CHECK(SystemCatalog);

private: // IO
    LUNAR_ENABLE_BINARY_IO(m_configs);
    friend std::ostream& operator<<(std::ostream&, SystemCatalog const&);

private: // helpers
    ///
    /// @param [in] name -> config name
    /// @return iterator from m_configs to searched database config name
    ///
    auto findDatabaseConfigByName(std::string_view name) const;

    ///
    /// @brief Self explanatory
    ///
    std::filesystem::path getLunarConfigFilePath() const;

private: // fields
    std::filesystem::path m_lunar_home;
    std::vector<Implementation::SystemCatalog::DatabaseConfig> m_configs;

    bool m_config_in_use_index_valid;
    std::size_t m_config_in_use_index;
};

} // namespace LunarDB::Selenity::API
