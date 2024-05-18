#include <gtest/gtest.h>

#include "LunarDB/Common/CppExtensions/testing/TempFileSystemGuards.hpp"
#include "LunarDB/Common/QueryData/helpers/Init.hpp"
#include "LunarDB/Selenity/private/helpers/Operators.hpp"
#include "QueryExecutors.hpp"

namespace LunarDB::Astral::Tests {

using TempDirectoryGuard = Common::CppExtensions::Testing::TempFileSystemGuards::TempDirectoryGuard;

TEST(Astral_DatabaseExecutorTest, create_drop_use)
{
    // 1. setup
    TempDirectoryGuard const c_lunar_home{
        Selenity::API::SystemCatalog::Instance().getLunarHomePath().string()};
    auto& catalog{Selenity::API::SystemCatalog::Instance()};

    // 2. create database
    auto parsed_query = Moonlight::API::ParsedQuery::make<Common::QueryData::Database>();
    parsed_query.get<Common::QueryData::Database>() =
        Common::QueryData::Init::DatabaseInit{}
            .name("some_name")
            .operation_type(Common::QueryData::Primitives::EDatabaseOperationType::Create);

    Astral::Implementation::Database::execute(parsed_query);

    ASSERT_TRUE(catalog.getConfigs().size() == 1);
    auto const database_home_path = catalog.getConfigs()[0].getHomePath();
    EXPECT_TRUE(std::filesystem::exists(database_home_path));

    // 3. use existing database
    parsed_query.get<Common::QueryData::Database>() =
        Common::QueryData::Init::DatabaseInit{}
            .name("some_name")
            .operation_type(Common::QueryData::Primitives::EDatabaseOperationType::Use);

    Astral::Implementation::Database::execute(parsed_query);

    EXPECT_TRUE(catalog.usingDatabase());

    // 4. use non existing database
    parsed_query.get<Common::QueryData::Database>() =
        Common::QueryData::Init::DatabaseInit{}
            .name("some_non_existing_database")
            .operation_type(Common::QueryData::Primitives::EDatabaseOperationType::Use);

    EXPECT_THROW({ Astral::Implementation::Database::execute(parsed_query); }, std::runtime_error);

    // 5. load catalog from disk, check if configs saved
    auto const old_cfgs = Selenity::API::SystemCatalog::Instance().getConfigs();
    catalog.loadFromDisk();
    auto const new_cfgs = Selenity::API::SystemCatalog::Instance().getConfigs();

    EXPECT_EQ(old_cfgs, new_cfgs);

    // 6. throw when creating same database
    EXPECT_THROW({ Astral::Implementation::Database::execute(parsed_query); }, std::runtime_error);

    // 7. drop database
    parsed_query.get<Common::QueryData::Database>() =
        Common::QueryData::Init::DatabaseInit{}
            .name("some_name")
            .operation_type(Common::QueryData::Primitives::EDatabaseOperationType::Drop);

    Astral::Implementation::Database::execute(parsed_query);

    ASSERT_TRUE(catalog.getConfigs().empty());
    EXPECT_FALSE(std::filesystem::exists(database_home_path));

    // 8. throw when dropping same database
    EXPECT_THROW({ Astral::Implementation::Database::execute(parsed_query); }, std::runtime_error);
}

} // namespace LunarDB::Astral::Tests
