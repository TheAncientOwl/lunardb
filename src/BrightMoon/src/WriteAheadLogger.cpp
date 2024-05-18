#include "LunarDB/BrightMoon/WriteAheadLogger.hpp"
#include "LunarDB/Common/CppExtensions/BinaryIO.hpp"

#include <string>

namespace LunarDB::BrightMoon::API {

DEFINE_LUNAR_PRIMITIVE_IMPL(RecoveryFlag, {Literal::Recover, "y"}, {Literal::NoRecover, "n"});

namespace {

///
/// @brief Compute file paths for recovery and current logging.
/// @param[in] wal_home WriteAheadLogger data dir path.
/// @return {current, last}
///
std::pair<std::filesystem::path, std::optional<std::filesystem::path>> computeFilePaths(
    std::filesystem::path const& wal_home)
{
    auto const c_index_file_path{wal_home / "wal.hash.db"};

    auto out = std::make_pair<std::filesystem::path, std::optional<std::filesystem::path>>(
        wal_home /
            ("_wal." + std::to_string(std::chrono::system_clock::now().time_since_epoch().count()) +
             ".log"),
        std::nullopt);

    if (!std::filesystem::exists(c_index_file_path))
    {
        std::ofstream index_file(c_index_file_path, std::ios::binary);
        index_file.close();
    }
    else
    {
        std::ifstream index_file(c_index_file_path, std::ios::binary);
        std::string last_file_name{};
        Common::CppExtensions::BinaryIO::Deserializer::deserialize(index_file, last_file_name);
        index_file.close();

        out.second = wal_home / last_file_name;
    }

    std::ofstream index_file(c_index_file_path, std::ios::trunc | std::ios::binary);
    Common::CppExtensions::BinaryIO::Serializer::serialize(index_file, out.first.filename());
    index_file.close();

    return out;
}

///
/// Self explanatory
/// @param[in] wal_home WriteAheadLogger data dir path.
///
inline std::filesystem::path getRecoveryFilePath(std::filesystem::path const& wal_home)
{
    return wal_home / "wal.recovery.flag";
}

///
/// @brief Saves the recovery flag to disk.
/// @param[in] wal_home WriteAheadLogger data dir path.
/// @param flag
///
void writeRecoveryFlag(std::filesystem::path const& wal_home, ERecoveryFlag flag)
{
    std::ofstream flag_file(getRecoveryFilePath(wal_home), std::ios::trunc | std::ios::binary);
    Common::CppExtensions::BinaryIO::Serializer::serialize(flag_file, RecoveryFlag::toString(flag));
    flag_file.close();
}

///
/// @brief Reads the recovery flag from disk.
/// @param[in] wal_home WriteAheadLogger data dir path.
///
ERecoveryFlag readRecoveryFlag(std::filesystem::path const& wal_home)
{
    auto const recovery_file_path{getRecoveryFilePath(wal_home)};

    ERecoveryFlag flag{ERecoveryFlag::NoRecover};
    if (!std::filesystem::exists(recovery_file_path))
    {
        writeRecoveryFlag(wal_home, ERecoveryFlag::Recover);
    }
    else
    {
        std::ifstream flag_file(getRecoveryFilePath(wal_home), std::ios::binary);
        std::string flag_str{};
        Common::CppExtensions::BinaryIO::Deserializer::deserialize(flag_file, flag_str);
        flag_file.close();
        flag = RecoveryFlag::toLiteral(flag_str);
    }

    return flag;
}

} // namespace

LUNAR_SINGLETON_INIT_IMPL(WriteAheadLogger)
{
    // TODO: Fetch LunarDB home from another entity and add /wal path
    static std::filesystem::path const c_wal_dir_path{"/tmp/lunardb/wal"};
    if (!std::filesystem::exists(c_wal_dir_path))
    {
        std::filesystem::create_directories(c_wal_dir_path);
    }

    std::filesystem::path current_log_file_path{};
    std::tie(current_log_file_path, m_recovery_file_path) = computeFilePaths(c_wal_dir_path);

    m_recovery_flag = readRecoveryFlag(c_wal_dir_path);
    writeRecoveryFlag(c_wal_dir_path, ERecoveryFlag::Recover);

    m_log.open(current_log_file_path, std::ios::binary);
    m_log_start_time = std::chrono::system_clock::now();
}

void WriteAheadLogger::onNaturalSystemExit()
{
    // TODO: Fetch LunarDB home from another entity and add /wal path
    static std::filesystem::path const c_wal_dir_path{"/tmp/lunardb/wal"};
    if (!std::filesystem::exists(c_wal_dir_path))
    {
        std::filesystem::create_directories(c_wal_dir_path);
    }

    writeRecoveryFlag(c_wal_dir_path, ERecoveryFlag::NoRecover);
}

void WriteAheadLogger::log(TransactionData const& data)
{
    // TODO: Provide implementation
    throw std::runtime_error{"Not implemented yet..."};
}

void WriteAheadLogger::recover()
{
    // TODO: Provide implementation
    throw std::runtime_error{"Not implemented yet..."};
}

} // namespace LunarDB::BrightMoon::API
