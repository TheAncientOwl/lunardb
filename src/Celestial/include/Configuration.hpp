#pragma once

#include <unordered_set>

#include "LunarDB/Common/CppExtensions/BinaryIO.hpp"
#include "LunarDB/Common/CppExtensions/DefinePrimitive.hpp"
#include "LunarDB/Common/CppExtensions/UniqueID.hpp"
#include "LunarDB/Common/QueryData/Primitives.hpp"

namespace LunarDB::Celestial::API::Configuration {

// clang-format off
DEFINE_LUNAR_PRIMITIVE(AuthState,
    Unknown = 0,
    Authenticated = 1,
    NotAuthenticated = 2,
    WrongPassword = 3,
    UnknwonUser = 4
)

DEFINE_LUNAR_PRIMITIVE(PermissionUpdateType,
    Unknown = 0,
    Grant = 1,
    Revoke = 2
)
// clang-format on

struct Permission
{
    using EUserPermissionType = Common::QueryData::Primitives::EUserPermissionType;

    EUserPermissionType type{EUserPermissionType::None};
    Common::CppExtensions::Types::UniqueID database_uid;
    Common::CppExtensions::Types::UniqueID collection_uid;

    bool operator==(Permission const&) const;
    struct Hash
    {
        std::size_t operator()(Permission const&) const;
    };

    LUNAR_ENABLE_BINARY_IO(type, database_uid, collection_uid);
};

struct PermissionUpdate
{
    EPermissionUpdateType update_type{EPermissionUpdateType::Unknown};
    Permission data;
};

struct User
{
    Common::CppExtensions::Types::UniqueID uid;
    std::string name;
    std::string password;
    std::unordered_set<Permission, Permission::Hash> permissions;
};

} // namespace LunarDB::Celestial::API::Configuration
