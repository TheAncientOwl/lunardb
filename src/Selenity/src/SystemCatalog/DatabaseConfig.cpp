#include "LunarDB/Selenity/private/SystemCatalog/DatabaseConfig.hpp"

namespace LunarDB::Selenity::Implementation::SystemCatalog {

DatabaseConfig::DatabaseConfig(std::filesystem::path home_path, std::string name)
    : m_home_path(std::move(home_path)), m_name(std::move(name))
{
}

} // namespace LunarDB::Selenity::Implementation::SystemCatalog
