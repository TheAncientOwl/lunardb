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
    TempDirectoryGuard const c_lunar_home{TEMP_LUNAR_HOME_PATH};

    SystemCatalog out_catalog{c_lunar_home};

    // 2. create database
    out_catalog.createDatabase("some_database");
    auto const database_storage_path = out_catalog.configs()[0].storage_path();
    out_catalog.saveToDisk();

    ASSERT_TRUE(out_catalog.configs().size() == 1);
    EXPECT_TRUE(std::filesystem::exists(database_storage_path));

    // 3. throw when using non existing database
    EXPECT_THROW({ out_catalog.useDatabase("non_existing_db"); }, std::runtime_error);

    // 3. use database
    out_catalog.useDatabase("some_database");
    EXPECT_TRUE(out_catalog.usingDatabase());

    // 4. check if changes saved
    {
        SystemCatalog in_catalog{c_lunar_home};
        in_catalog.loadFromDisk();

        EXPECT_TRUE(surfaceEquals(out_catalog, in_catalog))
            << "in_catalog: " << in_catalog << "\nout_catalog: " << out_catalog;
    }

    // 5. throw when creating same database
    EXPECT_THROW({ out_catalog.createDatabase("some_database"); }, std::runtime_error);

    // 6. drop database
    out_catalog.dropDatabase("some_database");
    out_catalog.saveToDisk();

    ASSERT_TRUE(out_catalog.configs().empty());
    EXPECT_FALSE(std::filesystem::exists(database_storage_path));
    EXPECT_FALSE(out_catalog.usingDatabase());

    // 7. check if changes saved
    {
        SystemCatalog in_catalog{c_lunar_home};
        in_catalog.loadFromDisk();

        EXPECT_TRUE(surfaceEquals(out_catalog, in_catalog))
            << "in_catalog: " << in_catalog << "\nout_catalog: " << out_catalog;
    }

    // 8. throw when dropping same database
    EXPECT_THROW({ out_catalog.dropDatabase("some_database"); }, std::runtime_error);
}

} // namespace LunarDB::Selenity::API::Tests
