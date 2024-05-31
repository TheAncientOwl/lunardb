#pragma once

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

public: // public API
    Common::CppExtensions::UniqueID const& getUID() const;
    std::string_view getName() const;

private: // fields
    std::shared_ptr<Configurations::CollectionConfiguration> m_collection_config;
};

} // namespace LunarDB::Selenity::API::Managers::Collections
