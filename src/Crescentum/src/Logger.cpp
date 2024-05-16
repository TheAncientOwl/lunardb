#include "LunarDB/Crescentum/Logger.hpp"

#include <filesystem>
#include <string>

namespace LunarDB::Crescentum::API {

// clang-format off
DEFINE_LUNAR_PRIMITIVE_IMPL(LogLevel,
    { Literal::Verbose, "VERBOSE" },
    { Literal::Info, "INFO" },
    { Literal::Debug, "DEBUG" },
    { Literal::Warning, "WARNING" },
    { Literal::Error, "ERROR" },
    { Literal::Critical, "CRITICAL" },
)

DEFINE_LUNAR_PRIMITIVE_IMPL(LunarModule,
    { Literal::General, "General" },
    { Literal::LunarDB, "LunarDB" },
    { Literal::Moonlight, "Moonlight" },
    { Literal::Astral, "Astral" },
    { Literal::BrightMoon, "BrightMoon" },
    { Literal::Selenity, "Selenity" },
    { Literal::Celestial, "Celestial" },
    { Literal::Crescentum, "Crescentum" }
)
// clang-format on

LUNAR_SINGLETON_INIT_IMPL(Logger)
{
    static std::filesystem::path const c_logs_dir_path{"/tmp/lunardb/logs"};

    if (!std::filesystem::exists(c_logs_dir_path))
    {
        std::filesystem::create_directories(c_logs_dir_path);
    }

    auto const c_log_file{
        c_logs_dir_path /
        ("session." + std::to_string(std::chrono::system_clock::now().time_since_epoch().count()) +
         ".log")};

    m_log.open(c_log_file);
    m_log_start_time = std::chrono::system_clock::now();
}

void Logger::close()
{
    while (!m_log_queue.empty())
    {
        m_log << m_log_queue.front();
        m_log_queue.pop();
    }

    m_log.close();
}

} // namespace LunarDB::Crescentum::API
