#include <gtest/gtest.h>

#include "Common/CppExtensions/testing/TempFileSystemGuards.hpp"
#include "Common/QueryData/helpers/Init.hpp"
#include "QueryExecutors.hpp"
#include "Selenity/private/SystemCatalog/helpers/Ostream.hpp"

namespace LunarDB::Astral::Tests {

using TempDirectoryGuard = Common::CppExtensions::Testing::TempFileSystemGuards::TempDirectoryGuard;

TEST(Astral_DatabaseExecutorTest, create_drop)
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

    // 3. load catalog from disk, check if configs saved
    {
        Selenity::API::SystemCatalog in_catalog{c_lunar_home};
        in_catalog.loadFromDisk();

        EXPECT_EQ(catalog, in_catalog);
    }

    // 4. throw when creating same database
    EXPECT_THROW(
        { Astral::Implementation::Database::execute(parsed_query, deps); }, std::runtime_error);

    // 5. drop database
    parsed_query.get<QueryData::Database>() =
        QueryData::Init::DatabaseInit{}
            .name("some_name")
            .operation_type(QueryData::Primitives::EDatabaseOperationType::Drop);

    Astral::Implementation::Database::execute(parsed_query, deps);

    ASSERT_TRUE(catalog.configs().empty());
    EXPECT_FALSE(std::filesystem::exists(database_storage_path));

    // 6. throw when dropping same database
    EXPECT_THROW(
        { Astral::Implementation::Database::execute(parsed_query, deps); }, std::runtime_error);
}

} // namespace LunarDB::Astral::Tests
