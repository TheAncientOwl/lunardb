#pragma once

#include <fstream>
#include <ranges>

#include "LunarDB/Common/CppExtensions/BinaryIO.hpp"
#include "LunarDB/Selenity/Managers/CatalogManager.hpp"

namespace LunarDB::Selenity::API::Managers {

template <typename ManagerConfig, typename CatalogEntryConfig, typename CatalogEntryManager>
CatalogManager<ManagerConfig, CatalogEntryConfig, CatalogEntryManager>::CatalogManager(
    std::shared_ptr<ManagerConfig> config)
    : m_catalog{config, {}, {}}
{
}

template <typename ManagerConfig, typename CatalogEntryConfig, typename CatalogEntryManager>
void CatalogManager<ManagerConfig, CatalogEntryConfig, CatalogEntryManager>::saveConfigs() const
{
    // TODO: Refactor to write to other file then rename
    std::ofstream catalog_file(getCatalogFilePath(), std::ios::trunc | std::ios::binary);

    Common::CppExtensions::BinaryIO::Serializer::serialize(
        catalog_file, m_catalog.name_to_config.size());
    for (auto const& [name, config] : m_catalog.name_to_config)
    {
        Common::CppExtensions::BinaryIO::Serializer::serialize(catalog_file, config);
    }

    catalog_file.close();
}

template <typename ManagerConfig, typename CatalogEntryConfig, typename CatalogEntryManager>
void CatalogManager<ManagerConfig, CatalogEntryConfig, CatalogEntryManager>::CatalogData::clearConfig()
{
    name_to_config.clear();
    id_to_manager.clear();
}

template <typename ManagerConfig, typename CatalogEntryConfig, typename CatalogEntryManager>
void CatalogManager<ManagerConfig, CatalogEntryConfig, CatalogEntryManager>::loadConfigs()
{
    m_catalog.clearConfig();

    std::ifstream catalog_file(getCatalogFilePath(), std::ios::binary);

    if (catalog_file.is_open())
    {
        typename decltype(m_catalog.name_to_config)::size_type size{};
        Common::CppExtensions::BinaryIO::Deserializer::deserialize(catalog_file, size);
        m_catalog.name_to_config.reserve(size);
        m_catalog.id_to_manager.reserve(size);

        for (auto const _ : std::ranges::iota_view(0u, size))
        {
            auto entry = std::make_shared<CatalogEntryConfig>();
            Common::CppExtensions::BinaryIO::Deserializer::deserialize(catalog_file, entry);

            auto name{entry->name};
            auto entry_ptr =
                m_catalog.name_to_config.emplace(std::move(name), std::move(entry)).first->second;
            m_catalog.id_to_manager.emplace(
                entry_ptr->uid, std::make_shared<CatalogEntryManager>(entry_ptr));
        }
    }
    else
    {
        // TODO: log warning
    }
}

} // namespace LunarDB::Selenity::API::Managers
