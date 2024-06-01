#include <algorithm>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>
#include <sstream>
#include <stack>
#include <string>

#include "LunarDB/Moonlight/QueryExtractor.hpp"
#include "LunarDB/Selenity/Managers/Collections/EvaluateWhereClause.hpp"
#include "LunarDB/Selenity/Managers/Collections/TableManager.hpp"

using namespace std::string_literals;

namespace LunarDB::Selenity::API::Managers::Collections {

namespace {

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

void insert(
    std::filesystem::path const& home,
    Configurations::CollectionConfiguration::Schema& collection_schema,
    Common::QueryData::Insert::Object const& object)
{
    auto const rid{Common::CppExtensions::UniqueID::generate()};
    auto const rid_str{rid.toString()};

    nlohmann::json json{};
    json["_rid"] = rid_str;
    fillRecurseJSON(json, collection_schema, object);

    auto const document_file_path{home / (rid_str + ".ldbdoc")};
    auto const parent_path{document_file_path.parent_path()};
    if (!std::filesystem::exists(parent_path))
    {
        std::filesystem::create_directories(parent_path);
    }

    std::ofstream document(document_file_path);
    if (document.is_open())
    {
        document << json.dump(4);
        document.close();
    }
    else
    {
        // TODO: log error
    }
}

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
                oss << std::fixed << std::setprecision(10) << solved;
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

void TableManager::insert(std::vector<Common::QueryData::Insert::Object> const& objects)
{
    auto const documents_path{getDataHomePath()};
    if (!std::filesystem::exists(documents_path))
    {
        std::filesystem::create_directories(documents_path);
    }

    for (auto const& object : objects)
    {
        Collections::insert(documents_path, m_collection_config->schema, object);
    }
}

std::vector<std::unique_ptr<AbstractManager::ICollectionEntry>> TableManager::select(
    Common::QueryData::Select const& config) const
{
    std::vector<std::unique_ptr<AbstractManager::ICollectionEntry>> out{};
    auto const documents_path{getDataHomePath()};

    if (!std::filesystem::exists(documents_path) || !std::filesystem::is_directory(documents_path))
    {
        return out;
    }

    for (auto const& entry : std::filesystem::directory_iterator(documents_path))
    {
        if (!std::filesystem::is_regular_file(entry))
        {
            continue;
        }

        std::ifstream object_file(entry.path());
        if (object_file.is_open())
        {
            auto collection_entry_ptr = std::make_unique<TableManager::CollectionEntry>();
            object_file >> collection_entry_ptr->data;
            std::unique_ptr<AbstractManager::ICollectionEntry> icollection_entry_ptr{
                collection_entry_ptr.release()};
            object_file.close();

            if (WhereClause::evaluate(icollection_entry_ptr, m_collection_config->schema, config.where))
            {
                out.emplace_back(std::move(icollection_entry_ptr));
            }
        }
        else
        {
            // TODO: Log error
        }
    }

    return out;
}

nlohmann::json const& TableManager::CollectionEntry::getJSON() const
{
    return data;
}

void TableManager::deleteWhere(Common::QueryData::WhereClause const& where)
{
    auto documents_path{getDataHomePath()};

    if (!std::filesystem::exists(documents_path) || !std::filesystem::is_directory(documents_path))
    {
        // TODO: Log warning
        return;
    }

    for (auto const& entry : std::filesystem::directory_iterator(documents_path))
    {
        if (!std::filesystem::is_regular_file(entry))
        {
            continue;
        }

        std::ifstream object_file(entry.path());
        if (object_file.is_open())
        {
            auto collection_entry_ptr = std::make_unique<TableManager::CollectionEntry>();
            object_file >> collection_entry_ptr->data;
            object_file.close();

            std::unique_ptr<AbstractManager::ICollectionEntry> icollection_entry_ptr{
                collection_entry_ptr.release()};

            if (WhereClause::evaluate(icollection_entry_ptr, m_collection_config->schema, where))
            {
                std::filesystem::remove(entry.path());
            }
        }
        else
        {
            // TODO: Log error
        }
    }
}

void TableManager::update(Common::QueryData::Update const& config)
{
    auto documents_path{getDataHomePath()};

    if (!std::filesystem::exists(documents_path) || !std::filesystem::is_directory(documents_path))
    {
        // TODO: Log warning
        return;
    }

    for (auto const& entry : std::filesystem::directory_iterator(documents_path))
    {
        if (!std::filesystem::is_regular_file(entry))
        {
            continue;
        }

        std::fstream object_file{};
        object_file.open(entry.path(), std::ios::in);
        if (object_file.is_open())
        {
            auto collection_entry_ptr = std::make_unique<TableManager::CollectionEntry>();
            object_file >> collection_entry_ptr->data;
            object_file.close();

            std::unique_ptr<AbstractManager::ICollectionEntry> icollection_entry_ptr{
                collection_entry_ptr.release()};

            if (WhereClause::evaluate(icollection_entry_ptr, m_collection_config->schema, config.where))
            {
                object_file.open(entry.path(), std::ios::out | std::ios::trunc);
                if (object_file.is_open())
                {
                    collection_entry_ptr.reset(dynamic_cast<TableManager::CollectionEntry*>(
                        icollection_entry_ptr.release()));
                    Collections::update(
                        collection_entry_ptr->data, m_collection_config->schema, config.modify);
                    object_file << collection_entry_ptr->data;
                    object_file.close();
                }
                else
                {
                    // TODO: Log error
                }
            }
        }
        else
        {
            // TODO: Log error
        }
    }
}

} // namespace LunarDB::Selenity::API::Managers::Collections
