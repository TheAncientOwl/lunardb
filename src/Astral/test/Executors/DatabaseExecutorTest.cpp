#include <gtest/gtest.h>

#include "LunarDB/Common/CppExtensions/testing/TempFileSystemGuards.hpp"
#include "LunarDB/Common/QueryData/helpers/Init.hpp"
#include "LunarDB/Selenity/private/SystemCatalog/helpers/Operators.hpp"
#include "QueryExecutors.hpp"

namespace LunarDB::Astral::Tests {

using TempDirectoryGuard = Common::CppExtensions::Testing::TempFileSystemGuards::TempDirectoryGuard;

TEST(Astral_DatabaseExecutorTest, create_drop_use)
{
    // 1. setup
    TempDirectoryGuard const c_lunar_home{TEMP_LUNAR_HOME_PATH};
    Selenity::API::SystemCatalog catalog{c_lunar_home};
    API::SelenityDependencies deps{catalog};

    // 2. create database
    auto parsed_query = Moonlight::API::ParsedQuery::make<QueryData::Database>();
    parsed_query.get<QueryData::Database>() =
        QueryData::Init::DatabaseInit{}
            .name("some_name")
            .operation_type(QueryData::Primitives::EDatabaseOperationType::Create);

    Astral::Implementation::Database::execute(parsed_query, deps);

    ASSERT_TRUE(catalog.configs().size() == 1);
    auto const database_storage_path = catalog.configs()[0].storage_path();
    EXPECT_TRUE(std::filesystem::exists(database_storage_path));

    // 3. use existing database
    parsed_query.get<QueryData::Database>() =
        QueryData::Init::DatabaseInit{}
            .name("some_name")
            .operation_type(QueryData::Primitives::EDatabaseOperationType::Use);

    Astral::Implementation::Database::execute(parsed_query, deps);

    EXPECT_TRUE(catalog.usingDatabase());

    // 4. use non existing database
    parsed_query.get<QueryData::Database>() =
        QueryData::Init::DatabaseInit{}
            .name("some_non_existing_database")
            .operation_type(QueryData::Primitives::EDatabaseOperationType::Use);

    EXPECT_THROW(
        { Astral::Implementation::Database::execute(parsed_query, deps); }, std::runtime_error);

    // 5. load catalog from disk, check if configs saved
    {
        Selenity::API::SystemCatalog in_catalog{c_lunar_home};
        in_catalog.loadFromDisk();

        EXPECT_TRUE(surfaceEquals(catalog, in_catalog))
            << "in_catalog: " << in_catalog << "\ncatalog: " << catalog;
    }

    // 6. throw when creating same database
    EXPECT_THROW(
        { Astral::Implementation::Database::execute(parsed_query, deps); }, std::runtime_error);

    // 7. drop database
    parsed_query.get<QueryData::Database>() =
        QueryData::Init::DatabaseInit{}
            .name("some_name")
            .operation_type(QueryData::Primitives::EDatabaseOperationType::Drop);

    Astral::Implementation::Database::execute(parsed_query, deps);

    ASSERT_TRUE(catalog.configs().empty());
    EXPECT_FALSE(std::filesystem::exists(database_storage_path));

    // 8. throw when dropping same database
    EXPECT_THROW(
        { Astral::Implementation::Database::execute(parsed_query, deps); }, std::runtime_error);
}

} // namespace LunarDB::Astral::Tests
