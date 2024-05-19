#pragma once

#include <filesystem>
#include <iostream>

#include "LunarDB/Common/CppExtensions/BinaryIO.hpp"
#include "LunarDB/Common/CppExtensions/EncapsulationHelpers.hpp"
#include "LunarDB/Common/CppExtensions/UniqueID.hpp"

namespace LunarDB::Selenity::Implementation::SystemCatalog {

class DatabaseManager
{
public: // life cycle
    DatabaseManager(std::filesystem::path home_path, std::string name);
    LUNAR_PROVIDE_DEFAULT_LIFE_CYCLE_OF(DatabaseManager);

public: // public API
    Common::CppExtensions::Types::UniqueID getCollectionUID(std::string const& collection_name) const;
    Common::CppExtensions::Types::UniqueID getUID() const;

    void createCollection(std::string name);

public: // basic encapsulation
    LUNAR_PROVIDE_REF_GET_SET(home_path, HomePath);
    LUNAR_PROVIDE_REF_GET_SET(name, Name);
    LUNAR_PROVIDE_DEFAULT_EQUALITY_CHECK(DatabaseManager);

private: // binary IO
    LUNAR_ENABLE_BINARY_IO(m_uid, m_home_path, m_name);

private: // fields
    Common::CppExtensions::Types::UniqueID m_uid;
    std::filesystem::path m_home_path;
    std::string m_name;
};

} // namespace LunarDB::Selenity::Implementation::SystemCatalog
