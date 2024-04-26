#pragma once

#include <filesystem>
#include <iostream>

#include "Common/CppExtensions/BinaryIO.hpp"
#include "Common/CppExtensions/EncapsulationHelpers.hpp"

namespace LunarDB::Selenity::Implementation::SystemCatalog {

class DatabaseConfig
{
public: // life cycle
    DatabaseConfig(std::filesystem::path storage_path, std::string name);
    LUNAR_PROVIDE_DEFAULT_LIFE_CYCLE_OF(DatabaseConfig);

public: // basic encapsulation
    LUNAR_PROVIDE_REF_WINDOW(storage_path, StoragePath);
    LUNAR_PROVIDE_REF_WINDOW(name, Name);
    LUNAR_PROVIDE_DEFAULT_EQUALITY_CHECK(DatabaseConfig);

private: // binary IO
    LUNAR_ENABLE_BINARY_IO(m_storage_path, m_name);

private: // fields
    std::filesystem::path m_storage_path;
    std::string m_name;
};

} // namespace LunarDB::Selenity::Implementation::SystemCatalog
