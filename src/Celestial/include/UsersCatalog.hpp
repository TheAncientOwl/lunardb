#pragma once

#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
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
    Common::CppExtensions::Types::UniqueID createUser(std::string username, std::string password);

    ///
    /// @brief Self explanatory
    /// @param user_uid
    ///
    void removeUser(Common::CppExtensions::Types::UniqueID const& user_uid);

    ///
    /// @brief Self explanatory
    /// @param user_uid
    /// @param new_password
    ///
    void updatePassword(Common::CppExtensions::Types::UniqueID const& user_uid, std::string new_password);

    ///
    /// @brief Self explanatory
    /// @param user_uid
    /// @param permission
    ///
    void updatePermission(
        Common::CppExtensions::Types::UniqueID const& user_uid,
        Configuration::PermissionUpdate permission);

    ///
    /// @brief Self explanatory
    /// @param user_uid
    /// @param permission
    /// @return true if the use has permission, false otherwise
    ///
    bool userHasPermission(
        Common::CppExtensions::Types::UniqueID const& user_uid,
        Configuration::Permission const& permission);

    ///
    /// @brief Self explanatory
    /// @param username
    /// @param password
    /// @return {authentication operation state, auth key to send to the user}
    ///
    std::pair<Configuration::EAuthState, Authentication::AuthKey> authenticateUser(
        std::string_view username,
        std::string_view password);

    ///
    /// @brief Self explanatory
    /// @param user_uid
    /// @return true if user authenticated, false otherwise
    ///
    bool isUserAuthenticated(
        Common::CppExtensions::Types::UniqueID const& user_uid,
        Authentication::AuthKey const& auth_key) const;

    ///
    /// @brief Self explanatory
    /// @param user_uid
    ///
    void deauthenticateUser(Common::CppExtensions::Types::UniqueID const& user_uid);

    ~UsersCatalog();

private: // singleton
    LUNAR_SINGLETON_INIT(UsersCatalog);

private: // private API
    ///
    /// @brief Self explanatory
    ///
    std::filesystem::path getUsersHomePath() const;

    ///
    /// @brief Self explanatory
    /// @param user_uid
    ///
    std::filesystem::path getUserConfigurationFilePath(Common::CppExtensions::Types::UniqueID user_uid) const;

    ///
    /// @brief Self explanatory
    ///
    std::filesystem::path getUsernamesFilePath() const;

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
    /// @param user_uid
    /// @return User configuration if user found
    /// @throw std::runtime_error if user not found
    ///
    Configuration::User loadUserFromDisk(Common::CppExtensions::Types::UniqueID user_uid);

    ///
    /// @brief Self explanatory
    /// @note Strategy:
    ///     1. Look for user in internal structure
    ///     2. Look for user on disk
    ///     3. Throw if not found
    /// @param user_uid
    /// @return Reference to user in internal structure
    ///
    Configuration::User& getUser(Common::CppExtensions::Types::UniqueID user_uid);

private: // fields
    template <typename Value>
    using UniqueIDMap =
        std::unordered_map<Common::CppExtensions::Types::UniqueID, Value, Common::CppExtensions::Types::UniqueID::Hash>;

    UniqueIDMap<Configuration::User> m_users;
    UniqueIDMap<Authentication::AuthKey> m_authenticated_users;
    std::unordered_set<std::string> m_usernames;
};

} // namespace LunarDB::Celestial::API
