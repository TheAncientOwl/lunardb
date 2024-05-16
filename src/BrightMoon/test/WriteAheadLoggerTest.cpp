#include <gtest/gtest.h>

#include "LunarDB/BrightMoon/WriteAheadLogger.hpp"

namespace LunarDB::BrightMoon::Tests {

TEST(BrightMoon_WriteAheadLoggerTest, init)
{
    LunarDB::BrightMoon::API::WriteAheadLogger::Instance().onNaturalSystemExit();
}

} // namespace LunarDB::BrightMoon::Tests
