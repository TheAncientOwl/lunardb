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
        nlohmann::json& getJSON() override;

    private:
        nlohmann::json data{};

        friend class Selenity::API::Managers::Collections::DocumentManager;
    };

public: // public API
    std::vector<std::unique_ptr<AbstractManager::ICollectionEntry>> select(
        Common::QueryData::Select const& config) const override;

    void insert(std::vector<Common::QueryData::Insert::Object> const& objects) override;
    void update(Common::QueryData::Update const& config) override;
    void deleteWhere(Common::QueryData::WhereClause const& where) override;

    void undoInsert(nlohmann::json json, bool is_last_call) override;
    void undoUpdate(nlohmann::json json, bool is_last_call) override;
    void undoDelete(nlohmann::json json, bool is_last_call) override;
};

} // namespace LunarDB::Selenity::API::Managers::Collections
