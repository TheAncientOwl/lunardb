#include <gtest/gtest.h>

#include "LunarDB/Common/CppExtensions/Testing/TempLunarHomeGuard.hpp"
#include "LunarDB/Common/QueryData/helpers/Init.hpp"
#include "LunarDB/Common/QueryData/helpers/Operators.hpp"
#include "LunarDB/Moonlight/ParsedQuery.hpp"
#include "LunarDB/Selenity/SchemasCatalog.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"
#include "QueryExecutors.hpp"

using namespace std::string_literals;

namespace LunarDB::Astral::Tests {

TEST(Astral_DropExecutorTest, drop)
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
    auto create_parsed_query = Moonlight::API::ParsedQuery::make<Common::QueryData::Create>();
    create_parsed_query.get<Common::QueryData::Create>() =
        Init::CreateInit{}
            .is_volatile(false)
            .structure_type(c_structure_type)
            .single(Init::CreateInit::SingleInit{}
                        .structure_name("SomeCollection")
                        .schema_name(c_schema.name)
                        .bindings(c_bindings)
                        .blended(false))
            .multiple(std::nullopt);
    EXPECT_NO_THROW({ Astral::Implementation::Create::execute(create_parsed_query); });
    EXPECT_THROW({ Astral::Implementation::Create::execute(create_parsed_query); }, std::runtime_error);

    auto drop_parsed_query = Moonlight::API::ParsedQuery::make<Common::QueryData::Drop>();
    drop_parsed_query.get<Common::QueryData::Drop>() =
        Init::DropInit{}.structure_name(c_collection_name).cascade(false);
    EXPECT_NO_THROW({ Astral::Implementation::Drop::execute(drop_parsed_query); });
    EXPECT_THROW({ Astral::Implementation::Drop::execute(drop_parsed_query); }, std::runtime_error);

    std::shared_ptr<Selenity::API::Managers::DatabaseManager> manager{nullptr};
    EXPECT_NO_THROW({ manager = system_catalog.getDatabaseInUse(); });
    EXPECT_THROW({ manager->getCollection(c_collection_name); }, std::runtime_error);
}

} // namespace LunarDB::Astral::Tests
