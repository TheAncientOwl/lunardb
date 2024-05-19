#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

#include "LunarDB/Common/CppExtensions/UniqueID.hpp"
#include "LunarDB/Selenity/CatalogEntry.hpp"
#include "LunarDB/Selenity/Collections/BaseManager.hpp"

namespace LunarDB::Selenity::Implementation {

class DatabaseManager
{
public: // life cycle
    DatabaseManager(std::shared_ptr<CatalogEntry> catalog_entry);

    DatabaseManager() = default;
    ~DatabaseManager();
    DatabaseManager(DatabaseManager const&) = delete;
    DatabaseManager& operator=(DatabaseManager const&) = delete;
    DatabaseManager(DatabaseManager&&) noexcept = default;
    DatabaseManager& operator=(DatabaseManager&&) noexcept = default;

public: // public API
    void createCollection(std::string const& collection_name);
    void dropCollection(std::string const& collection_name);

    Common::CppExtensions::UniqueID getUID() const;
    std::filesystem::path const& getHomePath() const;
    std::string_view getName() const;

    std::shared_ptr<Collections::BaseManager> getCollectionManager(std::string const& collection_name);

private: // private API
    void saveCatalogToDisk() const;
    void loadCatalogFromDisk();

    std::filesystem::path getCollectionsHomePath() const;
    std::filesystem::path getCollectionsCatalogFilePath() const;

private: // fields
    std::shared_ptr<CatalogEntry> m_catalog_info{};

    // TODO: Refactor, patter also used in SystemCatalog
    // map collection name -> catalog entry
    std::unordered_map<std::string, std::shared_ptr<CatalogEntry>> m_collections_catalog;

    // map collection uid -> collection manager
    Common::CppExtensions::UniqueID::MapTo<std::shared_ptr<Collections::BaseManager>> m_collection_managers;
};

} // namespace LunarDB::Selenity::Implementation
