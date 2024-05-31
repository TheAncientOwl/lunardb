#pragma once

#include <nlohmann/json.hpp>

#include "LunarDB/Selenity/Managers/Collections/AbstractManager.hpp"

namespace LunarDB::Selenity::API::Managers::Collections {

class DocumentManager : public AbstractManager
{
public: // lifecycle
    DocumentManager(std::shared_ptr<Configurations::CollectionConfiguration> config);

public: // CollectionEntry
    class CollectionEntry : public AbstractManager::ICollectionEntry
    {
    public:
        nlohmann::json const& getJSON() const override;

    private:
        nlohmann::json data{};

        friend class Selenity::API::Managers::Collections::DocumentManager;
    };

public: // public API
    void insert(std::vector<Common::QueryData::Insert::Object> const& objects) override;

    std::vector<std::unique_ptr<AbstractManager::ICollectionEntry>> select(
        Common::QueryData::Select const& config) const override;
};

} // namespace LunarDB::Selenity::API::Managers::Collections
