#pragma once

#include <filesystem>
#include <iostream>

#include "LunarDB/Common/CppExtensions/BinaryIO.hpp"
#include "LunarDB/Common/CppExtensions/EncapsulationHelpers.hpp"

namespace LunarDB::Selenity::Implementation::SystemCatalog {

class DatabaseCatalog
{
public: // life cycle
    DatabaseCatalog(std::filesystem::path home_path, std::string name);
    LUNAR_PROVIDE_DEFAULT_LIFE_CYCLE_OF(DatabaseCatalog);

public: // basic encapsulation
    LUNAR_PROVIDE_REF_GET_SET(home_path, HomePath);
    LUNAR_PROVIDE_REF_GET_SET(name, Name);
    LUNAR_PROVIDE_DEFAULT_EQUALITY_CHECK(DatabaseCatalog);

private: // binary IO
    LUNAR_ENABLE_BINARY_IO(m_home_path, m_name);

private: // fields
    std::filesystem::path m_home_path;
    std::string m_name;
};

} // namespace LunarDB::Selenity::Implementation::SystemCatalog
