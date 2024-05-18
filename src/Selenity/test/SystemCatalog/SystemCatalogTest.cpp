#include <fstream>
#include <gtest/gtest.h>

#include "LunarDB/Common/CppExtensions/BinaryIO.hpp"
#include "LunarDB/Common/CppExtensions/testing/TempFileSystemGuards.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"
#include "LunarDB/Selenity/private/helpers/Operators.hpp"

namespace LunarDB::Selenity::API::Tests {

using TempDirectoryGuard = Common::CppExtensions::Testing::TempFileSystemGuards::TempDirectoryGuard;

TEST(Selenity_SystemCatalog_SystemCatalogTest, create_drop)
{
    // 1. setup
    TempDirectoryGuard const c_lunar_home{Selenity::API::SystemCatalog::Instance().getLunarHomePath()};

    auto& catalog{Selenity::API::SystemCatalog::Instance()};

    // 2. create database
    catalog.createDatabase("some_database");
    auto const database_home_path = catalog.getConfigs()[0].getHomePath();
    catalog.saveToDisk();

    ASSERT_TRUE(catalog.getConfigs().size() == 1);
    EXPECT_TRUE(std::filesystem::exists(database_home_path));

    // 3. throw when using non existing database
    EXPECT_THROW({ catalog.useDatabase("non_existing_db"); }, std::runtime_error);

    // 3. use database
    catalog.useDatabase("some_database");
    EXPECT_TRUE(catalog.usingDatabase());

    // 4. check if changes saved
    {
        auto const old_cfgs = Selenity::API::SystemCatalog::Instance().getConfigs();
        catalog.loadFromDisk();
        auto const new_cfgs = Selenity::API::SystemCatalog::Instance().getConfigs();
    }

    // 5. throw when creating same database
    EXPECT_THROW({ catalog.createDatabase("some_database"); }, std::runtime_error);

    // 6. drop database
    catalog.dropDatabase("some_database");
    catalog.saveToDisk();

    ASSERT_TRUE(catalog.getConfigs().empty());
    EXPECT_FALSE(std::filesystem::exists(database_home_path));
    EXPECT_FALSE(catalog.usingDatabase());

    // 7. check if changes saved
    {
        auto const old_cfgs = Selenity::API::SystemCatalog::Instance().getConfigs();
        catalog.loadFromDisk();
        auto const new_cfgs = Selenity::API::SystemCatalog::Instance().getConfigs();
    }

    // 8. throw when dropping same database
    EXPECT_THROW({ catalog.dropDatabase("some_database"); }, std::runtime_error);
}

} // namespace LunarDB::Selenity::API::Tests
