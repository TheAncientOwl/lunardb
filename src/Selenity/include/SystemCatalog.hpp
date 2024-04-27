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
    void createDatabase(std::string name);
    void dropDatabase(std::string_view name);
    void useDatabase(std::string_view name);
    bool usingDatabase() const;

    void saveToDisk() const;
    void loadFromDisk();

public: // basic encapsulation
    LUNAR_PROVIDE_CONST_GETTER(lunar_home);
    LUNAR_PROVIDE_CONST_GETTER(configs);
    LUNAR_PROVIDE_DEFAULT_EQUALITY_CHECK(SystemCatalog);

private: // IO
    LUNAR_ENABLE_BINARY_IO(m_configs);
    friend std::ostream& operator<<(std::ostream&, SystemCatalog const&);

private: // helpers
    auto findDatabaseConfigByName(std::string_view name) const;
    std::filesystem::path getLunarConfigFilePath() const;

private: // fields
    std::filesystem::path m_lunar_home;
    std::vector<Implementation::SystemCatalog::DatabaseConfig> m_configs;

    bool m_config_in_use_index_valid;
    std::size_t m_config_in_use_index;
};

} // namespace LunarDB::Selenity::API
