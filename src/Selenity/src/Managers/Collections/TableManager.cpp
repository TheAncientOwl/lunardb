#include <fstream>
#include <nlohmann/json.hpp>

#include "LunarDB/Selenity/Managers/Collections/EvaluateWhereClause.hpp"
#include "LunarDB/Selenity/Managers/Collections/TableManager.hpp"

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

            if (WhereClause::evaluate(icollection_entry_ptr, m_collection_config->schema, config.where))
            {
                out.emplace_back(std::move(icollection_entry_ptr));
            }
            object_file.close();
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
}

} // namespace LunarDB::Selenity::API::Managers::Collections
