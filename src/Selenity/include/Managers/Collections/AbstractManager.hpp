#pragma once

#include <memory>
#include <nlohmann/json.hpp>

#include "LunarDB/Common/QueryData/QueryData.hpp"
#include "LunarDB/Selenity/Managers/Configurations.hpp"

namespace LunarDB::Selenity::API::Managers::Collections {

class AbstractManager
{
public: // lifecycle
    AbstractManager(std::shared_ptr<Configurations::CollectionConfiguration> config);

public: // Factory
    struct Factory
    {
        static std::shared_ptr<AbstractManager> create(
            std::shared_ptr<Configurations::CollectionConfiguration> config);
    };

public: // CollectionEntry
    class ICollectionEntry
    {
    public: // lifecycle
        ICollectionEntry() = default;
        virtual ~ICollectionEntry() = default;
        ICollectionEntry(ICollectionEntry const&) = default;
        ICollectionEntry& operator=(ICollectionEntry const&) = default;
        ICollectionEntry(ICollectionEntry&&) noexcept = default;
        ICollectionEntry& operator=(ICollectionEntry&&) noexcept = default;

    public: // interface API
        virtual nlohmann::json const& getJSON() const = 0;
    };

public: // public API
    std::shared_ptr<Configurations::CollectionConfiguration> const& getConfig() const;
    Common::CppExtensions::UniqueID const& getUID() const;
    std::string_view getName() const;

    virtual void insert(std::vector<Common::QueryData::Insert::Object> const& objects) = 0;

    virtual std::vector<std::unique_ptr<ICollectionEntry>> select(
        Common::QueryData::Select const& config) const = 0;

protected: // fields
    std::shared_ptr<Configurations::CollectionConfiguration> m_collection_config;
};

} // namespace LunarDB::Selenity::API::Managers::Collections