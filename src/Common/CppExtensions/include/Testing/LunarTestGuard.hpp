#pragma once

#include <filesystem>

#include "LunarDB/Selenity/SchemasCatalog.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"

#ifdef WIN32
#define LUNAR_TESTING_HOME_PATH "C:/tmp/lunardb"
#else
#define LUNAR_TESTING_HOME_PATH "/tmp/lunardb"
#endif

// #define LUNAR_ENABLE_TESTING

namespace LunarDB::Common::Testing {

struct LunarTestGuard
{
    LunarTestGuard()
    {
        std::filesystem::remove_all(LUNAR_TESTING_HOME_PATH);
        Selenity::API::SystemCatalog::Instance().loadConfigs();
        Selenity::API::SchemasCatalog::Instance().clearCache();
    }
};

} // namespace LunarDB::Common::Testing
