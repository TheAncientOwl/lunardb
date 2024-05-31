#pragma once

#include "LunarDB/Selenity/Managers/Collections/AbstractManager.hpp"

namespace LunarDB::Selenity::API::Managers::Collections {

class DocumentManager : public AbstractManager
{
public: // lifecycle
    DocumentManager(std::shared_ptr<Configurations::CollectionConfiguration> config);

public: // public API
    void insert(std::vector<Common::QueryData::Insert::Object> const& objects) override;
};

} // namespace LunarDB::Selenity::API::Managers::Collections
