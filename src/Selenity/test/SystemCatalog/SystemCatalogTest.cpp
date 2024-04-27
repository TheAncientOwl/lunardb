#include <fstream>
#include <gtest/gtest.h>

#include "Common/CppExtensions/BinaryIO.hpp"
#include "Common/CppExtensions/testing/TempFileSystemGuards.hpp"
#include "Selenity/SystemCatalog.hpp"
#include "Selenity/private/SystemCatalog/helpers/Ostream.hpp"

namespace LunarDB::Selenity::API::Tests {

using TempDirectoryGuard = Common::CppExtensions::Testing::TempFileSystemGuards::TempDirectoryGuard;

TEST(Selenity_SystemCatalog_SystemCatalogTest, createDatabase)
{
    TempDirectoryGuard const c_lunar_home{TEMP_LUNAR_HOME_PATH};

    SystemCatalog out_catalog{c_lunar_home};

    out_catalog.createDatabase("some_database");
    ASSERT_TRUE(out_catalog.configs().size() == 1);
    EXPECT_TRUE(std::filesystem::exists(out_catalog.configs()[0].storage_path()));

    out_catalog.saveToDisk();

    SystemCatalog in_catalog{c_lunar_home};
    in_catalog.loadFromDisk();

    EXPECT_EQ(out_catalog, in_catalog);
}

} // namespace LunarDB::Selenity::API::Tests
