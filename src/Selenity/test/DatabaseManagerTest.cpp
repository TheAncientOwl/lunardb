#include <fstream>
#include <gtest/gtest.h>

#include "LunarDB/Common/CppExtensions/BinaryIO.hpp"
#include "LunarDB/Common/CppExtensions/Testing/TempLunarHomeGuard.hpp"
#include "LunarDB/Common/CppExtensions/UniqueID.hpp"
#include "LunarDB/Common/QueryData/helpers/Init.hpp"
#include "LunarDB/Common/QueryData/helpers/Operators.hpp"
#include "LunarDB/Selenity/Managers/DatabaseManager.hpp"
#include "LunarDB/Selenity/SchemasCatalog.hpp"

using namespace std::string_literals;

namespace LunarDB::Selenity::API::Managers::Tests {

TEST(Selenity_SystemCatalog_DatabaseManagerTest, binary_io)
{
    LunarDB::Common::Testing::TempLunarHomeGuard _{};

    auto const c_database_name{"somedatabase"s};
    auto const c_home{"/tmp/lunardb/databases/somedatabase"s};

    auto const c_collection_type{Configurations::CollectionConfiguration::ECollectionType::Document};

    auto const database_config = std::make_shared<Configurations::DatabaseConfiguration>(
        c_database_name, c_home, LunarDB::Common::CppExtensions::UniqueID::generate());

    auto const c_collection_name{"SomeCollection"s};
    auto const c_schema1_name{"SomeSchema"};
    std::vector<Common::QueryData::Create::Single::Binding> c_bindings{};
    auto const c_structure_type{Common::QueryData::Primitives::EStructureType::Collection};
    auto const c_schema1{Common::QueryData::Init::SchemaInit{}
                             .name(c_schema1_name)
                             .fields({Common::QueryData::Init::SchemaInit::FieldInit{}
                                          .array(false)
                                          .name("Field1")
                                          .nullable(false)
                                          .type("String")})};
    EXPECT_NO_THROW({ Selenity::API::SchemasCatalog::Instance().createSchema(c_schema1); });
    EXPECT_NO_THROW({ Selenity::API::SystemCatalog::Instance().createDatabase(c_database_name); });
    EXPECT_NO_THROW({ Selenity::API::SystemCatalog::Instance().useDatabase(c_database_name); });

    DatabaseManager manager1{database_config};
    EXPECT_NO_THROW({
        manager1.createCollection(c_collection_name, c_schema1_name, c_structure_type, c_bindings);
    });
    EXPECT_THROW(
        {
            manager1.createCollection(c_collection_name, c_schema1_name, c_structure_type, c_bindings);
        },
        std::runtime_error);
    EXPECT_NO_THROW({ manager1.getCollection(c_collection_name); });
    EXPECT_THROW({ manager1.getCollection("random"); }, std::runtime_error);

    DatabaseManager manager2{database_config};
    EXPECT_EQ(manager1.getHomePath(), manager2.getHomePath());
    EXPECT_EQ(manager1.getUID(), manager2.getUID());
    EXPECT_EQ(manager1.getName(), manager2.getName());

    EXPECT_NO_THROW({ manager2.getCollection(c_collection_name); });
    EXPECT_THROW({ manager2.getCollection("random"); }, std::runtime_error);

    EXPECT_THROW(
        {
            manager2.createCollection(c_collection_name, c_schema1_name, c_structure_type, c_bindings);
        },
        std::runtime_error);
    EXPECT_NO_THROW({ manager2.dropCollection(c_collection_name); });
    EXPECT_THROW({ manager2.dropCollection(c_collection_name); }, std::runtime_error);

    DatabaseManager manager3{database_config};
    EXPECT_EQ(manager1.getHomePath(), manager3.getHomePath());
    EXPECT_EQ(manager1.getUID(), manager3.getUID());
    EXPECT_EQ(manager1.getName(), manager3.getName());

    EXPECT_THROW({ manager2.getCollection(c_collection_name); }, std::runtime_error);
    EXPECT_THROW({ manager2.getCollection("random"); }, std::runtime_error);

    EXPECT_THROW({ manager3.dropCollection(c_collection_name); }, std::runtime_error);
    EXPECT_NO_THROW({
        manager3.createCollection(c_collection_name, c_schema1_name, c_structure_type, c_bindings);
    });
}

TEST(Selenity_SystemCatalog_DatabaseManagerTest, collection)
{
    LunarDB::Common::Testing::TempLunarHomeGuard _{};

    auto const c_database_name{"somedatabase"s};

    auto& system_catalog{Selenity::API::SystemCatalog::Instance()};
    auto& schemas_catalog{Selenity::API::SchemasCatalog::Instance()};

    namespace Init = Common::QueryData::Init;
    Common::QueryData::Schema const c_schema1 =
        Init::SchemaInit{}
            .name("SomeSchema")
            .fields(std::vector<Common::QueryData::Schema::Field>{
                Init::SchemaInit::FieldInit{}.name("field_1").type("Rid").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_2").type("String").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_3").type("Boolean").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_4").type("DateTime").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_5").type("Integer").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_10").type("Float").nullable(false).array(false)});
    EXPECT_NO_THROW({ schemas_catalog.createSchema(c_schema1); });
    EXPECT_NO_THROW({ schemas_catalog.createSchema(c_schema1); });
    EXPECT_NO_THROW({ schemas_catalog.getSchema(c_schema1.name); });

    EXPECT_NO_THROW({ system_catalog.createDatabase(c_database_name); });
    EXPECT_NO_THROW({ system_catalog.useDatabase(c_database_name); });

    std::shared_ptr<Selenity::API::Managers::DatabaseManager> manager{nullptr};
    EXPECT_NO_THROW({ manager = system_catalog.getDatabaseInUse(); });

    auto const c_collection_name{"SomeCollection"s};
    auto const c_structure_type{Common::QueryData::Primitives::EStructureType::Collection};
    auto const c_bindings{std::vector<Common::QueryData::Create::Single::Binding>{}};
    EXPECT_NO_THROW({
        manager->createCollection(c_collection_name, c_schema1.name, c_structure_type, c_bindings);
    });
    EXPECT_THROW(
        {
            manager->createCollection(c_collection_name, c_schema1.name, c_structure_type, c_bindings);
        },
        std::runtime_error);
    EXPECT_NO_THROW({ manager->getCollection(c_collection_name); });

    manager->saveConfigs();

    auto const manager_copy{
        std::make_shared<Selenity::API::Managers::DatabaseManager>(manager->getConfig())};
    manager_copy->loadConfigs();
    EXPECT_NO_THROW({ manager_copy->getCollection(c_collection_name); });

    auto const& collection{manager->getCollection(c_collection_name)};
    auto const& collection_copy{manager_copy->getCollection(c_collection_name)};

    auto const& config{collection->getConfig()};
    auto const& config_copy{collection_copy->getConfig()};

    EXPECT_EQ(config->bindings, config_copy->bindings);
    EXPECT_EQ(config->collection_type, config_copy->collection_type);
    EXPECT_EQ(config->home, config_copy->home);
    EXPECT_EQ(config->name, config_copy->name);
    EXPECT_EQ(config->schema, config_copy->schema);
    EXPECT_EQ(config->uid, config_copy->uid);
}

TEST(Selenity_SystemCatalog_DatabaseManagerTest, rebind)
{
    LunarDB::Common::Testing::TempLunarHomeGuard _{};

    auto const c_database_name{"somedatabase"s};

    auto& system_catalog{Selenity::API::SystemCatalog::Instance()};
    auto& schemas_catalog{Selenity::API::SchemasCatalog::Instance()};

    EXPECT_NO_THROW({ system_catalog.createDatabase(c_database_name); });
    EXPECT_NO_THROW({ system_catalog.useDatabase(c_database_name); });

    std::shared_ptr<Selenity::API::Managers::DatabaseManager> database{nullptr};
    EXPECT_NO_THROW({ database = system_catalog.getDatabaseInUse(); });

    // create collection 1
    namespace Init = Common::QueryData::Init;
    Common::QueryData::Schema const c_schema1 =
        Init::SchemaInit{}
            .name("SomeSchema1")
            .fields(std::vector<Common::QueryData::Schema::Field>{
                Init::SchemaInit::FieldInit{}.name("field_1").type("Rid").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_2").type("String").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_3").type("Boolean").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_4").type("DateTime").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_5").type("Integer").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_10").type("Float").nullable(false).array(false)});
    EXPECT_NO_THROW({ schemas_catalog.createSchema(c_schema1); });
    EXPECT_NO_THROW({ schemas_catalog.createSchema(c_schema1); });
    EXPECT_NO_THROW({ schemas_catalog.getSchema(c_schema1.name); });

    auto const c_collection_name1{"SomeCollection1"s};
    auto const c_structure_type1{Common::QueryData::Primitives::EStructureType::Collection};
    auto const c_bindings1{std::vector<Common::QueryData::Create::Single::Binding>{}};

    EXPECT_NO_THROW({
        database->createCollection(c_collection_name1, c_schema1.name, c_structure_type1, c_bindings1);
    });

    // create collection 2
    namespace Init = Common::QueryData::Init;
    Common::QueryData::Schema const c_schema2 =
        Init::SchemaInit{}
            .name("SomeSchema2")
            .fields(std::vector<Common::QueryData::Schema::Field>{
                Init::SchemaInit::FieldInit{}.name("field_1").type("Rid").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_10").type("Float").nullable(false).array(false)});
    EXPECT_NO_THROW({ schemas_catalog.createSchema(c_schema2); });
    EXPECT_NO_THROW({ schemas_catalog.createSchema(c_schema2); });
    EXPECT_NO_THROW({ schemas_catalog.getSchema(c_schema2.name); });

    auto const c_collection_name2{"SomeCollection2"s};
    auto const c_structure_type2{Common::QueryData::Primitives::EStructureType::Collection};
    auto const c_bindings2{std::vector<Common::QueryData::Create::Single::Binding>{}};

    EXPECT_NO_THROW({
        database->createCollection(c_collection_name2, c_schema2.name, c_structure_type2, c_bindings2);
    });

    // rebind
    EXPECT_NO_THROW({ database->rebind(c_collection_name2, "field_1", c_collection_name1); });
}

} // namespace LunarDB::Selenity::API::Managers::Tests
