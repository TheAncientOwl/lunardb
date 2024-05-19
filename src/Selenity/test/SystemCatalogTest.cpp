#include <fstream>
#include <gtest/gtest.h>

#include "LunarDB/Common/CppExtensions/BinaryIO.hpp"
#include "LunarDB/Common/CppExtensions/Testing/TempLunarHomeGuard.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"

using namespace std::string_literals;

namespace LunarDB::Selenity::API::Tests {

TEST(Selenity_SystemCatalog_SystemCatalogTest, create_drop)
{
    Common::Testing::TempLunarHomeGuard _{};

    // 1. setup
    auto& catalog{Selenity::API::SystemCatalog::Instance()};

    auto const c_database_name{"some_database"s};

    // 2. create database
    EXPECT_NO_THROW({ catalog.createDatabase(c_database_name); });
    EXPECT_NO_THROW({ catalog.useDatabase(c_database_name); });
    ASSERT_TRUE(catalog.getDatabaseInUse() != nullptr);
    auto const database_home_path = catalog.getDatabaseInUse()->getHomePath();

    EXPECT_TRUE(std::filesystem::exists(database_home_path));

    // 3. throw when using non existing database
    EXPECT_THROW({ catalog.useDatabase("non_existing_db"); }, std::runtime_error);

    // 3. use database
    EXPECT_NO_THROW({ catalog.useDatabase(c_database_name); });

    EXPECT_TRUE(catalog.usingDatabase());
    EXPECT_NO_THROW({ catalog.useDatabase(c_database_name); });
    EXPECT_TRUE(std::filesystem::exists(database_home_path));

    // 4. check if changes saved
    EXPECT_THROW({ catalog.createDatabase(c_database_name); }, std::runtime_error);
    EXPECT_NO_THROW({ catalog.useDatabase(c_database_name); });

    // 5. drop database
    EXPECT_NO_THROW({ catalog.dropDatabase(c_database_name); });

    EXPECT_FALSE(catalog.usingDatabase());
    EXPECT_THROW({ catalog.useDatabase(c_database_name); }, std::runtime_error);
    EXPECT_FALSE(std::filesystem::exists(database_home_path));

    // 6. check if changes saved
    EXPECT_THROW({ catalog.dropDatabase(c_database_name); }, std::runtime_error);
    EXPECT_THROW({ catalog.useDatabase(c_database_name); }, std::runtime_error);
}

} // namespace LunarDB::Selenity::API::Tests
