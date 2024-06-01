#pragma once

#include "LunarDB/Selenity/Managers/Collections/AbstractManager.hpp"

namespace LunarDB::Selenity::API::Managers::Collections {

class TableManager : public AbstractManager
{
public: // lifecycle
    TableManager(std::shared_ptr<Configurations::CollectionConfiguration> config);

public: // CollectionEntry
    class CollectionEntry : public AbstractManager::ICollectionEntry
    {
    public:
        nlohmann::json const& getJSON() const override;

    private:
        nlohmann::json data{};

        friend class Selenity::API::Managers::Collections::TableManager;
    };

public: // public API
    void insert(std::vector<Common::QueryData::Insert::Object> const& objects) override;

    std::vector<std::unique_ptr<AbstractManager::ICollectionEntry>> select(
        Common::QueryData::Select const& config) const override;

    void deleteWhere(Common::QueryData::WhereClause const& where) override;

    void update(Common::QueryData::Update const& config) override;
};

} // namespace LunarDB::Selenity::API::Managers::Collections
