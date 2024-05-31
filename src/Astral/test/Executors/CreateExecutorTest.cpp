#include <gtest/gtest.h>
#include <ranges>

#include "LunarDB/Common/CppExtensions/Testing/TempLunarHomeGuard.hpp"
#include "LunarDB/Common/QueryData/helpers/Init.hpp"
#include "LunarDB/Common/QueryData/helpers/Operators.hpp"
#include "LunarDB/Moonlight/ParsedQuery.hpp"
#include "LunarDB/Selenity/SchemasCatalog.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"
#include "QueryExecutors.hpp"

using namespace std::string_literals;

namespace LunarDB::Astral::Tests {

TEST(Astral_CreateExecutorTest, create)
{
    LunarDB::Common::Testing::TempLunarHomeGuard _{};

    auto const c_database_name{"somedatabase"s};

    auto& system_catalog{Selenity::API::SystemCatalog::Instance()};
    auto& schemas_catalog{Selenity::API::SchemasCatalog::Instance()};

    namespace Init = Common::QueryData::Init;
    Common::QueryData::Schema const c_schema =
        Init::SchemaInit{}
            .name("SomeSchema")
            .fields(std::vector<Common::QueryData::Schema::Field>{
                Init::SchemaInit::FieldInit{}.name("field_1").type("Rid").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_2").type("String").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_3").type("Boolean").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_4").type("DateTime").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_5").type("Integer").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_10").type("Float").nullable(false).array(false)});
    EXPECT_NO_THROW({ schemas_catalog.createSchema(c_schema); });
    EXPECT_NO_THROW({ schemas_catalog.createSchema(c_schema); });
    EXPECT_NO_THROW({ schemas_catalog.getSchema(c_schema.name); });

    EXPECT_NO_THROW({ system_catalog.createDatabase(c_database_name); });
    EXPECT_NO_THROW({ system_catalog.useDatabase(c_database_name); });

    auto const c_collection_name{"SomeCollection"s};
    auto const c_structure_type{Common::QueryData::Primitives::EStructureType::Collection};
    auto const c_bindings{std::vector<Common::QueryData::Create::Single::Binding>{}};
    auto parsed_query = Moonlight::API::ParsedQuery::make<Common::QueryData::Create>();
    parsed_query.get<Common::QueryData::Create>() =
        Init::CreateInit{}
            .is_volatile(false)
            .structure_type(c_structure_type)
            .single(Init::CreateInit::SingleInit{}
                        .structure_name("SomeCollection")
                        .schema_name(c_schema.name)
                        .bindings(c_bindings)
                        .blended(false))
            .multiple(std::nullopt);
    EXPECT_NO_THROW({ Astral::Implementation::Create::execute(parsed_query); });
    EXPECT_THROW({ Astral::Implementation::Create::execute(parsed_query); }, std::runtime_error);

    std::shared_ptr<Selenity::API::Managers::DatabaseManager> manager{nullptr};
    EXPECT_NO_THROW({ manager = system_catalog.getDatabaseInUse(); });
    EXPECT_NO_THROW({ manager->getCollection(c_collection_name); });
    auto const& collection{manager->getCollection(c_collection_name)};
    auto const& config{collection->getConfig()};

    EXPECT_TRUE(config->bindings.empty());
    EXPECT_EQ(
        config->collection_type,
        Selenity::API::Managers::Configurations::CollectionConfiguration::ECollectionType::Document);
    ASSERT_EQ(config->schema.fields.size(), c_schema.fields.size() + 1);
    EXPECT_FALSE(config->schema.fields[0].array);
    EXPECT_FALSE(config->schema.fields[0].nullable);
    EXPECT_EQ(config->schema.fields[0].name, "_rid"s);
    EXPECT_EQ(
        config->schema.fields[0].type, Selenity::API::Managers::Configurations::EFieldDataType::Rid);
    for (auto const index : std::ranges::iota_view{1u, config->schema.fields.size()})
    {
        auto const& config_field{config->schema.fields[index]};
        auto const& schema_field{c_schema.fields[index - 1]};

        EXPECT_EQ(config_field.array, schema_field.array);
        EXPECT_EQ(config_field.name, schema_field.name);
        EXPECT_EQ(config_field.nullable, schema_field.nullable);
    }
}

} // namespace LunarDB::Astral::Tests
