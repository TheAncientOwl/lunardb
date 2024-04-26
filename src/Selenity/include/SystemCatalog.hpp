#pragma once

#include <filesystem>
#include <memory>

#include "Common/CppExtensions/BinaryIO.hpp"

namespace LunarDB::Selenity {

class SystemCatalog
{
public: // API
    void createDatabase(std::string_view name);

    void loadFromDisk();
    void saveToDisk() const;

private: // IO
    LUNAR_ENABLE_BINARY_IO(lunar_home);

private: // fields
    std::filesystem::path lunar_home;
};

} // namespace LunarDB::Selenity
