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
    EXPECT_NO_THROW({ Selenity::API::SchemasCatalog::Instance().createSchema(c_schema); });
    EXPECT_NO_THROW({ Selenity::API::SystemCatalog::Instance().createDatabase(c_database_name); });
    EXPECT_NO_THROW({ Selenity::API::SystemCatalog::Instance().useDatabase(c_database_name); });

    DatabaseManager manager1{database_config};
    EXPECT_NO_THROW({
        manager1.createCollection(c_collection_name, c_schema_name, c_structure_type, c_bindings);
    });
    EXPECT_THROW(
        {
            manager1.createCollection(c_collection_name, c_schema_name, c_structure_type, c_bindings);
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
            manager2.createCollection(c_collection_name, c_schema_name, c_structure_type, c_bindings);
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
        manager3.createCollection(c_collection_name, c_schema_name, c_structure_type, c_bindings);
    });
}

} // namespace LunarDB::Selenity::API::Managers::Tests
