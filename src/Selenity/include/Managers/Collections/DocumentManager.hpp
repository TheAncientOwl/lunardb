#pragma once

#include "LunarDB/Selenity/Managers/Collections/AbstractManager.hpp"

namespace LunarDB::Selenity::API::Managers::Collections {

class DocumentManager : public AbstractManager
{
public: // lifecycle
    DocumentManager(std::shared_ptr<Configurations::CollectionConfiguration> config);

private: // fields
    std::shared_ptr<Configurations::CollectionConfiguration> m_collection_config;
};

} // namespace LunarDB::Selenity::API::Managers::Collections
