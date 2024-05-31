#include <fstream>
#include <gtest/gtest.h>

#include "LunarDB/Common/CppExtensions/BinaryIO.hpp"
#include "LunarDB/Common/CppExtensions/Testing/TempLunarHomeGuard.hpp"
#include "LunarDB/Common/CppExtensions/UniqueID.hpp"
#include "LunarDB/Selenity/Managers/DatabaseManager.hpp"

using namespace std::string_literals;

namespace LunarDB::Selenity::API::Managers::Tests {

TEST(Selenity_SystemCatalog_DatabaseManagerTest, binary_io)
{
    LunarDB::Common::Testing::TempLunarHomeGuard _{};

    auto const c_name{"somedatabase"s};
    auto const c_home{"/tmp/lunardb/some_database"s};

    auto const c_collection_name{"collection1"s};
    auto const c_collection_type{Configurations::CollectionConfiguration::ECollectionType::Document};

    auto const database_config = std::make_shared<Configurations::DatabaseConfiguration>(
        c_name, c_home, LunarDB::Common::CppExtensions::UniqueID::generate());

    DatabaseManager manager1{database_config};
    EXPECT_NO_THROW({ manager1.createCollection(c_collection_name, c_collection_type); });
    EXPECT_THROW(
        { manager1.createCollection(c_collection_name, c_collection_type); }, std::runtime_error);
    EXPECT_NO_THROW({ manager1.getCollection(c_collection_name); });
    EXPECT_THROW({ manager1.getCollection("random"); }, std::runtime_error);

    DatabaseManager manager2{database_config};
    EXPECT_EQ(manager1.getHomePath(), manager2.getHomePath());
    EXPECT_EQ(manager1.getUID(), manager2.getUID());
    EXPECT_EQ(manager1.getName(), manager2.getName());

    EXPECT_NO_THROW({ manager2.getCollection(c_collection_name); });
    EXPECT_THROW({ manager2.getCollection("random"); }, std::runtime_error);

    EXPECT_THROW(
        { manager2.createCollection(c_collection_name, c_collection_type); }, std::runtime_error);
    EXPECT_NO_THROW({ manager2.dropCollection(c_collection_name); });
    EXPECT_THROW({ manager2.dropCollection(c_collection_name); }, std::runtime_error);

    DatabaseManager manager3{database_config};
    EXPECT_EQ(manager1.getHomePath(), manager3.getHomePath());
    EXPECT_EQ(manager1.getUID(), manager3.getUID());
    EXPECT_EQ(manager1.getName(), manager3.getName());

    EXPECT_THROW({ manager2.getCollection(c_collection_name); }, std::runtime_error);
    EXPECT_THROW({ manager2.getCollection("random"); }, std::runtime_error);

    EXPECT_THROW({ manager3.dropCollection(c_collection_name); }, std::runtime_error);
    EXPECT_NO_THROW({ manager3.createCollection(c_collection_name, c_collection_type); });
}

} // namespace LunarDB::Selenity::API::Managers::Tests
