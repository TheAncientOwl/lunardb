#pragma once

#include <chrono>
#include <filesystem>
#include <fstream>
#include <optional>
#include <string>

#include "LunarDB/BrightMoon/TransactionData.hpp"
#include "LunarDB/Common/CppExtensions/DefinePrimitive.hpp"
#include "LunarDB/Common/CppExtensions/Singleton.hpp"
#include "LunarDB/Common/CppExtensions/UniqueID.hpp"
#include "LunarDB/Common/QueryData/QueryData.hpp"

namespace LunarDB::BrightMoon::API {

// clang-format off
DEFINE_LUNAR_PRIMITIVE(RecoveryFlag,
    Recover = 0,
    NoRecover = 1
)
// clang-format on

class WriteAheadLogger : public Common::CppExtensions::DesignPatterns::Singleton<WriteAheadLogger>
{
public:
    void openTransaction(LunarDB::Common::QueryData::Primitives::EQueryType const type);
    void closeTransaction(LunarDB::Common::QueryData::Primitives::EQueryType const type);
    void log(Transactions::TransactionData const& data);
    void onNaturalSystemExit();
    void recover();

private:
    LUNAR_SINGLETON_INIT(WriteAheadLogger);

private:
    std::ofstream m_log{};
    std::chrono::_V2::system_clock::time_point m_log_start_time{};
    std::optional<std::filesystem::path> m_recovery_file_path{};
    ERecoveryFlag m_recovery_flag{false};
    Common::CppExtensions::UniqueID m_current_transaction_uid{};
};

} // namespace LunarDB::BrightMoon::API
