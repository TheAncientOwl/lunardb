#include <gtest/gtest.h>

#include <filesystem>

#include "LunarDB/Common/CppExtensions/Testing/LunarTestGuard.hpp"
#include "LunarDB/Common/QueryData/QueryData.hpp"
#include "LunarDB/Common/QueryData/helpers/Init.hpp"
#include "LunarDB/Selenity/SchemasCatalog.hpp"
#include "QueryExecutors.hpp"

using namespace std::string_literals;

namespace LunarDB::Astral::Tests {

TEST(Astral_SchemaExecutorTest, create_schema)
{
    LunarDB::Common::Testing::LunarTestGuard _{};

    auto& schemas_catalog{Selenity::API::SchemasCatalog::Instance()};

    auto const c_schema1_name{"SomeSchema1"s};
    auto const c_schema2_name{"SomeSchema2"s};

    namespace Init = Common::QueryData::Init;

    auto parsed_query = Moonlight::API::ParsedQuery::make<Common::QueryData::Schema>();

    parsed_query.get<Common::QueryData::Schema>() =
        Init::SchemaInit{}
            .name(c_schema1_name)
            .fields(std::vector<Common::QueryData::Schema::Field>{
                Init::SchemaInit::FieldInit{}.name("field_1").type("Rid").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_2").type("String").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_3").type("Boolean").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_4").type("DateTime").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_5").type("Integer").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_6").type("Integer8").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_7").type("Integer16").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_8").type("Integer32").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_9").type("Integer64").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_10").type("Float").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_11").type("Float32").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_12").type("Float64").nullable(false).array(false)});

    EXPECT_NO_THROW({ Astral::Implementation::Schema::execute(parsed_query); });
    EXPECT_NO_THROW({ Astral::Implementation::Schema::execute(parsed_query); });
    EXPECT_NO_THROW({ Astral::Implementation::Schema::execute(parsed_query); });
    EXPECT_NO_THROW({ std::ignore = schemas_catalog.getSchema(c_schema1_name); });
    EXPECT_NO_THROW({ std::ignore = schemas_catalog.getSchema(c_schema1_name); });
    EXPECT_NO_THROW({ std::ignore = schemas_catalog.getSchema(c_schema1_name); });
    EXPECT_NO_THROW({
        EXPECT_TRUE(std::filesystem::exists(schemas_catalog.getSchemaFilePath(c_schema1_name)));
    });

    parsed_query.get<Common::QueryData::Schema>() =
        Init::SchemaInit{}
            .name(c_schema1_name)
            .fields(std::vector<Common::QueryData::Schema::Field>{
                Init::SchemaInit::FieldInit{}.name("field_1").type("Rid").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_2").type("String").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_3").type("Boolean").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_4").type("DateTime").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_10").type("Float").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_11").type("Float32").nullable(false).array(false),
                Init::SchemaInit::FieldInit{}.name("field_12").type("Float64").nullable(false).array(false)});

    EXPECT_NO_THROW({ Astral::Implementation::Schema::execute(parsed_query); });
    EXPECT_NO_THROW({ Astral::Implementation::Schema::execute(parsed_query); });
    EXPECT_NO_THROW({ Astral::Implementation::Schema::execute(parsed_query); });
    EXPECT_NO_THROW({ std::ignore = schemas_catalog.getSchema(c_schema1_name); });
    EXPECT_NO_THROW({ std::ignore = schemas_catalog.getSchema(c_schema1_name); });
    EXPECT_NO_THROW({ std::ignore = schemas_catalog.getSchema(c_schema1_name); });
    EXPECT_NO_THROW({
        EXPECT_TRUE(std::filesystem::exists(schemas_catalog.getSchemaFilePath(c_schema1_name)));
    });

    EXPECT_THROW({ std::ignore = schemas_catalog.getSchema(c_schema2_name); }, std::runtime_error);
    EXPECT_THROW({ std::ignore = schemas_catalog.getSchema(c_schema2_name); }, std::runtime_error);
    EXPECT_THROW({ std::ignore = schemas_catalog.getSchema(c_schema2_name); }, std::runtime_error);
}

} // namespace LunarDB::Astral::Tests
