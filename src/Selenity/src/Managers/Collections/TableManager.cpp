#include <algorithm>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>
#include <ranges>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "LunarDB/BrightMoon/WriteAheadLogger.hpp"
#include "LunarDB/Common/CppExtensions/BinaryIO.hpp"
#include "LunarDB/Crescentum/Logger.hpp"
#include "LunarDB/Moonlight/QueryExtractor.hpp"
#include "LunarDB/Selenity/Managers/Collections/EvaluateWhereClause.hpp"
#include "LunarDB/Selenity/Managers/Collections/TableManager.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"

LUNAR_DECLARE_LOGGER_MODULE(MODULE_SELENITY);

using namespace std::string_literals;

namespace LunarDB::Selenity::API::Managers::Collections {

namespace {

// TODO: Move in separate file
void fillRecurseJSON(
    nlohmann::json& json,
    Configurations::CollectionConfiguration::Schema& collection_schema,
    Common::QueryData::Insert::Object const& object)
{
    // TODO: Check object structure with schema and add to schema where necessary
    using Object = Common::QueryData::Insert::Object;

    for (auto const& [key, value] : object.entries)
    {
        if (std::holds_alternative<std::string>(value))
        {
            json[key] = std::get<std::string>(value);
        }
        else if (std::holds_alternative<Object>(value))
        {
            fillRecurseJSON(json[key], collection_schema, std::get<Object>(value));
        }
        else if (std::holds_alternative<std::vector<std::string>>(value))
        {
            json[key] = std::get<std::vector<std::string>>(value);
        }
        else if (std::holds_alternative<std::vector<Object>>(value))
        {
            nlohmann::json array = nlohmann::json::array();

            for (auto const& arr_object : std::get<std::vector<Object>>(value))
            {
                auto& arr_json_item = array.emplace_back();
                fillRecurseJSON(arr_json_item, collection_schema, arr_object);
            }

            json[key] = std::move(array);
        }
        else
        {
            // TODO: Log error
            assert(false && "Object writing failure, unknown variant alternative");
        }
    }
}

// TODO: Refactor to take table file stream as input
void insert(
    std::filesystem::path const& home,
    Configurations::CollectionConfiguration::Schema& collection_schema,
    Common::QueryData::Insert::Object const& object,
    std::shared_ptr<LunarDB::Selenity::API::Managers::Configurations::CollectionConfiguration> const& config)

{
    auto const rid{Common::CppExtensions::UniqueID::generate()};
    auto const rid_str{rid.toString()};

    nlohmann::json json{};
    json["_rid"] = rid_str;
    json["_del"] = "0";
    fillRecurseJSON(json, collection_schema, object);
    LunarDB::BrightMoon::API::Transactions::InsertTransactionData wal_data{};
    wal_data.database =
        LunarDB::Selenity::API::SystemCatalog::Instance().getDatabaseInUse()->getName();
    wal_data.collection = config->name;
    wal_data.json = json.dump();
    LunarDB::BrightMoon::API::WriteAheadLogger::Instance().log(wal_data);

    auto const document_file_path{home / "data.ldbtbl"};
    auto const parent_path{document_file_path.parent_path()};
    if (!std::filesystem::exists(parent_path))
    {
        std::filesystem::create_directories(parent_path);
    }

    std::ofstream table_file(document_file_path, std::ios::out | std::ios::app | std::ios::binary);
    if (table_file.is_open())
    {
        auto bson{nlohmann::json::to_bson(json)};
        LunarDB::Common::CppExtensions::BinaryIO::Serializer::serialize(table_file, bson);
        table_file.close();

        std::uint64_t entries_count{0};
        auto const file_path{home / "metadata.ldb"};

        {
            std::ifstream metadata_file(file_path, std::ios::binary);
            if (metadata_file.is_open())
            {
                Common::CppExtensions::BinaryIO::Deserializer::deserialize(
                    metadata_file, entries_count);
                metadata_file.close();
            }
        }

        entries_count++;

        {
            std::ofstream metadata_file(file_path, std::ios::binary);
            if (metadata_file.is_open())
            {
                Common::CppExtensions::BinaryIO::Serializer::serialize(metadata_file, entries_count);
                metadata_file.flush();
                metadata_file.close();
            }
            else
            {
                // TODO: Log error
                throw std::runtime_error("could not open metadata");
            }
        }
    }
    else
    {
        // TODO: log error
        throw std::runtime_error("could not open table file");
    }
}

// TODO: Move in separate file
std::uint8_t precedence(char operation)
{
    if (operation == '+' || operation == '-')
    {
        return 1;
    }
    if (operation == '*' || operation == '/')
    {
        return 2;
    }
    return 0;
}

template <typename T>
concept NumericType = requires() { std::is_same_v<T, int> || std::is_same_v<T, float>; };

template <NumericType Numeric>
Numeric applyOperation(Numeric lhs, Numeric rhs, char operation)
{
    switch (operation)
    {
    case '+':
        return lhs + rhs;
    case '-':
        return lhs - rhs;
    case '*':
        return lhs * rhs;
    case '/':
        if (rhs == 0)
        {
            throw std::runtime_error("Divison by 0");
        }
        return lhs / rhs;
    case '%':
        if constexpr (std::is_same_v<Numeric, int>)
        {
            return lhs % rhs;
        }
        else
        {
            return std::fmod(lhs, rhs);
        }
        break;
    default:
        throw std::runtime_error("Invalid operation '"s + operation + "'");
    }
}

template <NumericType Numeric>
Numeric solveNumericExpression(std::string_view expression, std::string_view key, Numeric key_numeric)
{
    using namespace std::string_view_literals;
    using namespace std::string_literals;

    Moonlight::Implementation::QueryExtractor extractor{expression};
    assert(!extractor.empty() && "Invalid update expression");

    std::stack<Numeric> values{};
    std::stack<char> operations{};

    while (!extractor.empty())
    {
        auto const token = extractor.extractOne();

        // Current token is an opening brace, push to operators stack
        if (token.length() == 1 && token.front() == '(')
        {
            operations.push('(');
        }
        // Current token is the field that will be modified, push its numeric value to the stack
        else if (token == key)
        {
            values.push(key_numeric);
        }
        // Current token is numeric, push to stack
        else if (std::all_of(token.begin(), token.end(), [](char const c) { return std::isdigit(c); }))
        {
            if constexpr (std::is_same_v<Numeric, int>)
            {
                values.push(std::stoi(std::string(token)));
            }
            else
            {
                values.push(std::stof(std::string(token)));
            }
        }
        // Current token is a closing brace, solve entire brace
        else if (token.length() == 1 && token.front() == ')')
        {
            while (!operations.emplace() && operations.top() != '(')
            {
                auto const value2{values.top()};
                values.pop();

                auto const value1{values.top()};
                values.pop();

                auto const operation{operations.top()};
                operations.pop();

                values.push(applyOperation(value1, value2, operation));
            }

            // Pop opening brace
            if (!operations.empty())
            {
                operations.pop();
            }
        }
        // Current token is an operator
        // TODO: enforce it to be an operator
        else if (token.length() == 1)
        {
            // While top of 'operations' has same or greater precedence to current token, which is
            // an operator, apply operator on top of 'operations' to top two elements in values stack
            while (!operations.empty() && precedence(operations.top()) >= precedence(token.front()))
            {
                auto const value2{values.top()};
                values.pop();

                auto const value1{values.top()};
                values.pop();

                auto const operation{operations.top()};
                operations.pop();

                values.push(applyOperation(value1, value2, operation));
            }

            operations.push(token.front());
        }
    }

    // Entire expression has been parsed, apply remaining operations to remaining values
    while (!operations.empty())
    {
        auto const value2{values.top()};
        values.pop();

        auto const value1{values.top()};
        values.pop();

        auto const operation(operations.top());
        operations.pop();

        values.push(applyOperation(value1, value2, operation));
    }

    return values.top();
}

void update(
    nlohmann::json& json,
    Configurations::CollectionConfiguration::Schema const& schema,
    std::vector<Common::QueryData::Update::Modify> const& modify_list)
{
    using namespace std::string_literals;

    for (auto const& modify : modify_list)
    {
        auto const& field{schema.getField(modify.field)};
        switch (field->type)
        {
        case Configurations::EFieldDataType::Rid:
            throw std::runtime_error("Cannot set reserved _rid field");
        case Configurations::EFieldDataType::DateTime:
            // TODO: Provide implementation
            throw std::runtime_error{
                "[~/lunardb/src/Selenity/src/Managers/Collections/"
                "TableManager.cpp:UpdateDateTime] Not implemented yet..."};
        case Configurations::EFieldDataType::String:
            json[modify.field] = modify.expression;
            break;
        case Configurations::EFieldDataType::Boolean:
            if (modify.expression == "true" || modify.expression == "false")
            {
                json[modify.field] = modify.expression;
            }
            else
            {
                throw std::runtime_error("Invalid boolean value '"s + modify.expression + "'");
            }
        case Configurations::EFieldDataType::Integer: {
            auto& value{json[modify.field]};
            auto const value_str{value.template get<std::string>()};
            try
            {
                auto const value_int{std::stoi(value_str)};
                auto const solved{solveNumericExpression(modify.expression, modify.field, value_int)};
                value = std::to_string(solved);
            }
            catch (std::invalid_argument const& e)
            {
                throw std::runtime_error("Cannot convert '"s + value_str + "' to Integer; " + e.what());
            }
            catch (std::out_of_range const& e)
            {
                throw std::runtime_error(
                    "Value '"s + value_str + "' out of Integer range; " + e.what());
            }
            break;
        }
        case Configurations::EFieldDataType::Float: {
            auto& value{json[modify.field]};
            auto const value_str{value.template get<std::string>()};
            try
            {
                auto const value_float{std::stof(value_str)};
                auto const solved{solveNumericExpression(modify.expression, modify.field, value_float)};
                std::ostringstream oss{};
                if (solved == int(solved))
                {
                    oss << std::fixed << std::setprecision(0) << solved;
                }
                else
                {
                    oss << std::fixed << std::setprecision(10) << solved;
                }
                value = oss.str();
            }
            catch (std::invalid_argument const& e)
            {
                throw std::runtime_error("Cannot convert '"s + value_str + "' to Float; " + e.what());
            }
            catch (std::out_of_range const& e)
            {
                throw std::runtime_error("Value '"s + value_str + "' out of Float range; " + e.what());
            }
            break;
        }
        case Configurations::EFieldDataType::None:
            [[fallthrough]];
        default:
            assert(false && "Encountered unknown field data type");
            break;
        }
    }
}

} // namespace

TableManager::TableManager(std::shared_ptr<Configurations::CollectionConfiguration> config)
    : AbstractManager(config)
{
}

// TODO: Refactor to pass table file stream to Collections::insert
void TableManager::insert(std::vector<Common::QueryData::Insert::Object> const& objects)
{
    auto const documents_path{getDataHomePath()};
    if (!std::filesystem::exists(documents_path))
    {
        std::filesystem::create_directories(documents_path);
    }

    for (auto const& object : objects)
    {
        Collections::insert(documents_path, m_collection_config->schema, object, m_collection_config);
    }
}

// TODO: Refactor
std::vector<std::unique_ptr<AbstractManager::ICollectionEntry>> TableManager::select(
    Common::QueryData::Select const& config) const
{
    std::vector<std::unique_ptr<AbstractManager::ICollectionEntry>> out{};
    auto const documents_path{getDataHomePath()};

    if (!std::filesystem::exists(documents_path) || !std::filesystem::is_directory(documents_path))
    {
        return out;
    }

    std::uint64_t entries_count{0};
    auto const file_path{getDataHomePath() / "metadata.ldb"};
    std::fstream metadata_file{};
    metadata_file.open(file_path, std::ios::in | std::ios::binary);

    if (metadata_file.is_open())
    {
        Common::CppExtensions::BinaryIO::Deserializer::deserialize(metadata_file, entries_count);
        metadata_file.close();

        auto const table_file_path(documents_path / "data.ldbtbl");
        std::ifstream table_file(table_file_path, std::ios::binary);
        if (table_file.is_open())
        {
            for (auto const _ : std::ranges::iota_view{0u, entries_count})
            {
                auto collection_entry_ptr = std::make_unique<TableManager::CollectionEntry>();
                std::vector<std::uint8_t> bson{};
                Common::CppExtensions::BinaryIO::Deserializer::deserialize(table_file, bson);
                collection_entry_ptr->data = nlohmann::json::from_bson(bson);
                if (collection_entry_ptr->data["_del"] == 1)
                {
                    continue;
                }

                std::unique_ptr<AbstractManager::ICollectionEntry> icollection_entry_ptr{
                    collection_entry_ptr.release()};

                if (WhereClause::evaluate(
                        icollection_entry_ptr, m_collection_config->schema, config.where))
                {
                    out.emplace_back(std::move(icollection_entry_ptr));
                }
            }
            table_file.close();
        }
    }

    return out;
}

nlohmann::json const& TableManager::CollectionEntry::getJSON() const
{
    return data;
}

// TODO: Refactor
void TableManager::deleteWhere(Common::QueryData::WhereClause const& where)
{
    auto documents_path{getDataHomePath()};

    if (!std::filesystem::exists(documents_path) || !std::filesystem::is_directory(documents_path))
    {
        // TODO: Log warning
        return;
    }

    std::uint64_t entries_count{0};
    auto const file_path{getDataHomePath() / "metadata.ldb"};
    std::fstream metadata_file{};
    metadata_file.open(file_path, std::ios::in | std::ios::binary);

    if (metadata_file.is_open())
    {
        Common::CppExtensions::BinaryIO::Deserializer::deserialize(metadata_file, entries_count);
        metadata_file.close();

        auto const table_file_path(documents_path / "data.ldbtbl");
        std::fstream table_file(table_file_path, std::ios::in | std::ios::out | std::ios::binary);
        if (table_file.is_open())
        {
            for (auto const _ : std::ranges::iota_view{0u, entries_count})
            {
                auto collection_entry_ptr = std::make_unique<TableManager::CollectionEntry>();
                std::vector<std::uint8_t> bson{};
                Common::CppExtensions::BinaryIO::Deserializer::deserialize(table_file, bson);
                collection_entry_ptr->data = nlohmann::json::from_bson(bson);
                if (collection_entry_ptr->data["_del"] == 1)
                {
                    continue;
                }
                std::unique_ptr<AbstractManager::ICollectionEntry> icollection_entry_ptr{
                    collection_entry_ptr.release()};

                if (WhereClause::evaluate(icollection_entry_ptr, m_collection_config->schema, where))
                {
                    LunarDB::BrightMoon::API::Transactions::DeleteTransactionData wal_data{};
                    wal_data.database =
                        LunarDB::Selenity::API::SystemCatalog::Instance().getDatabaseInUse()->getName();
                    wal_data.collection = m_collection_config->name;
                    wal_data.old_json = icollection_entry_ptr->getJSON().dump();
                    LunarDB::BrightMoon::API::WriteAheadLogger::Instance().log(wal_data);

                    collection_entry_ptr.reset(dynamic_cast<TableManager::CollectionEntry*>(
                        icollection_entry_ptr.release()));
                    collection_entry_ptr->data["_del"] = "1";
                    bson = nlohmann::json::to_bson(collection_entry_ptr->data);

                    auto const current_pos = table_file.tellg();

                    table_file.seekp(
                        -(static_cast<std::uint64_t>(bson.size()) + sizeof(std::size_t)),
                        std::ios::cur);
                    Common::CppExtensions::BinaryIO::Serializer::serialize(table_file, bson);

                    table_file.seekg(current_pos, std::ios::beg);
                }
            }
            table_file.close();
        }
    }
}

// TODO: Refactor
void TableManager::update(Common::QueryData::Update const& config)
{
    auto documents_path{getDataHomePath()};

    if (!std::filesystem::exists(documents_path) || !std::filesystem::is_directory(documents_path))
    {
        // TODO: Log warning
        return;
    }

    std::uint64_t entries_count{0};
    auto const file_path{getDataHomePath() / "metadata.ldb"};
    std::fstream metadata_file{};
    metadata_file.open(file_path, std::ios::in | std::ios::binary);

    if (metadata_file.is_open())
    {
        Common::CppExtensions::BinaryIO::Deserializer::deserialize(metadata_file, entries_count);
        metadata_file.close();

        auto const table_file_path(documents_path / "data.ldbtbl");
        std::fstream table_file(table_file_path, std::ios::in | std::ios::out | std::ios::binary);
        if (table_file.is_open())
        {
            for (auto const _ : std::ranges::iota_view{0u, entries_count})
            {
                auto collection_entry_ptr = std::make_unique<TableManager::CollectionEntry>();
                std::vector<std::uint8_t> bson{};
                Common::CppExtensions::BinaryIO::Deserializer::deserialize(table_file, bson);
                collection_entry_ptr->data = nlohmann::json::from_bson(bson);
                if (collection_entry_ptr->data["_del"] == 1)
                {
                    continue;
                }
                std::unique_ptr<AbstractManager::ICollectionEntry> icollection_entry_ptr{
                    collection_entry_ptr.release()};

                if (WhereClause::evaluate(
                        icollection_entry_ptr, m_collection_config->schema, config.where))
                {
                    collection_entry_ptr.reset(dynamic_cast<TableManager::CollectionEntry*>(
                        icollection_entry_ptr.release()));

                    LunarDB::BrightMoon::API::Transactions::UpdateTransactionData wal_data{};
                    wal_data.database =
                        LunarDB::Selenity::API::SystemCatalog::Instance().getDatabaseInUse()->getName();
                    wal_data.collection = m_collection_config->name;
                    wal_data.old_json = collection_entry_ptr->getJSON().dump();
                    LunarDB::BrightMoon::API::WriteAheadLogger::Instance().log(wal_data);

                    Collections::update(
                        collection_entry_ptr->data, m_collection_config->schema, config.modify);
                    bson = nlohmann::json::to_bson(collection_entry_ptr->data);

                    auto const current_pos = table_file.tellg();

                    table_file.seekp(
                        -(static_cast<std::uint64_t>(bson.size()) + sizeof(std::size_t)),
                        std::ios::cur);
                    Common::CppExtensions::BinaryIO::Serializer::serialize(table_file, bson);

                    table_file.seekg(current_pos, std::ios::beg);
                }
            }
            table_file.close();
        }
    }
}

void TableManager::undoInsert(nlohmann::json json, bool is_last_call)
{
    CLOG_VERBOSE("TableManager::undoInsert(): begin");

    static std::unordered_set<std::string> s_inserted_rids{};

    s_inserted_rids.emplace(json["_rid"]);
    if (!is_last_call)
    {
        return;
    }

    auto documents_path{getDataHomePath()};
    if (!std::filesystem::exists(documents_path) || !std::filesystem::is_directory(documents_path))
    {
        CLOG_ERROR("TableManager::undoInsert(): Could not open file:", documents_path);
        return;
    }

    std::uint64_t entries_count{0};
    auto const metadata_file_path{getDataHomePath() / "metadata.ldb"};
    std::fstream metadata_file{};
    metadata_file.open(metadata_file_path, std::ios::in | std::ios::binary);

    if (metadata_file.is_open())
    {
        Common::CppExtensions::BinaryIO::Deserializer::deserialize(metadata_file, entries_count);
        metadata_file.close();

        auto const table_file_path(documents_path / "data.ldbtbl");
        std::fstream table_file(table_file_path, std::ios::in | std::ios::out | std::ios::binary);
        if (table_file.is_open())
        {
            auto const undo_size = s_inserted_rids.size();
            std::size_t undo_number{0};

            for (auto const _ : std::ranges::iota_view{0u, entries_count})
            {
                std::vector<std::uint8_t> bson{};
                Common::CppExtensions::BinaryIO::Deserializer::deserialize(table_file, bson);
                auto json_entry = nlohmann::json::from_bson(bson);

                if (auto const rid_it = s_inserted_rids.find(json_entry["_rid"]);
                    rid_it != s_inserted_rids.end())
                {
                    auto const rid{*rid_it};
                    CLOG_INFO("TableManager::undoInsert(): RID:", rid);
                    json_entry["_del"] = "1";
                    bson = nlohmann::json::to_bson(json_entry);

                    auto const current_pos = table_file.tellg();

                    table_file.seekp(
                        -(static_cast<std::uint64_t>(bson.size()) + sizeof(std::size_t)),
                        std::ios::cur);
                    Common::CppExtensions::BinaryIO::Serializer::serialize(table_file, bson);

                    table_file.seekg(current_pos, std::ios::beg);

                    undo_number++;
                    CLOG_INFO(
                        "TableManager::undoInsert(): ",
                        undo_number,
                        "out of",
                        undo_size,
                        "changes undone");
                    s_inserted_rids.erase(rid_it);

                    CLOG_INFO("TableManager::undoInsert(): finished successfully RID:", rid);
                }
            }
            table_file.close();
        }
        else
        {
            CLOG_ERROR("TableManager::undoInsert(): Could not open data file", table_file_path);
        }
        metadata_file.close();
    }
    else
    {
        CLOG_ERROR("TableManager::undoInsert(): Could not open metadata file", metadata_file_path);
    }

    s_inserted_rids.clear();
    CLOG_VERBOSE("TableManager::undoInsert(): end");
}

void TableManager::undoUpdate(nlohmann::json json, bool is_last_call)
{
    CLOG_VERBOSE("TableManager::undoUpdate(): begin");

    static std::unordered_map<std::string, nlohmann::json> s_updated_rids{};

    std::string rid{json["_rid"]};
    s_updated_rids.emplace(std::move(rid), std::move(json));
    if (!is_last_call)
    {
        return;
    }

    auto documents_path{getDataHomePath()};
    if (!std::filesystem::exists(documents_path) || !std::filesystem::is_directory(documents_path))
    {
        CLOG_ERROR("TableManager::undoUpdate(): Could not open file:", documents_path);
        return;
    }

    std::uint64_t entries_count{0};
    auto const metadata_file_path{getDataHomePath() / "metadata.ldb"};
    std::fstream metadata_file{};
    metadata_file.open(metadata_file_path, std::ios::in | std::ios::binary);

    if (metadata_file.is_open())
    {
        Common::CppExtensions::BinaryIO::Deserializer::deserialize(metadata_file, entries_count);
        metadata_file.close();

        auto const table_file_path(documents_path / "data.ldbtbl");
        std::fstream table_file(table_file_path, std::ios::in | std::ios::out | std::ios::binary);
        if (table_file.is_open())
        {
            auto const undo_size = s_updated_rids.size();
            std::size_t undo_number{0};

            for (auto const _ : std::ranges::iota_view{0u, entries_count})
            {
                std::vector<std::uint8_t> bson{};
                Common::CppExtensions::BinaryIO::Deserializer::deserialize(table_file, bson);
                auto json_data = nlohmann::json::from_bson(bson);

                if (auto const rid_it = s_updated_rids.find(json_data["_rid"]);
                    rid_it != s_updated_rids.end())
                {
                    auto const rid{rid_it->first};
                    CLOG_INFO("TableManager::undoUpdate(): RID:", rid);
                    bson = nlohmann::json::to_bson(rid_it->second);

                    auto const current_pos = table_file.tellg();

                    table_file.seekp(
                        -(static_cast<std::uint64_t>(bson.size()) + sizeof(std::size_t)),
                        std::ios::cur);
                    Common::CppExtensions::BinaryIO::Serializer::serialize(table_file, bson);

                    table_file.seekg(current_pos, std::ios::beg);

                    undo_number++;
                    CLOG_INFO(
                        "TableManager::undoUpdate(): ",
                        undo_number,
                        "out of",
                        undo_size,
                        "changes undone");
                    s_updated_rids.erase(rid_it);

                    CLOG_INFO("TableManager::undoUpdate(): finished successfully RID:", rid);
                }
            }
            table_file.close();
        }
        else
        {
            CLOG_ERROR("TableManager::undoUpdate(): Could not open data file", table_file_path);
        }
        metadata_file.close();
    }
    else
    {
        CLOG_ERROR("TableManager::undoUpdate(): Could not open metadata file", metadata_file_path);
    }

    s_updated_rids.clear();
    CLOG_VERBOSE("TableManager::undoUpdate(): end");
}

void TableManager::undoDelete(nlohmann::json json, bool is_last_call)
{
    CLOG_VERBOSE("TableManager::undoDelete(): begin");

    static std::unordered_set<std::string> s_deleted_rids{};

    s_deleted_rids.emplace(json["_rid"]);
    if (!is_last_call)
    {
        return;
    }

    auto documents_path{getDataHomePath()};
    if (!std::filesystem::exists(documents_path) || !std::filesystem::is_directory(documents_path))
    {
        CLOG_ERROR("TableManager::undoDelete(): Could not open file:", documents_path);
        return;
    }

    std::uint64_t entries_count{0};
    auto const metadata_file_path{getDataHomePath() / "metadata.ldb"};
    std::fstream metadata_file{};
    metadata_file.open(metadata_file_path, std::ios::in | std::ios::binary);

    if (metadata_file.is_open())
    {
        Common::CppExtensions::BinaryIO::Deserializer::deserialize(metadata_file, entries_count);
        metadata_file.close();

        auto const table_file_path(documents_path / "data.ldbtbl");
        std::fstream table_file(table_file_path, std::ios::in | std::ios::out | std::ios::binary);
        if (table_file.is_open())
        {
            auto const undo_size = s_deleted_rids.size();
            std::size_t undo_number{0};

            for (auto const _ : std::ranges::iota_view{0u, entries_count})
            {
                std::vector<std::uint8_t> bson{};
                Common::CppExtensions::BinaryIO::Deserializer::deserialize(table_file, bson);
                auto json_data = nlohmann::json::from_bson(bson);

                if (auto const rid_it = s_deleted_rids.find(json_data["_rid"]);
                    rid_it != s_deleted_rids.end())
                {
                    auto const rid{*rid_it};
                    CLOG_INFO("TableManager::undoDelete(): RID:", rid);
                    json_data["_del"] = "0";
                    bson = nlohmann::json::to_bson(json_data);

                    auto const current_pos = table_file.tellg();

                    table_file.seekp(
                        -(static_cast<std::uint64_t>(bson.size()) + sizeof(std::size_t)),
                        std::ios::cur);
                    Common::CppExtensions::BinaryIO::Serializer::serialize(table_file, bson);

                    table_file.seekg(current_pos, std::ios::beg);

                    undo_number++;
                    CLOG_INFO(
                        "TableManager::undoDelete(): ",
                        undo_number,
                        "out of",
                        undo_size,
                        "changes undone");
                    s_deleted_rids.erase(rid_it);

                    CLOG_INFO("TableManager::undoDelete(): finished successfully RID:", rid);
                }
            }
            table_file.close();
        }
        else
        {
            CLOG_ERROR("TableManager::undoDelete(): Could not open data file", table_file_path);
        }
        metadata_file.close();
    }
    else
    {
        CLOG_ERROR("TableManager::undoDelete(): Could not open metadata file", metadata_file_path);
    }

    s_deleted_rids.clear();
    CLOG_VERBOSE("TableManager::undoDelete(): end");
}

} // namespace LunarDB::Selenity::API::Managers::Collections
