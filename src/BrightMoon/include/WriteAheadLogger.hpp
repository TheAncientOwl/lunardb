#pragma once

#include <chrono>
#include <filesystem>
#include <fstream>
#include <optional>

#include "LunarDB/Common/CppExtensions/DefinePrimitive.hpp"
#include "LunarDB/Common/CppExtensions/Singleton.hpp"

namespace LunarDB::BrightMoon::API {

// clang-format off
DEFINE_LUNAR_PRIMITIVE(RecoveryFlag,
    Recover = 0,
    NoRecover = 1
)
// clang-format on

class TransactionData
{
    // TODO: Provide implementation
};

class WriteAheadLogger : public Common::CppExtensions::DesignPatterns::Singleton<WriteAheadLogger>
{
public:
    void log(TransactionData const& data);
    void onNaturalSystemExit();
    void recover();

private:
    LUNAR_SINGLETON_INIT(WriteAheadLogger);

private:
    std::ofstream m_log{};
    std::chrono::_V2::system_clock::time_point m_log_start_time{};
    std::optional<std::filesystem::path> m_recovery_file_path{};
    ERecoveryFlag m_recovery_flag{false};
};

} // namespace LunarDB::BrightMoon::API
