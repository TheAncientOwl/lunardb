#include <chrono>
#include <nlohmann/json.hpp>
#include <queue>
#include <sstream>
#include <stack>

#include "LunarDB/BrightMoon/WriteAheadLogger.hpp"
#include "LunarDB/Common/CppExtensions/BinaryIO.hpp"
#include "LunarDB/Common/CppExtensions/StringUtils.hpp"
#include "LunarDB/Crescentum/Logger.hpp"
#include "LunarDB/Moonlight/QueryExtractor.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"

LUNAR_DECLARE_LOGGER_MODULE(MODULE_BRIGHTMOON);

using namespace std::string_view_literals;

namespace LunarDB::BrightMoon::API {

// clang-format off
DEFINE_LUNAR_PRIMITIVE_IMPL(RecoveryFlag, 
    {Literal::Recover, "Y"}, 
    {Literal::NoRecover, "N"}
);
// clang-format on

namespace {

bool isSupportedTransaction(LunarDB::Common::QueryData::Primitives::EQueryType const type)
{
    using EQueryType = LunarDB::Common::QueryData::Primitives::EQueryType;
    static std::array<EQueryType, 9> const c_supported_transactions{
        // EQueryType::Migrate,
        // EQueryType::Truncate,
        // EQueryType::Rename,
        EQueryType::Insert,
        EQueryType::Update,
        EQueryType::Delete,
        // EQueryType::Commit,
        // EQueryType::Rollback,
        // EQueryType::SavePoint,
    };

    return std::find(c_supported_transactions.begin(), c_supported_transactions.end(), type) !=
           c_supported_transactions.end();
}

} // namespace

LUNAR_SINGLETON_INIT_IMPL(WriteAheadLogger)
{
    auto const logs_dir_path{getHomePath()};

    auto const log_file_path{logs_dir_path / "wal.log"};
    if (std::filesystem::exists(log_file_path))
    {
        m_recovery_file_path =
            logs_dir_path /
            ("session." + std::to_string(std::chrono::system_clock::now().time_since_epoch().count()) +
             ".wal.log");

        std::filesystem::rename(log_file_path, *m_recovery_file_path);
    }

    m_log.open(log_file_path, std::ios::binary);
}

std::filesystem::path WriteAheadLogger::getHomePath() const
{
    std::filesystem::path const home_path{
        LunarDB::Selenity::API::SystemCatalog::Instance().getLunarHomePath() / "wal"};

    if (!std::filesystem::exists(home_path))
    {
        std::filesystem::create_directories(home_path);
    }

    return home_path;
}

std::filesystem::path WriteAheadLogger::getRecoveryFlagFilePath() const
{
    return getHomePath() / "wal.recovery.flag";
}

void WriteAheadLogger::setRecoveryFlag(ERecoveryFlag flag) const
{
    CLOG_INFO("::writeRecoveryFlag():", flag);
    std::ofstream flag_file(getRecoveryFlagFilePath(), std::ios::trunc | std::ios::binary);
    if (flag_file.is_open())
    {
        Common::CppExtensions::BinaryIO::Serializer::serialize(
            flag_file, RecoveryFlag::toString(flag));
        flag_file.close();
    }
    else
    {
        CLOG_ERROR(
            "::writeRecoveryFlag(): Could not open recovery flag file", getRecoveryFlagFilePath());
    }
}

ERecoveryFlag WriteAheadLogger::getRecoveryFlag() const
{
    CLOG_VERBOSE("::readRecoveryFlag()");
    auto const recovery_file_path{getRecoveryFlagFilePath()};

    ERecoveryFlag flag{ERecoveryFlag::NoRecover};

    if (!std::filesystem::exists(recovery_file_path))
    {
        setRecoveryFlag(ERecoveryFlag::Recover);
    }
    else
    {
        std::ifstream flag_file(getRecoveryFlagFilePath(), std::ios::binary);
        if (flag_file.is_open())
        {
            std::string flag_str{};
            Common::CppExtensions::BinaryIO::Deserializer::deserialize(flag_file, flag_str);
            flag_file.close();
            flag = RecoveryFlag::toLiteral(flag_str);
        }
        else
        {
            CLOG_ERROR(
                "::readRecoveryFlag(): Could not open recovery flag file", getRecoveryFlagFilePath());
        }
    }

    CLOG_VERBOSE("::readRecoveryFlag(): flag ->", flag);

    return flag;
}

void WriteAheadLogger::onNaturalSystemExit()
{
    CLOG_INFO("::onNaturalSystemExit()");
    setRecoveryFlag(ERecoveryFlag::NoRecover);
}

void WriteAheadLogger::log(Transactions::TransactionData const& data)
{
    CLOG_VERBOSE("::log():", data.toString());
    m_log << data.toString() << std::endl;
}

void WriteAheadLogger::recover()
{
    CLOG_VERBOSE("::recover()");
    auto const recovery_flag = getRecoveryFlag();

    if (recovery_flag == ERecoveryFlag::NoRecover)
    {
        CLOG_VERBOSE("::recover(): No recovery needed");
        return;
    }

    if (!static_cast<bool>(m_recovery_file_path))
    {
        CLOG_CRITICAL("Recovery file not found. X05");
        return;
    }

    CLOG_VERBOSE("::recover(): Recovery needed");

    // 1. Read wal file backwards
    // 2. if no CLOSE_TRANSACTION found, read until you find OPEN_TRANSACTION
    // @note: while reading add the items to a queue to revert them.
    // 3. when OPEN_TRANSACTION found, revert the actions in queue.

    std::ifstream log_file(*m_recovery_file_path);

    if (!log_file.is_open())
    {
        CLOG_CRITICAL("::recover(): Could not open recovery file", *m_recovery_file_path);
        return;
    }

    std::string current_line{};
    current_line.reserve(256);
    std::queue<std::string> logs{};

    log_file.seekg(0, std::ios::end);
    auto file_size = log_file.tellg();

    CLOG_VERBOSE("::recover(): Reading last failed transaction logs");
    for (auto pos = file_size - std::streampos{1}, end = std::streamoff{0}; pos >= end; pos -= 1)
    {
        log_file.seekg(pos);

        char c{};
        log_file.get(c);

        if (c == '\n' && !current_line.empty())
        {
            auto line = std::string{current_line.rbegin(), current_line.rend()};

            if (LunarDB::Common::CppExtensions::StringUtils::startsWithIgnoreCase(
                    line, "OPEN_TRANSACTION"))
            {
                break;
            }

            if (logs.empty())
            {
                if (LunarDB::Common::CppExtensions::StringUtils::startsWithIgnoreCase(
                        line, "CLOSE_TRANSACTION"))
                {
                    return;
                }
                logs.emplace(std::move(line));
            }
            else
            {
                logs.emplace(std::move(line));
            }

            current_line.clear();
        }
        else if (c != '\n')
        {
            current_line.push_back(c);
        }

        if (pos == 0 && !current_line.empty())
        {
            auto line = std::string{current_line.rbegin(), current_line.rend()};
            if (!LunarDB::Common::CppExtensions::StringUtils::startsWithIgnoreCase(
                    line, "OPEN_TRANSACTION"))
            {
                logs.emplace(std::move(line));
            }
        }
    }

    log_file.close();

    auto& system_catalog{LunarDB::Selenity::API::SystemCatalog::Instance()};

    CLOG_VERBOSE("::recover(): Processing last failed transaction logs");
    while (!logs.empty())
    {
        auto log = std::move(logs.front());
        logs.pop();

        CLOG_VERBOSE("::recover():", log);

        if (log.starts_with("Insert"))
        {
            LunarDB::Moonlight::Implementation::QueryExtractor extractor{log};
            auto const [insert_kw, database_name, collection_name, arrow_kw, json_kw] =
                extractor.extractTuple<5>();

            nlohmann::json json = nlohmann::json::parse(extractor.data());

            system_catalog.useDatabase(std::string(database_name));
            auto collection =
                system_catalog.getDatabaseInUse()->getCollection(std::string(collection_name));
            collection->undoInsert(json, logs.empty());
        }
        else if (log.starts_with("Delete"))
        {
            LunarDB::Moonlight::Implementation::QueryExtractor extractor{log};
            auto const [delete_kw, database_name, collection_name, arrow_kw, json_kw] =
                extractor.extractTuple<5>();

            nlohmann::json json = nlohmann::json::parse(extractor.data());

            system_catalog.useDatabase(std::string(database_name));
            auto collection =
                system_catalog.getDatabaseInUse()->getCollection(std::string(collection_name));
            collection->undoDelete(json, logs.empty());
        }
        else if (log.starts_with("Update"))
        {
            LunarDB::Moonlight::Implementation::QueryExtractor extractor{log};
            auto const [update_kw, database_name, collection_name, arrow_kw, json_kw] =
                extractor.extractTuple<5>();

            nlohmann::json json = nlohmann::json::parse(extractor.data());

            system_catalog.useDatabase(std::string(database_name));
            auto collection =
                system_catalog.getDatabaseInUse()->getCollection(std::string(collection_name));
            collection->undoUpdate(json, logs.empty());
        }
        else
        {
            CLOG_ERROR("Unsupported undo operation", log);
        }
    }
};

void WriteAheadLogger::openTransaction(LunarDB::Common::QueryData::Primitives::EQueryType const type)
{
    if (!isSupportedTransaction(type))
    {
        return;
    }

    m_last_commit_savepoint_hash = Common::CppExtensions::UniqueID::generate().toString();
    savepoint(m_last_commit_savepoint_hash);

    m_current_transaction_uid = Common::CppExtensions::UniqueID::generate();
    CLOG_VERBOSE("::openTransaction():", m_current_transaction_uid->toString());
    Transactions::OpenTransactionData data{};
    data.uid = *m_current_transaction_uid;
    log(data);
}

void WriteAheadLogger::closeTransaction(LunarDB::Common::QueryData::Primitives::EQueryType const type)
{
    if (!isSupportedTransaction(type))
    {
        return;
    }

    commit();
}

void WriteAheadLogger::commit()
{
    if (m_current_transaction_uid.has_value())
    {
        CLOG_VERBOSE("::commit():", m_current_transaction_uid->toString());
        if (m_last_commit_savepoint_hash.has_value())
        {
            m_commit_savepoint_hashes.emplace(std::move(*m_last_commit_savepoint_hash));
            m_last_commit_savepoint_hash = std::nullopt;
        }
        Transactions::CloseTransactionData data{};
        data.uid = *m_current_transaction_uid;
        log(data);
        m_current_transaction_uid = std::nullopt;
    }
}

void WriteAheadLogger::savepoint(std::optional<std::string> const hash)
{
    Transactions::SavePointTransactionData data{};
    data.hash = hash.has_value() ? std::move(*hash)
                                 : LunarDB::Common::CppExtensions::UniqueID::generate().toString();
    CLOG_VERBOSE("::savepoint():", data.hash);
    log(data);
}

// TODO: Refactor
void WriteAheadLogger::rollback(std::optional<std::string> const hash)
{
    CLOG_VERBOSE("::rollback()");
    std::string rollback_hash{};
    if (hash.has_value())
    {
        rollback_hash = std::move(*hash);
    }
    else if (!m_commit_savepoint_hashes.empty())
    {
        rollback_hash = std::move(m_commit_savepoint_hashes.top());
        m_commit_savepoint_hashes.pop();
    }
    else
    {
        throw std::runtime_error{
            "No commits left to be undone in this session. Try a specific hash"};
    }
    CLOG_VERBOSE("::rollback(): hash", rollback_hash);

    // TODO: Update to support savepoints from all time;

    m_log.flush();
    m_log.close();

    auto const c_home_path{getHomePath()};
    auto const c_log_file_path{c_home_path / "wal.log"};
    auto const c_rollback_file_path{c_home_path / "rollback.log"};
    std::filesystem::copy(
        c_log_file_path, c_rollback_file_path, std::filesystem::copy_options::overwrite_existing);

    m_log.open(c_log_file_path, std::ios::binary | std::ios::app);

    std::ifstream rollback_file{c_rollback_file_path, std::ios::binary};

    std::string line{};
    bool found_hash{false};

    struct Table
    {
        char last_log_type{'-'};
        std::size_t rollback_history_index{0};
        std::vector<std::string> history{};
        std::stack<std::size_t> insert_end_indices{};
        std::stack<std::size_t> update_end_indices{};
        std::stack<std::size_t> delete_end_indices{};
    };

    std::unordered_map<std::string, std::unordered_map<std::string, Table>> history_dictionary{};

    static auto constexpr s_supported_operations{"IUD"sv};

    while (std::getline(rollback_file, line))
    {
        if (found_hash && s_supported_operations.find(line.front()) != std::string_view::npos)
        {
            LunarDB::Moonlight::Implementation::QueryExtractor extractor{line};
            auto const [type, database, table] = extractor.extractTuple<3>();

            auto database_it = history_dictionary.find(std::string{type});
            if (database_it == history_dictionary.end())
            {
                database_it =
                    history_dictionary.emplace(database, std::unordered_map<std::string, Table>{}).first;
            }

            auto table_it = database_it->second.find(std::string{table});
            if (table_it == database_it->second.end())
            {
                table_it = database_it->second.emplace(table, Table{}).first;
            }

            auto& data = table_it->second;

            std::stack<std::size_t>* stack_ptr{nullptr};
            bool supported_operation{false};
            switch (line.front())
            {
            case 'I':
                if (data.last_log_type != 'I')
                {
                    if (data.last_log_type == 'U')
                    {
                        stack_ptr = &data.update_end_indices;
                    }
                    else if (data.last_log_type == 'D')
                    {
                        stack_ptr = &data.delete_end_indices;
                    }
                    else if (data.last_log_type == '-')
                    {
                        stack_ptr = &data.insert_end_indices;
                    }
                }
                supported_operation = true;
                data.last_log_type = 'I';
                break;
            case 'U':
                if (data.last_log_type != 'U')
                {
                    if (data.last_log_type == 'I')
                    {
                        stack_ptr = &data.insert_end_indices;
                    }
                    else if (data.last_log_type == 'D')
                    {
                        stack_ptr = &data.delete_end_indices;
                    }
                    else if (data.last_log_type == 'U')
                    {
                        stack_ptr = &data.update_end_indices;
                    }
                }
                supported_operation = true;
                data.last_log_type = 'U';
                break;
            case 'D':
                if (data.last_log_type != 'D')
                {
                    if (data.last_log_type == 'I')
                    {
                        stack_ptr = &data.insert_end_indices;
                    }
                    else if (data.last_log_type == 'U')
                    {
                        stack_ptr = &data.update_end_indices;
                    }
                    else if (data.last_log_type == 'D')
                    {
                        stack_ptr = &data.delete_end_indices;
                    }
                }
                supported_operation = true;
                data.last_log_type = 'D';
                break;
            default:
                break;
            }

            if (stack_ptr)
            {
                stack_ptr->push(data.rollback_history_index);
            }

            if (supported_operation)
            {
                CLOG_VERBOSE("::rollback(): operation", data.last_log_type);
                data.history.emplace_back(std::move(line));
                ++data.rollback_history_index;
            }

            continue;
        }

        std::string_view line_sv{line};
        if (!line_sv.starts_with("SavePoint"))
        {
            continue;
        }
        line_sv.remove_prefix(10);
        LunarDB::Common::CppExtensions::StringUtils::trim(line_sv);
        if (line_sv == rollback_hash)
        {
            found_hash = true;
        }
        else if (m_rollbacked_hashes.contains(std::string{line_sv}))
        {
            history_dictionary.clear();
        }
    }

    auto& system_catalog{LunarDB::Selenity::API::SystemCatalog::Instance()};

    auto const current_database_name{system_catalog.getDatabaseInUse()->getName()};
    for (auto& [database_name, tables] : history_dictionary)
    {
        system_catalog.useDatabase(database_name);
        for (auto& [table_name, table] : tables)
        {
            if (table.history.empty())
            {
                return;
            }

            for (std::int64_t index = table.history.size() - 1; index >= 0; --index)
            {
                std::string const& log{table.history[index]};

                if (log.starts_with("Insert"))
                {
                    LunarDB::Moonlight::Implementation::QueryExtractor extractor{log};
                    auto const [insert_kw, database_name, collection_name, arrow_kw, json_kw] =
                        extractor.extractTuple<5>();

                    nlohmann::json json = nlohmann::json::parse(extractor.data());

                    system_catalog.useDatabase(std::string(database_name));
                    auto collection =
                        system_catalog.getDatabaseInUse()->getCollection(std::string(collection_name));

                    if (!table.insert_end_indices.empty() && index == table.insert_end_indices.top())
                    {
                        table.insert_end_indices.pop();
                        collection->undoInsert(json, true);
                    }
                    else
                    {
                        collection->undoInsert(json, false);
                    }
                }
                else if (log.starts_with("Delete"))
                {
                    LunarDB::Moonlight::Implementation::QueryExtractor extractor{log};
                    auto const [delete_kw, database_name, collection_name, arrow_kw, json_kw] =
                        extractor.extractTuple<5>();

                    nlohmann::json json = nlohmann::json::parse(extractor.data());

                    system_catalog.useDatabase(std::string(database_name));
                    auto collection =
                        system_catalog.getDatabaseInUse()->getCollection(std::string(collection_name));
                    if (!table.delete_end_indices.empty() && index == table.delete_end_indices.top())
                    {
                        table.delete_end_indices.pop();
                        collection->undoDelete(json, true);
                    }
                    else
                    {
                        collection->undoDelete(json, false);
                    }
                }
                else if (log.starts_with("Update"))
                {
                    LunarDB::Moonlight::Implementation::QueryExtractor extractor{log};
                    auto const [update_kw, database_name, collection_name, arrow_kw, json_kw] =
                        extractor.extractTuple<5>();

                    nlohmann::json json = nlohmann::json::parse(extractor.data());

                    system_catalog.useDatabase(std::string(database_name));
                    auto collection =
                        system_catalog.getDatabaseInUse()->getCollection(std::string(collection_name));
                    if (!table.update_end_indices.empty() && index == table.update_end_indices.top())
                    {
                        table.update_end_indices.pop();
                        collection->undoUpdate(json, true);
                    }
                    else
                    {
                        collection->undoUpdate(json, false);
                    }
                }
            }
        }
    }
    system_catalog.useDatabase(std::string{current_database_name});
    m_rollbacked_hashes.emplace(std::move(rollback_hash));
}

} // namespace LunarDB::BrightMoon::API
