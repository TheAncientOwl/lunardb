#pragma once

#include <filesystem>
#include <memory>
#include <unordered_map>

#include "LunarDB/Common/CppExtensions/UniqueID.hpp"

namespace LunarDB::Selenity::API::Managers {

template <typename ManagerConfig, typename CatalogEntryConfig, typename CatalogEntryManager>
class CatalogManager
{
public: // lifecycle
    CatalogManager(std::shared_ptr<ManagerConfig> config);

    CatalogManager() = default;
    ~CatalogManager() = default;
    CatalogManager(CatalogManager const&) = delete;
    CatalogManager& operator=(CatalogManager const&) = delete;
    CatalogManager(CatalogManager&&) noexcept = default;
    CatalogManager& operator=(CatalogManager&&) noexcept = default;

public: // interface API
    std::shared_ptr<ManagerConfig> const& getConfig() const;

    void saveConfigs() const;
    void loadConfigs();

    virtual std::filesystem::path getHomePath() const = 0;
    virtual std::filesystem::path getDataHomePath() const = 0;
    virtual std::filesystem::path getCatalogFilePath() const = 0;

protected: // fields
    struct CatalogData
    {
        std::shared_ptr<ManagerConfig> config;
        std::unordered_map<std::string, std::shared_ptr<CatalogEntryConfig>> name_to_config;
        Common::CppExtensions::UniqueID::MapTo<std::shared_ptr<CatalogEntryManager>> id_to_manager;

        void clearConfig();
    };

    CatalogData m_catalog;
};

} // namespace LunarDB::Selenity::API::Managers

#include "LunarDB/Selenity/Managers/private/CatalogManager.inl"
