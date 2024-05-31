#include "LunarDB/Selenity/Managers/Configurations.hpp"

namespace LunarDB::Selenity::API::Managers::Configurations::Implementation {

CollectionConfiguration::CollectionConfiguration(
    std::string name,
    std::filesystem::path home,
    Common::CppExtensions::UniqueID uid,
    ECollectionType type)
    : BaseManagerConfiguration{std::move(name), std::move(home), std::move(uid)}
    , collection_type{type}
{
}

} // namespace LunarDB::Selenity::API::Managers::Configurations::Implementation
