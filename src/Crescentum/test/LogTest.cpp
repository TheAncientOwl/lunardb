#include <gtest/gtest.h>

#include "LunarDB/Crescentum/Logger.hpp"

#include <filesystem>

LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL);

namespace LunarDB::Crescentum::API::Tests {

TEST(Crescentum_LogTest, log)
{
    using namespace std::chrono_literals;

    CLOG_CRITICAL("message1=", 232321, "message2=", 101011010101);
    CLOG_ERROR("message1=", 232321, "message2=", 101011010101);
    CLOG_WARN("message1=", 232321, "message2=", 101011010101);
    CLOG_DEBUG("message1=", 232321, "message2=", 101011010101);
    CLOG_VERBOSE("message1=", 232321, "message2=", 101011010101);
    CLOG_INFO("message1=", 232321, "message2=", 101011010101);

    for (std::size_t index = 0u; index < 10u; ++index)
    {
        auto const chance{rand() % 100};
        if (chance < 2)
        {
            CLOG_CRITICAL("Index % 25 == 0, system sleep for 1s");
            std::this_thread::sleep_for(1s);
        }
        else if (chance < 5)
        {
            CLOG_ERROR("index=", index, "chance=", chance);
        }
        else if (chance < 8)
        {
            CLOG_WARN("index=", index, "chance=", chance);
        }
        else if (chance < 10)
        {
            CLOG_DEBUG("index=", index, "chance=", chance);
        }
        else if (chance < 25)
        {
            CLOG_VERBOSE("index=", index, "chance=", chance);
        }
        else
        {
            CLOG_INFO("index=", index, "chance=", chance);
        }
    }

    Logger::Instance().close();

    EXPECT_TRUE(std::filesystem::exists("/tmp/lunardb/logs"));

    int x{};
};

} // namespace LunarDB::Crescentum::API::Tests
