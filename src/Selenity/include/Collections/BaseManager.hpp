#pragma once

#include <memory>

#include "LunarDB/Selenity/CatalogEntry.hpp"

namespace LunarDB::Selenity::Collections {

class BaseManager
{
public: // lifecycle
    BaseManager(std::shared_ptr<Implementation::CatalogEntry> catalog_entry);

public: // public API
    Common::CppExtensions::UniqueID getUID() const;
    std::filesystem::path const& getHomePath() const;
    std::string_view getName() const;

protected: // fields
    std::shared_ptr<Implementation::CatalogEntry> m_catalog_info{};
};

} // namespace LunarDB::Selenity::Collections
