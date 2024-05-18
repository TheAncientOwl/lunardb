#include <gtest/gtest.h>

#include "LunarDB/Celestial/UsersCatalog.hpp"
#include "LunarDB/Common/CppExtensions/testing/TempFileSystemGuards.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"

using namespace std::string_literals;

namespace LunarDB::Celestial::API::Tests {

TEST(Celestial_UsersCatalog, crud)
{
    auto const c_lunar_home{Selenity::API::SystemCatalog::Instance().getLunarHomePath()};
    Common::CppExtensions::Testing::TempFileSystemGuards::TempDirectoryGuard users_directory_guard{
        c_lunar_home / "users"};
    std::filesystem::remove_all(users_directory_guard);

    auto& catalog{Celestial::API::UsersCatalog::Instance()};

    auto const c_username1{"SomeUsername1"s};
    auto const c_password1{"SomePassword1"s};

    auto const c_username2{"SomeUsername2"s};
    auto const c_password2{"SomePassword2"s};

    auto const c_database_uid{Common::CppExtensions::Types::UniqueID::generate()};
    auto const c_collection_uid{Common::CppExtensions::Types::UniqueID::generate()};
    auto const c_insert_permission{Configuration::Permission{
        Configuration::Permission::EUserPermissionType::Insert, c_database_uid, c_collection_uid}};
    auto const c_update_permission{Configuration::Permission{
        Configuration::Permission::EUserPermissionType::Update, c_database_uid, c_collection_uid}};
    auto const c_delete_permission{Configuration::Permission{
        Configuration::Permission::EUserPermissionType::Delete, c_database_uid, c_collection_uid}};

    // 1. createUser
    Common::CppExtensions::Types::UniqueID uid1{};
    Common::CppExtensions::Types::UniqueID uid2{};

    EXPECT_NO_THROW({ uid1 = catalog.createUser(c_username1, c_password1); });
    EXPECT_THROW({ uid2 = catalog.createUser(c_username1, c_password1); }, std::runtime_error);
    EXPECT_FALSE(uid1.toString().empty());
    EXPECT_TRUE(std::filesystem::exists(c_lunar_home / "users" / (uid1.toString() + ".cfg")));
    EXPECT_TRUE(std::filesystem::exists(c_lunar_home / "users" / "usernames.db"));

    // 2. updatePassword
    EXPECT_NO_THROW({ catalog.updatePassword(uid1, "SomeUpdatedPassword1"); });
    EXPECT_THROW({ catalog.updatePassword(uid2, "SomeUpdatedPassword2"); }, std::runtime_error);

    // 3. updatePermission
    EXPECT_NO_THROW({
        catalog.updatePermission(
            uid1,
            Configuration::PermissionUpdate{
                Configuration::EPermissionUpdateType::Grant, c_insert_permission});
    });
    EXPECT_NO_THROW({
        catalog.updatePermission(
            uid1,
            Configuration::PermissionUpdate{
                Configuration::EPermissionUpdateType::Grant, c_update_permission});
    });
    EXPECT_THROW(
        {
            catalog.updatePermission(
                uid2,
                Configuration::PermissionUpdate{
                    Configuration::EPermissionUpdateType::Grant, c_insert_permission});
        },
        std::runtime_error);

    // 3. userHasPermission
    EXPECT_TRUE(catalog.userHasPermission(uid1, c_insert_permission));
    EXPECT_TRUE(catalog.userHasPermission(uid1, c_update_permission));
    EXPECT_FALSE(catalog.userHasPermission(uid1, c_delete_permission));
    EXPECT_THROW({ catalog.userHasPermission(uid2, c_insert_permission); }, std::runtime_error);

    // 4. removeUser
    EXPECT_NO_THROW({ catalog.removeUser(uid1); });
    EXPECT_THROW({ catalog.removeUser(uid1); }, std::runtime_error);

    EXPECT_THROW({ catalog.updatePassword(uid1, "SomeUpdatedPassword1"); }, std::runtime_error);
    EXPECT_THROW(
        {
            catalog.updatePermission(
                uid1,
                Configuration::PermissionUpdate{
                    Configuration::EPermissionUpdateType::Grant, c_insert_permission});
        },
        std::runtime_error);
    EXPECT_THROW({ catalog.userHasPermission(uid1, c_insert_permission); }, std::runtime_error);
}

TEST(Celestial_UsersCatalog, authentication)
{
    // TODO: Provide implementation
}

} // namespace LunarDB::Celestial::API::Tests
