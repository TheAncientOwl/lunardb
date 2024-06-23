#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>

#include "LunarDB/Celestial/Authentication.hpp"
#include "LunarDB/Celestial/Configuration.hpp"
#include "LunarDB/Common/CppExtensions/BinaryIO.hpp"
#include "LunarDB/Common/CppExtensions/Singleton.hpp"

namespace LunarDB::Celestial::API {

class UsersCatalog : public Common::CppExtensions::DesignPatterns::Singleton<UsersCatalog>
{
public: // public API
    ///
    /// @brief Self explanatory
    /// @param user
    /// @param password
    ///
    Common::CppExtensions::UniqueID createUser(std::string username, std::string password);

    ///
    /// @brief Self explanatory
    /// @param user_uid
    ///
    void removeUser(Common::CppExtensions::UniqueID const& user_uid);

    ///
    /// @brief Self explanatory
    /// @param user_uid
    /// @param new_password
    ///
    void updatePassword(Common::CppExtensions::UniqueID const& user_uid, std::string new_password);

    ///
    /// @brief Self explanatory
    /// @param user_uid
    /// @param permission
    ///
    void updatePermission(
        Common::CppExtensions::UniqueID const& user_uid,
        Configuration::PermissionUpdate permission);

    ///
    /// @brief Self explanatory
    /// @param user_uid
    /// @param permission
    /// @return true if the use has permission, false otherwise
    ///
    bool userHasPermission(
        Common::CppExtensions::UniqueID const& user_uid,
        Configuration::Permission const& permission);

    ///
    /// @brief Self explanatory
    /// @param username
    /// @param password
    /// @return {authentication operation state, auth key to send to the user}
    ///
    std::pair<Configuration::EAuthState, Authentication::AuthKey> authenticateUser(
        std::string const& username,
        std::string_view password);

    ///
    /// @brief Self explanatory
    /// @param user_uid
    /// @return true if user authenticated, false otherwise
    ///
    bool isUserAuthenticated(
        Common::CppExtensions::UniqueID const& user_uid,
        Authentication::AuthKey const& auth_key) const;

    ///
    /// @brief Self explanatory
    /// @param user_uid
    ///
    void deauthenticateUser(Common::CppExtensions::UniqueID const& user_uid);

    ///
    /// @brief Self explanatory
    /// @param username
    /// @return
    ///
    Common::CppExtensions::UniqueID getUserUID(std::string const& username) const;

    ~UsersCatalog();

    ///
    /// @brief Self explanatory
    ///
    std::filesystem::path getUsersHomePath() const;

    ///
    /// @brief Self explanatory
    /// @param user_uid
    ///
    std::filesystem::path getUserConfigurationFilePath(Common::CppExtensions::UniqueID user_uid) const;

    ///
    /// @brief Self explanatory
    ///
    std::filesystem::path getUsernamesFilePath() const;

    void setRootPassword(std::string root_password);

    std::string_view getRootPassword() const;

    Configuration::User const& getUserConfiguration(std::string const& username);

private: // singleton
    LUNAR_SINGLETON_INIT(UsersCatalog);

private: // private API
    ///
    /// @brief Self explanatory
    /// @note Data encryption
    ///
    void loadFromDisk();

    ///
    /// @brief Self explanatory
    /// @note Data encryption
    ///
    void saveToDisk() const;

    ///
    /// @brief Self explanatory
    ///
    void saveUserNamesToDisk() const;

    ///
    /// @brief Self explanatory
    /// @note Data encryption
    /// @param user
    ///
    void saveUserToDisk(Configuration::User const& user) const;

    ///
    /// @brief Self explanatory
    /// @note Data encryption
    /// @param path
    /// @return User configuration if user found
    /// @throw std::runtime_error if user not found
    ///
    Configuration::User loadUserFromDisk(std::filesystem::path const& user_file_path);

    ///
    /// @brief Self explanatory
    /// @note Data encryption
    /// @param user_uid
    /// @return User configuration if user found
    /// @throw std::runtime_error if user not found
    ///
    Configuration::User loadUserFromDisk(Common::CppExtensions::UniqueID user_uid);

    ///
    /// @brief Self explanatory
    /// @note Strategy:
    ///     1. Look for user in internal structure
    ///     2. Look for user on disk
    ///     3. Throw if not found
    /// @param user_uid
    /// @return Reference to user in internal structure
    ///
    Configuration::User& getUserFromUID(Common::CppExtensions::UniqueID user_uid);

    ///
    /// @brief Self explanatory
    /// @note Strategy:
    ///     1. Get user UID
    ///     2. Call getUserFromName(UID)
    /// @param username
    /// @return Reference to user in internal structure
    ///
    Configuration::User& getUserFromName(std::string const& username);

private: // fields
    Common::CppExtensions::UniqueID::MapTo<Configuration::User> m_uid_to_config_cache;
    Common::CppExtensions::UniqueID::MapTo<Authentication::AuthKey> m_authenticated_users;
    std::unordered_map<std::string, Common::CppExtensions::UniqueID> m_name_to_uid;

    std::string m_root_password{""};
};

} // namespace LunarDB::Celestial::API
