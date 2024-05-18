#include "LunarDB/Celestial/Configuration.hpp"

#include <functional>

namespace LunarDB::Celestial::API::Configuration {

bool Permission::operator==(Permission const& rhs) const
{
    return type == rhs.type && database_uid == rhs.database_uid &&
           collection_uid == rhs.collection_uid;
}

std::size_t Permission::Hash::operator()(Permission const& permission) const
{
    std::size_t seed{0};

    auto const type_hash{std::hash<std::uint8_t>{}(static_cast<std::uint8_t>(permission.type))};
    seed ^= type_hash;

    auto const database_uid_hash{
        Common::CppExtensions::Types::UniqueID::Hash{}(permission.database_uid)};
    seed ^= (database_uid_hash << 1);

    auto const collection_uid_hash{
        Common::CppExtensions::Types::UniqueID::Hash{}(permission.collection_uid)};
    seed ^= (collection_uid_hash << 2);

    return seed;
}

} // namespace LunarDB::Celestial::API::Configuration
