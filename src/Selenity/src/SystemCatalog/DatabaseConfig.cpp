#include "Selenity/private/SystemCatalog/DatabaseConfig.hpp"

namespace LunarDB::Selenity::Implementation::SystemCatalog {

DatabaseConfig::DatabaseConfig(std::filesystem::path storage_path, std::string name)
    : m_storage_path(std::move(storage_path)), m_name(std::move(name))
{
}

} // namespace LunarDB::Selenity::Implementation::SystemCatalog
