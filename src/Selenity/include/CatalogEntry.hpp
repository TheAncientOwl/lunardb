#pragma once

#include <filesystem>
#include <string>

#include "LunarDB/Common/CppExtensions/UniqueID.hpp"

namespace LunarDB::Selenity::Implementation {

struct CatalogEntry
{
    std::string name;
    Common::CppExtensions::UniqueID uid;
    std::filesystem::path home;

    LUNAR_ENABLE_BINARY_IO(name, uid, home);
};

} // namespace LunarDB::Selenity::Implementation
