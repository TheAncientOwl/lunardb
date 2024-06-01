#pragma once

#include <filesystem>

#include "LunarDB/Selenity/SchemasCatalog.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"

#define LUNAR_TESTING_HOME_PATH "/tmp/lunardb"

namespace LunarDB::Common::Testing {

struct LunarTestGuard
{
    LunarTestGuard()
    {
        std::filesystem::remove_all(LUNAR_TESTING_HOME_PATH);
        Selenity::API::SystemCatalog::Instance().loadConfigs();
        Selenity::API::SchemasCatalog::Instance().clearCache();
    }
    ~LunarTestGuard() { std::filesystem::remove_all(LUNAR_TESTING_HOME_PATH); }
};

} // namespace LunarDB::Common::Testing
