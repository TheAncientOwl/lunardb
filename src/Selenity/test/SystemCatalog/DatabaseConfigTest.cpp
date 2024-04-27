#include <fstream>
#include <gtest/gtest.h>

#include "Common/CppExtensions/BinaryIO.hpp"
#include "Selenity/private/SystemCatalog/DatabaseConfig.hpp"
#include "Selenity/private/SystemCatalog/helpers/Ostream.hpp"

namespace LunarDB::Selenity::Implementation::SystemCatalog::Tests {

TEST(Selenity_SystemCatalog_DatabaseConfigTest, binary_io)
{
    auto const c_file{"/tmp/lunardb_test_db_config.ldb"};

    std::ofstream out(c_file, std::ios::binary);
    DatabaseConfig const out_config{"/tmp/lunardb/some_db_storage", "some_db"};
    Common::CppExtensions::BinaryIO::Serializer::serialize(out, out_config);
    out.close();

    std::ifstream in(c_file, std::ios::binary);
    DatabaseConfig in_config{};
    Common::CppExtensions::BinaryIO::Deserializer::deserialize(in, in_config);
    in.close();

    std::remove(c_file);

    EXPECT_EQ(out_config, in_config);
}

TEST(Selenity_SystemCatalog_DatabaseConfigTest, binary_io_setters)
{
    auto const c_file{"/tmp/lunardb_test_db_config.ldb"};

    std::ofstream out(c_file, std::ios::binary);
    DatabaseConfig out_config{"/tmp/lunardb/some_db_storage", "some_db"};
    out_config.setStoragePath("some/storage_path");
    out_config.setName("some_name");
    Common::CppExtensions::BinaryIO::Serializer::serialize(out, out_config);
    out.close();

    std::ifstream in(c_file, std::ios::binary);
    DatabaseConfig in_config{};
    Common::CppExtensions::BinaryIO::Deserializer::deserialize(in, in_config);
    in.close();

    std::remove(c_file);

    EXPECT_EQ(out_config, in_config);
}

} // namespace LunarDB::Selenity::Implementation::SystemCatalog::Tests
