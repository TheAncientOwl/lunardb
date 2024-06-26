#include "LunarDB/Crescentum/Logger.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"

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
    { Literal::Crescentum, "Crescentum" },
    { Literal::LunarDB_SRV, "LunarDB_Server" },
    { Literal::LunarDB_CLI, "LunarDB_CLI" },
)
// clang-format on

LUNAR_SINGLETON_INIT_IMPL(Logger)
{
    auto const c_logs_dir_path{Selenity::API::SystemCatalog::Instance().getLunarHomePath() / "logs"};

    if (!std::filesystem::exists(c_logs_dir_path))
    {
        std::filesystem::create_directories(c_logs_dir_path);
    }

    auto const c_log_file_path{c_logs_dir_path / "lunardb.log"};
    if (std::filesystem::exists(c_log_file_path))
    {
        std::filesystem::rename(
            c_log_file_path,
            c_logs_dir_path /
                ("session." +
                 std::to_string(std::chrono::system_clock::now().time_since_epoch().count()) + ".log"));
    }

    m_log.open(c_log_file_path);
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

Logger::~Logger()
{
    close();
}

} // namespace LunarDB::Crescentum::API
