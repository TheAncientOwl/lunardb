#include <gtest/gtest.h>

#include "LunarDB/Celestial/UsersCatalog.hpp"
#include "LunarDB/Common/CppExtensions/Testing/TempLunarHomeGuard.hpp"
#include "LunarDB/Common/QueryData/helpers/Init.hpp"
#include "LunarDB/Selenity/SchemasCatalog.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"
#include "QueryExecutors.hpp"

using namespace std::string_literals;

namespace LunarDB::Astral::Tests {

TEST(Astral_RevokeExecutorTest, revoke)
{
    LunarDB::Common::Testing::TempLunarHomeGuard _{};

    // 1. System setup
    auto& system_catalog{Selenity::API::SystemCatalog::Instance()};
    auto& users_catalog{Celestial::API::UsersCatalog::Instance()};

    auto const c_database_name{"SomeDatabase"s};
    system_catalog.createDatabase(c_database_name);
    system_catalog.useDatabase(c_database_name);

    auto database_in_use{system_catalog.getDatabaseInUse()};
    ASSERT_TRUE(database_in_use != nullptr);
    auto const c_database_in_use_uid{database_in_use->getUID()};

    auto const c_collection_name{"SomeCollection"s};
    auto const c_schema_name{"SomeSchema"};
    std::vector<Common::QueryData::Create::Single::Binding> c_bindings{};
    auto const c_structure_type{Common::QueryData::Primitives::EStructureType::Collection};
    auto const c_schema{Common::QueryData::Init::SchemaInit{}
                            .name(c_schema_name)
                            .fields({Common::QueryData::Init::SchemaInit::FieldInit{}
                                         .array(false)
                                         .name("Field1")
                                         .nullable(false)
                                         .type("String")})};
    Selenity::API::SchemasCatalog::Instance().createSchema(c_schema);
    database_in_use->createCollection(c_collection_name, c_schema_name, c_structure_type, c_bindings);
    auto const c_collection_uid{database_in_use->getCollection(c_collection_name)->getUID()};

    auto const c_username{"SomeUsername"s};
    auto const c_password{"SomePassword"s};
    auto const c_user_uid{users_catalog.createUser(c_username, c_password)};

    ASSERT_TRUE(std::filesystem::exists(system_catalog.getLunarHomePath()));
    ASSERT_TRUE(std::filesystem::exists(users_catalog.getUsersHomePath()));
    ASSERT_TRUE(std::filesystem::exists(users_catalog.getUsernamesFilePath()));
    ASSERT_TRUE(std::filesystem::exists(users_catalog.getUserConfigurationFilePath(c_user_uid)));

    {
        // grant permissions
        auto parsed_query = Moonlight::API::ParsedQuery::make<Common::QueryData::Grant>();
        parsed_query.get<Common::QueryData::Grant>() =
            Common::QueryData::Init::GrantInit{}
                .to_user(c_username)
                .structure_name(c_collection_name)
                .permissions(std::vector<Common::QueryData::Primitives::EUserPermissionType>{
                    Common::QueryData::Primitives::EUserPermissionType::Insert,
                    Common::QueryData::Primitives::EUserPermissionType::Select,
                    Common::QueryData::Primitives::EUserPermissionType::Update});

        EXPECT_NO_THROW({ Astral::Implementation::Grant::execute(parsed_query); });
    }

    // 2. Testing
    auto parsed_query = Moonlight::API::ParsedQuery::make<Common::QueryData::Revoke>();
    parsed_query.get<Common::QueryData::Revoke>() =
        Common::QueryData::Init::RevokeInit{}
            .from_user(c_username)
            .structure_name(c_collection_name)
            .permissions(std::vector<Common::QueryData::Primitives::EUserPermissionType>{
                Common::QueryData::Primitives::EUserPermissionType::Insert,
                Common::QueryData::Primitives::EUserPermissionType::Update});

    EXPECT_NO_THROW({ Astral::Implementation::Revoke::execute(parsed_query); });
    EXPECT_NO_THROW({ Astral::Implementation::Revoke::execute(parsed_query); });

    EXPECT_NO_THROW({
        EXPECT_TRUE(users_catalog.userHasPermission(
            c_user_uid,
            Celestial::API::Configuration::Permission{
                Common::QueryData::Primitives::EUserPermissionType::Select,
                c_database_in_use_uid,
                c_collection_uid}));
    });

    EXPECT_NO_THROW({
        EXPECT_FALSE(users_catalog.userHasPermission(
            c_user_uid,
            Celestial::API::Configuration::Permission{
                Common::QueryData::Primitives::EUserPermissionType::Insert,
                c_database_in_use_uid,
                c_collection_uid}));
    });
    EXPECT_NO_THROW({
        EXPECT_FALSE(users_catalog.userHasPermission(
            c_user_uid,
            Celestial::API::Configuration::Permission{
                Common::QueryData::Primitives::EUserPermissionType::Update,
                c_database_in_use_uid,
                c_collection_uid}));
    });
    EXPECT_NO_THROW({
        EXPECT_FALSE(users_catalog.userHasPermission(
            c_user_uid,
            Celestial::API::Configuration::Permission{
                Common::QueryData::Primitives::EUserPermissionType::Create,
                c_database_in_use_uid,
                c_collection_uid}));
    });
    EXPECT_NO_THROW({
        EXPECT_FALSE(users_catalog.userHasPermission(
            c_user_uid,
            Celestial::API::Configuration::Permission{
                Common::QueryData::Primitives::EUserPermissionType::Delete,
                c_database_in_use_uid,
                c_collection_uid}));
    });
}

} // namespace LunarDB::Astral::Tests
