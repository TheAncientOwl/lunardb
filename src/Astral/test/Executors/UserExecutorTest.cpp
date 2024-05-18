#include <gtest/gtest.h>

#include "LunarDB/Celestial/UsersCatalog.hpp"
#include "LunarDB/Common/QueryData/helpers/Init.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"
#include "QueryExecutors.hpp"

namespace LunarDB::Astral::Tests {

TEST(Astral_UserExecutorTest, create_remove)
{
    std::filesystem::remove_all("/tmp/lunardb");
    auto& users_catalog{Celestial::API::UsersCatalog::Instance()};

    auto parsed_query = Moonlight::API::ParsedQuery::make<Common::QueryData::User>();
    parsed_query.get<Common::QueryData::User>() =
        Common::QueryData::Init::UserInit{}
            .name("some_name")
            .action(Common::QueryData::Primitives::EUserActionType::Create)
            .password("passwd1234");

    EXPECT_NO_THROW({ Astral::Implementation::User::execute(parsed_query); });
    EXPECT_THROW({ Astral::Implementation::User::execute(parsed_query); }, std::runtime_error);

    auto const uid{users_catalog.getUserUID("some_name")};

    EXPECT_TRUE(std::filesystem::exists(users_catalog.getUsersHomePath()));
    EXPECT_TRUE(std::filesystem::exists(users_catalog.getUserConfigurationFilePath(uid)));
    EXPECT_TRUE(std::filesystem::exists(users_catalog.getUsernamesFilePath()));

    parsed_query.get<Common::QueryData::User>() =
        Common::QueryData::Init::UserInit{}
            .name("some_name")
            .action(Common::QueryData::Primitives::EUserActionType::Remove)
            .password(std::nullopt);
    Astral::Implementation::User::execute(parsed_query);
    EXPECT_THROW({ Astral::Implementation::User::execute(parsed_query); }, std::runtime_error);
    EXPECT_FALSE(std::filesystem::exists(users_catalog.getUserConfigurationFilePath(uid)));
}

} // namespace LunarDB::Astral::Tests
