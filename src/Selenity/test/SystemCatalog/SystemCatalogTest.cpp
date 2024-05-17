#include <fstream>
#include <gtest/gtest.h>

#include "LunarDB/Common/CppExtensions/BinaryIO.hpp"
#include "LunarDB/Common/CppExtensions/testing/TempFileSystemGuards.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"
#include "LunarDB/Selenity/private/SystemCatalog/helpers/Operators.hpp"

namespace LunarDB::Selenity::API::Tests {

using TempDirectoryGuard = Common::CppExtensions::Testing::TempFileSystemGuards::TempDirectoryGuard;

TEST(Selenity_SystemCatalog_SystemCatalogTest, create_drop)
{
    // 1. setup
    TempDirectoryGuard const c_lunar_home{Selenity::API::SystemCatalog::Instance().getLunarHomePath()};

    auto& catalog{Selenity::API::SystemCatalog::Instance()};

    // 2. create database
    catalog.createDatabase("some_database");
    auto const database_storage_path = catalog.configs()[0].storage_path();
    catalog.saveToDisk();

    ASSERT_TRUE(catalog.configs().size() == 1);
    EXPECT_TRUE(std::filesystem::exists(database_storage_path));

    // 3. throw when using non existing database
    EXPECT_THROW({ catalog.useDatabase("non_existing_db"); }, std::runtime_error);

    // 3. use database
    catalog.useDatabase("some_database");
    EXPECT_TRUE(catalog.usingDatabase());

    // 4. check if changes saved
    {
        auto const old_cfgs = Selenity::API::SystemCatalog::Instance().configs();
        catalog.loadFromDisk();
        auto const new_cfgs = Selenity::API::SystemCatalog::Instance().configs();
    }

    // 5. throw when creating same database
    EXPECT_THROW({ catalog.createDatabase("some_database"); }, std::runtime_error);

    // 6. drop database
    catalog.dropDatabase("some_database");
    catalog.saveToDisk();

    ASSERT_TRUE(catalog.configs().empty());
    EXPECT_FALSE(std::filesystem::exists(database_storage_path));
    EXPECT_FALSE(catalog.usingDatabase());

    // 7. check if changes saved
    {
        auto const old_cfgs = Selenity::API::SystemCatalog::Instance().configs();
        catalog.loadFromDisk();
        auto const new_cfgs = Selenity::API::SystemCatalog::Instance().configs();
    }

    // 8. throw when dropping same database
    EXPECT_THROW({ catalog.dropDatabase("some_database"); }, std::runtime_error);
}

} // namespace LunarDB::Selenity::API::Tests
