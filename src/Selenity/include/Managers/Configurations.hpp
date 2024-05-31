#pragma once

#include <filesystem>
#include <string>

#include "LunarDB/Common/CppExtensions/BinaryIO.hpp"
#include "LunarDB/Common/CppExtensions/UniqueID.hpp"

namespace LunarDB::Selenity::API::Managers::Configurations {

namespace Implementation {

struct BaseManagerConfiguration
{
    std::string name{};
    std::filesystem::path home{};
    Common::CppExtensions::UniqueID uid{};

    LUNAR_ENABLE_BINARY_IO(name, home, uid);
};

struct CollectionConfiguration : public BaseManagerConfiguration
{
    enum class ECollectionType
    {
        Undefined,
        Table,
        Document
    };

    ECollectionType collection_type;

    CollectionConfiguration(
        std::string name,
        std::filesystem::path home,
        Common::CppExtensions::UniqueID uid,
        ECollectionType type);

    CollectionConfiguration() = default;
    ~CollectionConfiguration() = default;
    CollectionConfiguration(CollectionConfiguration const&) = default;
    CollectionConfiguration& operator=(CollectionConfiguration const&) = default;
    CollectionConfiguration(CollectionConfiguration&&) noexcept = default;
    CollectionConfiguration& operator=(CollectionConfiguration&&) noexcept = default;

    LUNAR_ENABLE_BINARY_IO(name, home, uid, collection_type);
};

struct ManagerNoConfiguration
{
};

} // namespace Implementation

using DatabaseConfiguration = Implementation::BaseManagerConfiguration;
using CollectionConfiguration = Implementation::CollectionConfiguration;
using NoConfiguration = Implementation::ManagerNoConfiguration;

} // namespace LunarDB::Selenity::API::Managers::Configurations
