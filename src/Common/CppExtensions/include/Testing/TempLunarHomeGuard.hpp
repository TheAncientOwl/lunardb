#pragma once

#include <filesystem>

#define LUNAR_TESTING_HOME_PATH "/tmp/lunardb"

namespace LunarDB::Common::Testing {

struct TempLunarHomeGuard
{
    TempLunarHomeGuard() { std::filesystem::remove_all(LUNAR_TESTING_HOME_PATH); }
    ~TempLunarHomeGuard() { std::filesystem::remove_all(LUNAR_TESTING_HOME_PATH); }
};

} // namespace LunarDB::Common::Testing
