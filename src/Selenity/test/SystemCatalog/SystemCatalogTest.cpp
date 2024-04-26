#include <fstream>
#include <gtest/gtest.h>

#include "Common/CppExtensions/BinaryIO.hpp"
#include "Common/CppExtensions/testing/TempFileSystemGuards.hpp"
#include "Selenity/SystemCatalog.hpp"

#define AS_STRING_(x) #x
#define AS_STRING(x) AS_STRING_(x)
#define TEMP_HOME_PATH "/tmp/lunardb_" AS_STRING(__LINE__) "_tmp_home"

namespace std {

std::ostream& operator<<(
    std::ostream& os,
    LunarDB::Selenity::Implementation::SystemCatalog::DatabaseConfig const& rhs)
{
    os << "storage_path: " << rhs.storage_path() << ", name: " << rhs.name();
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> const& rhs)
{
    os << "[ ";
    std::for_each(std::begin(rhs), std::end(rhs), [&os](auto const& value) { os << value << ", "; });
    os << " ]";
    return os;
}

std::ostream& operator<<(std::ostream& os, LunarDB::Selenity::API::SystemCatalog const& rhs)
{
    os << "lunar_home: " << rhs.lunar_home() << ", configs: " << rhs.configs();
    return os;
}

} // namespace std

namespace LunarDB::Selenity::API::Tests {

using TempDirectoryGuard = Common::CppExtensions::Testing::TempFileSystemGuards::TempDirectoryGuard;

TEST(Selenity_SystemCatalog_SystemCatalogTest, createDatabase)
{
    TempDirectoryGuard const c_lunar_home{TEMP_HOME_PATH};

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
