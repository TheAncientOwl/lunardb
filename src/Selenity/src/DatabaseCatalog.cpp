#include "LunarDB/Selenity/private/DatabaseCatalog.hpp"

namespace LunarDB::Selenity::Implementation::SystemCatalog {

DatabaseCatalog::DatabaseCatalog(std::filesystem::path home_path, std::string name)
    : m_home_path(std::move(home_path)), m_name(std::move(name))
{
}

Common::CppExtensions::Types::UniqueID DatabaseCatalog::getCollectionUID(
    std::string const& collection_name) const
{
    // TODO: Provide actual implementation
    static auto const c_uid{Common::CppExtensions::Types::UniqueID::generate()};
    return c_uid;
}

Common::CppExtensions::Types::UniqueID DatabaseCatalog::getUID() const
{
    // TODO: Provide actual implementation
    static auto const c_uid{Common::CppExtensions::Types::UniqueID::generate()};
    return c_uid;
}

void DatabaseCatalog::createCollection(std::string name)
{
    // TODO: Provide implementation
}

} // namespace LunarDB::Selenity::Implementation::SystemCatalog
