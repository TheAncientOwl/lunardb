#pragma once

#include "LunarDB/Selenity/Managers/Collections/AbstractManager.hpp"

namespace LunarDB::Selenity::API::Managers::Collections {

class TableManager : public AbstractManager
{
public: // lifecycle
    TableManager(std::shared_ptr<Configurations::CollectionConfiguration> config);

public: // public API
    void insert(std::vector<Common::QueryData::Insert::Object> const& objects) override;
};

} // namespace LunarDB::Selenity::API::Managers::Collections
