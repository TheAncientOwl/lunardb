#include <gtest/gtest.h>

#include "LunarDB/Common/CppExtensions/Testing/TempLunarHomeGuard.hpp"
#include "LunarDB/Common/QueryData/helpers/Init.hpp"
#include "LunarDB/Common/QueryData/helpers/Operators.hpp"
#include "LunarDB/Selenity/SchemasCatalog.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"

using namespace std::string_literals;

namespace LunarDB::Astral::Tests {

TEST(Astral_CreateExecutorTest, create)
{
    LunarDB::Common::Testing::TempLunarHomeGuard _{};

    auto const c_database_name{"somedatabase"s};

    auto& system_catalog{Selenity::API::SystemCatalog::Instance()};
    auto& schemas_catalog{Selenity::API::SchemasCatalog::Instance()};

    namespace Init = Common::QueryData::Init;
    Common::QueryData::Schema const c_schema =
        Init::SchemaInit{}
            .name("SomeSchema")
            .fields(std::vector<Common::QueryData::Schema::Field>{
                Init::SchemaInit::FieldInit{}.name("field_1").type("Rid").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_2").type("String").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_3").type("Boolean").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_4").type("DateTime").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_5").type("Integer").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_10").type("Float").nullable(false).array(false)});
    EXPECT_NO_THROW({ schemas_catalog.createSchema(c_schema); });
    EXPECT_NO_THROW({ schemas_catalog.createSchema(c_schema); });
    EXPECT_NO_THROW({ schemas_catalog.getSchema(c_schema.name); });

    EXPECT_NO_THROW({ system_catalog.createDatabase(c_database_name); });
    EXPECT_NO_THROW({ system_catalog.useDatabase(c_database_name); });

    std::shared_ptr<Selenity::API::Managers::DatabaseManager> manager{nullptr};
    EXPECT_NO_THROW({ manager = system_catalog.getDatabaseInUse(); });

    auto const c_collection_name{"SomeCollection"s};
    auto const c_structure_type{Common::QueryData::Primitives::EStructureType::Collection};
    auto const c_bindings{std::vector<Common::QueryData::Create::Single::Binding>{}};
    EXPECT_NO_THROW({
        manager->createCollection(c_collection_name, c_schema.name, c_structure_type, c_bindings);
    });
    EXPECT_THROW(
        {
            manager->createCollection(c_collection_name, c_schema.name, c_structure_type, c_bindings);
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

} // namespace LunarDB::Astral::Tests
