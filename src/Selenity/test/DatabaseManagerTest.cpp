#include <fstream>
#include <gtest/gtest.h>

#include "LunarDB/Common/CppExtensions/BinaryIO.hpp"
#include "LunarDB/Common/CppExtensions/Testing/TempLunarHomeGuard.hpp"
#include "LunarDB/Selenity/DatabaseManager.hpp"

using namespace std::string_literals;

namespace LunarDB::Selenity::Implementation::Tests {

TEST(Selenity_SystemCatalog_DatabaseManagerTest, binary_io)
{
    LunarDB::Common::Testing::TempLunarHomeGuard _{};

    auto const c_name{"some_database"s};
    auto const c_home{"/tmp/lunardb/some_database"s};

    EXPECT_TRUE(false) << "Refactor when class implemented";

    // DatabaseManager out_manager{Common::CppExtensions::UniqueID::generate(), c_name, c_home};
    // out_manager.saveCatalogToDisk;
    // out_manager.saveCatalogTo(out_file);
    // out_file.close();

    // std::ifstream in_file(LUNAR_TESTING_HOME_PATH "/some_database.config", std::ios::binary);
    // DatabaseManager in_manager{};
    // in_manager.loadCatalogFrom(in_file);
    // in_file.close();

    // auto const c_collection_name{"some_collection"s};
    // EXPECT_EQ(out_manager.getHomePath(), in_manager.getHomePath());
    // EXPECT_EQ(out_manager.getUID(), in_manager.getUID());
    // EXPECT_EQ(out_manager.getName(), in_manager.getName());
    // EXPECT_THROW(
    //     { std::ignore = out_manager.getCollectionManager(c_collection_name); }, std::runtime_error);
    // EXPECT_THROW(
    //     { std::ignore = in_manager.getCollectionManager(c_collection_name); }, std::runtime_error);
}

} // namespace LunarDB::Selenity::Implementation::Tests
