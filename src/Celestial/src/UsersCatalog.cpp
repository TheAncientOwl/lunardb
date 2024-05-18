#include "LunarDB/Celestial/UsersCatalog.hpp"

#include <cassert>
#include <fstream>
#include <stdexcept>

#include "LunarDB/Common/CppExtensions/BinaryIO.hpp"
#include "LunarDB/Common/CppExtensions/StringUtils.hpp"
#include "LunarDB/Common/Cryptography/AES256.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"

namespace LunarDB::Celestial::API {

LUNAR_SINGLETON_INIT_IMPL(UsersCatalog)
{
    loadFromDisk();
}

Common::CppExtensions::Types::UniqueID UsersCatalog::createUser(std::string username, std::string password)
{
    // 1. Check if username available
    if (m_usernames.find(username) != m_usernames.end())
    {
        throw std::runtime_error(Common::CppExtensions::StringUtils::stringify(
            "User with", std::move(username), "username already exists"));
    }

    // 2. WriteAheadLog
    // TODO: Provide implementation

    // 3. Add user to internal data
    std::ignore = m_usernames.insert(username);
    auto const new_id{Common::CppExtensions::Types::UniqueID::generate()};
    auto const map_result = m_users.emplace(
        new_id, Configuration::User{new_id, std::move(username), std::move(password), {}});

    assert(map_result.second && "[Create User] Map insert failed");

    // 4. Save user to disk
    saveUserToDisk(map_result.first->second);
    saveUserNamesToDisk();

    return new_id;
}

void UsersCatalog::removeUser(Common::CppExtensions::Types::UniqueID const& user_uid)
{
    // 1. Get user data
    auto& user{getUser(user_uid)};

    // 2. WriteAheadLog
    // TODO: Provide implementation

    // 3. Remove user from internal data
    std::ignore = m_users.erase(user_uid);
    std::ignore = m_usernames.erase(user.name);

    // 4. Remove user from disk
    // ?MAYBE: Mark user for deletion?
    std::filesystem::remove(getUserConfigurationFilePath(user_uid));
    saveUserNamesToDisk();
}

void UsersCatalog::updatePassword(Common::CppExtensions::Types::UniqueID const& user_uid, std::string new_password)
{
    // 1. Get user internal data
    auto& user{getUser(user_uid)};

    // 2. WriteAheadLog
    // TODO: Provide implementation

    // 3. Update user internal data
    user.password = std::move(new_password);

    // 4. Save user to disk
    saveUserToDisk(user);
}

void UsersCatalog::updatePermission(
    Common::CppExtensions::Types::UniqueID const& user_uid,
    Configuration::PermissionUpdate permission)
{
    assert(
        permission.update_type != Configuration::EPermissionUpdateType::Unknown &&
        "Error, 'Unknown' update type issued");

    // 1. Get user internal data
    auto& user{getUser(user_uid)};

    // 2. WriteAheadLog
    // TODO: Provide implementation

    // 3. Update user internal data
    switch (permission.update_type)
    {
    case Configuration::EPermissionUpdateType::Grant:
        std::ignore = user.permissions.emplace(std::move(permission.data));
        break;
    case Configuration::EPermissionUpdateType::Revoke:
        std::ignore = user.permissions.erase(permission.data);
        break;
    default:
        break;
    }

    // 4. Save user to disk
    saveUserToDisk(user);
}

bool UsersCatalog::userHasPermission(
    Common::CppExtensions::Types::UniqueID const& user_uid,
    Configuration::Permission const& permission)
{
    auto const& user{getUser(user_uid)};
    return user.permissions.find(permission) != user.permissions.end();
}

std::pair<Configuration::EAuthState, Authentication::AuthKey> authenticateUser(
    std::string_view username,
    std::string_view password)
{
    // TODO: Provide implementation
    throw std::runtime_error{"Not implemented yet..."};
}

bool UsersCatalog::isUserAuthenticated(
    Common::CppExtensions::Types::UniqueID const& user_uid,
    Authentication::AuthKey const& auth_key) const
{
    auto const it = m_authenticated_users.find(user_uid);
    return it != m_authenticated_users.end() && it->second == auth_key;
}

void UsersCatalog::deauthenticateUser(Common::CppExtensions::Types::UniqueID const& user_uid)
{
    std::ignore = m_authenticated_users.erase(user_uid);
}

std::filesystem::path UsersCatalog::getUsersHomePath() const
{
    auto const c_users_home_path{
        Selenity::API::SystemCatalog::Instance().getLunarHomePath() / "users"};

    if (!std::filesystem::exists(c_users_home_path))
    {
        std::filesystem::create_directories(c_users_home_path);
    }

    return c_users_home_path;
}

std::filesystem::path UsersCatalog::getUserConfigurationFilePath(
    Common::CppExtensions::Types::UniqueID user_uid) const
{
    return getUsersHomePath() / (user_uid.toString() + ".cfg");
}

void UsersCatalog::saveUserToDisk(Configuration::User const& user) const
{
    // TODO: WriteAheadLog

    namespace Serializer = Common::CppExtensions::BinaryIO::Serializer;

    std::ofstream user_file(getUserConfigurationFilePath(user.uid), std::ios::trunc | std::ios::binary);

    auto const encrypted_password{Common::Cryptography::AES256::Instance().encrypt(
        Common::Cryptography::AES256::ByteArray(user.password.begin(), user.password.end()))};

    Serializer::serialize(user_file, user.name);
    Serializer::serialize(user_file, encrypted_password);
    Serializer::serialize(user_file, user.permissions);

    user_file.close();
}

Configuration::User UsersCatalog::loadUserFromDisk(Common::CppExtensions::Types::UniqueID user_uid)
{
    namespace Deserializer = Common::CppExtensions::BinaryIO::Deserializer;

    auto const user_file_path{getUserConfigurationFilePath(user_uid)};

    if (!std::filesystem::exists(user_file_path))
    {
        throw std::runtime_error(Common::CppExtensions::StringUtils::stringify(
            "Configuration file for user '", user_uid, "' missing"));
    }

    std::ifstream user_file(getUserConfigurationFilePath(user_uid), std::ios::binary);

    Configuration::User user{};
    user.uid = std::move(user_uid);

    auto encrypted_password{Common::Cryptography::AES256::ByteArray{}};

    Deserializer::deserialize(user_file, user.name);
    Deserializer::deserialize(user_file, encrypted_password);
    Deserializer::deserialize(user_file, user.permissions);

    auto const decrypted_password{Common::Cryptography::AES256::Instance().decrypt(encrypted_password)};
    user.password = std::string(decrypted_password.begin(), decrypted_password.end());

    user_file.close();

    return user;
}

Configuration::User& UsersCatalog::getUser(Common::CppExtensions::Types::UniqueID user_uid)
{
    if (auto user_it = m_users.find(user_uid); user_it != m_users.end())
    {
        return user_it->second;
    }
    else
    {
        return m_users.emplace(user_uid, loadUserFromDisk(user_uid)).first->second;
    }
}

std::filesystem::path UsersCatalog::getUsernamesFilePath() const
{
    return getUsersHomePath() / "usernames.db";
}

void UsersCatalog::saveToDisk() const
{
    // save usernames
    saveUserNamesToDisk();
}

void UsersCatalog::loadFromDisk()
{
    // load usernames
    if (!std::filesystem::exists(getUsernamesFilePath()))
    {
        saveUserNamesToDisk();
    }
    else
    {
        std::ifstream usernames_file(getUsernamesFilePath(), std::ios::binary);
        m_usernames.clear();
        Common::CppExtensions::BinaryIO::Deserializer::deserialize(usernames_file, m_usernames);
        usernames_file.close();
    }
}

void UsersCatalog::saveUserNamesToDisk() const
{
    std::ofstream usernames_file(getUsernamesFilePath(), std::ios::trunc | std::ios::binary);
    Common::CppExtensions::BinaryIO::Serializer::serialize(usernames_file, m_usernames);
    usernames_file.close();
}

UsersCatalog::~UsersCatalog()
{
    saveToDisk();
}

} // namespace LunarDB::Celestial::API
