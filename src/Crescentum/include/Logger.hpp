#pragma once

#include <chrono>
#include <fstream>
#include <queue>

#include "LunarDB/Common/CppExtensions/DefinePrimitive.hpp"
#include "LunarDB/Common/CppExtensions/Singleton.hpp"

namespace LunarDB::Crescentum::API {

// clang-format off
DEFINE_LUNAR_PRIMITIVE(LogLevel, 
    Verbose = 0,
    Info = 1,
    Debug = 2,
    Warning = 3,
    Error = 4,
    Critical = 5
)

DEFINE_LUNAR_PRIMITIVE(LunarModule,
    General = 0,
    LunarDB = 1,
    Moonlight = 2,
    Astral = 3,
    BrightMoon = 4,
    Selenity = 5,
    Celestial = 6,
    Crescentum = 7,
    LunarDB_SRV = 8,
    LunarDB_CLI = 9,
)
// clang-format on

class Logger : public Common::CppExtensions::DesignPatterns::Singleton<Logger>
{
public:
    template <typename... Args>
    void log(ELogLevel level, ELunarModule module, Args&&... args);

    void close();

public:
    ~Logger();

private:
    LUNAR_SINGLETON_INIT(Logger);

private:
    std::ofstream m_log{};
    std::queue<std::string> m_log_queue{};
    std::size_t m_log_queue_size{0};
    std::chrono::_V2::system_clock::time_point m_log_start_time{};
};

} // namespace LunarDB::Crescentum::API

#define MODULE_GENERAL LunarDB::Crescentum::API::ELunarModule::General
#define MODULE_LUNARDB LunarDB::Crescentum::API::ELunarModule::LunarDB
#define MODULE_MOONLIGHT LunarDB::Crescentum::API::ELunarModule::Moonlight
#define MODULE_ASTRAL LunarDB::Crescentum::API::ELunarModule::Astral
#define MODULE_BRIGHTMOON LunarDB::Crescentum::API::ELunarModule::BrightMoon
#define MODULE_SELENITY LunarDB::Crescentum::API::ELunarModule::Selenity
#define MODULE_CELESTIAL LunarDB::Crescentum::API::ELunarModule::Celestial
#define MODULE_CRESCENTUM LunarDB::Crescentum::API::ELunarModule::Crescentum
#define MODULE_LUNARDB_SRV LunarDB::Crescentum::API::ELunarModule::LunarDB_SRV

#define LUNAR_DECLARE_LOGGER_MODULE(module) auto const lunar_logger_module{module};

#define CLOG_VERBOSE(...)                             \
    LunarDB::Crescentum::API::Logger::Instance().log( \
        LunarDB::Crescentum::API::ELogLevel::Verbose, lunar_logger_module, __VA_ARGS__)

#define CLOG_INFO(...)                                \
    LunarDB::Crescentum::API::Logger::Instance().log( \
        LunarDB::Crescentum::API::ELogLevel::Info, lunar_logger_module, __VA_ARGS__)

#define CLOG_DEBUG(...)                               \
    LunarDB::Crescentum::API::Logger::Instance().log( \
        LunarDB::Crescentum::API::ELogLevel::Debug, lunar_logger_module, __VA_ARGS__)

#define CLOG_WARN(...)                                \
    LunarDB::Crescentum::API::Logger::Instance().log( \
        LunarDB::Crescentum::API::ELogLevel::Warning, lunar_logger_module, __VA_ARGS__)

#define CLOG_ERROR(...)                               \
    LunarDB::Crescentum::API::Logger::Instance().log( \
        LunarDB::Crescentum::API::ELogLevel::Error, lunar_logger_module, __VA_ARGS__)

#define CLOG_CRITICAL(...)                            \
    LunarDB::Crescentum::API::Logger::Instance().log( \
        LunarDB::Crescentum::API::ELogLevel::Critical, lunar_logger_module, __VA_ARGS__)

#include "LunarDB/Crescentum/private/Logger.inl"
