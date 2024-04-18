#include "QueryParserTest.hpp"

#define QUERY_TYPE Create

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

// clang-format off
TEST(Moonlight_CreateParserTest, singleNoBindingSuccess01)
{
    auto const query = "create table SomeTable based on SomeSchema";
    auto const expected = Init::CreateInit{}
        .is_volatile(false)
        .structure_type(Primitives::EStructureType::Table)
        .single(Init::CreateInit::SingleInit{}
            .structure_name("SomeTable")
            .schema_name("SomeSchema")
            .bindings({})
            .blended(false)
        )
        .multiple(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_CreateParserTest, singleNoBindingSuccess02)
{
    auto const query = "create volatile table SomeTable based on SomeSchema";
    auto const expected = Init::CreateInit{}
        .is_volatile(true)
        .structure_type(Primitives::EStructureType::Table)
        .single(Init::CreateInit::SingleInit{}
            .structure_name("SomeTable")
            .schema_name("SomeSchema")
            .bindings({})
            .blended(false)
        )
        .multiple(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_CreateParserTest, singleNoBindingSuccess03)
{
    auto const query = "create table SomeTable based on SomeSchema blended";
    auto const expected = Init::CreateInit{}
        .is_volatile(false)
        .structure_type(Primitives::EStructureType::Table)
        .single(Init::CreateInit::SingleInit{}
            .structure_name("SomeTable")
            .schema_name("SomeSchema")
            .bindings({})
            .blended(true)
        )
        .multiple(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_CreateParserTest, singleNoBindingSuccess04)
{
    auto const query = "create volatile table SomeTable based on SomeSchema blended";
    auto const expected = Init::CreateInit{}
        .is_volatile(true)
        .structure_type(Primitives::EStructureType::Table)
        .single(Init::CreateInit::SingleInit{}
            .structure_name("SomeTable")
            .schema_name("SomeSchema")
            .bindings({})
            .blended(true)
        )
        .multiple(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_CreateParserTest, singleNoBindingSuccess05)
{
    auto const query = "create collection SomeCollection based on SomeSchema";
    auto const expected = Init::CreateInit{}
        .is_volatile(false)
        .structure_type(Primitives::EStructureType::Collection)
        .single(Init::CreateInit::SingleInit{}
            .structure_name("SomeCollection")
            .schema_name("SomeSchema")
            .bindings({})
            .blended(false)
        )
        .multiple(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_CreateParserTest, singleNoBindingSuccess06)
{
    auto const query = "create volatile collection SomeCollection based on SomeSchema";
    auto const expected = Init::CreateInit{}
        .is_volatile(true)
        .structure_type(Primitives::EStructureType::Collection)
        .single(Init::CreateInit::SingleInit{}
            .structure_name("SomeCollection")
            .schema_name("SomeSchema")
            .bindings({})
            .blended(false)
        )
        .multiple(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_CreateParserTest, singleNoBindingSuccess07)
{
    auto const query = "create collection SomeCollection based on SomeSchema blended";
    auto const expected = Init::CreateInit{}
        .is_volatile(false)
        .structure_type(Primitives::EStructureType::Collection)
        .single(Init::CreateInit::SingleInit{}
            .structure_name("SomeCollection")
            .schema_name("SomeSchema")
            .bindings({})
            .blended(true)
        )
        .multiple(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_CreateParserTest, singleNoBindingSuccess08)
{
    auto const query = "create volatile collection SomeCollection based on SomeSchema blended";
    auto const expected = Init::CreateInit{}
        .is_volatile(true)
        .structure_type(Primitives::EStructureType::Collection)
        .single(Init::CreateInit::SingleInit{}
            .structure_name("SomeCollection")
            .schema_name("SomeSchema")
            .bindings({})
            .blended(true)
        )
        .multiple(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_CreateParserTest, singleBindingSuccess01)
{
    auto const query =
        "create table SomeTable based on SomeSchema"
        "    binding [ field1 from SomeTable1, field2 from SomeTable2 ]";

    auto const expected = Init::CreateInit{}
        .is_volatile(false)
        .structure_type(Primitives::EStructureType::Table)
        .single(Init::CreateInit::SingleInit{}
            .structure_name("SomeTable")
            .schema_name("SomeSchema")
            .bindings({
                Init::CreateInit::SingleInit::BindingInit{}.field("field1").table("SomeTable1"),
                Init::CreateInit::SingleInit::BindingInit{}.field("field2").table("SomeTable2")
                })
            .blended(false)
        )
        .multiple(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_CreateParserTest, singleBindingSuccess02)
{
    auto const query =
        "create volatile table SomeTable based on SomeSchema"
        "    binding [ field1 from SomeTable1, field2 from SomeTable2 ]";

    auto const expected = Init::CreateInit{}
        .is_volatile(true)
        .structure_type(Primitives::EStructureType::Table)
        .single(Init::CreateInit::SingleInit{}
            .structure_name("SomeTable")
            .schema_name("SomeSchema")
            .bindings({
                Init::CreateInit::SingleInit::BindingInit{}.field("field1").table("SomeTable1"),
                Init::CreateInit::SingleInit::BindingInit{}.field("field2").table("SomeTable2")
                })
            .blended(false)
        )
        .multiple(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_CreateParserTest, singleBindingSuccess03)
{
    auto const query =
        "create table SomeTable based on SomeSchema "
        "    binding [ field1 from SomeTable1, field2 from SomeTable2 ] blended";

    auto const expected = Init::CreateInit{}
        .is_volatile(false)
        .structure_type(Primitives::EStructureType::Table)
        .single(Init::CreateInit::SingleInit{}
            .structure_name("SomeTable")
            .schema_name("SomeSchema")
            .bindings({
                Init::CreateInit::SingleInit::BindingInit{}.field("field1").table("SomeTable1"),
                Init::CreateInit::SingleInit::BindingInit{}.field("field2").table("SomeTable2")
                })
            .blended(true)
        )
        .multiple(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_CreateParserTest, singleBindingSuccess04)
{
    auto const query =
        "create volatile table SomeTable based on SomeSchema"
        "    binding [ field1 from SomeTable1, field2 from SomeTable2 ] blended";

    auto const expected = Init::CreateInit{}
        .is_volatile(true)
        .structure_type(Primitives::EStructureType::Table)
        .single(Init::CreateInit::SingleInit{}
            .structure_name("SomeTable")
            .schema_name("SomeSchema")
            .bindings({
                Init::CreateInit::SingleInit::BindingInit{}.field("field1").table("SomeTable1"),
                Init::CreateInit::SingleInit::BindingInit{}.field("field2").table("SomeTable2")
                })
            .blended(true)
        )
        .multiple(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_CreateParserTest, singleBindingSuccess05)
{
    auto const query =
        "create collection SomeCollection based on SomeSchema"
        "    binding [ field1 from SomeCollection1, field2 from SomeCollection2 ]";

    auto const expected = Init::CreateInit{}
        .is_volatile(false)
        .structure_type(Primitives::EStructureType::Collection)
        .single(Init::CreateInit::SingleInit{}
            .structure_name("SomeCollection")
            .schema_name("SomeSchema")
            .bindings({
                Init::CreateInit::SingleInit::BindingInit{}.field("field1").table("SomeCollection1"),
                Init::CreateInit::SingleInit::BindingInit{}.field("field2").table("SomeCollection2")
                })
            .blended(false)
        )
        .multiple(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_CreateParserTest, singleBindingSuccess06)
{
    auto const query =
        "create volatile collection SomeCollection based on SomeSchema"
        "    binding [ field1 from SomeCollection1, field2 from SomeCollection2 ]";

    auto const expected = Init::CreateInit{}
        .is_volatile(true)
        .structure_type(Primitives::EStructureType::Collection)
        .single(Init::CreateInit::SingleInit{}
            .structure_name("SomeCollection")
            .schema_name("SomeSchema")
            .bindings({
                Init::CreateInit::SingleInit::BindingInit{}.field("field1").table("SomeCollection1"),
                Init::CreateInit::SingleInit::BindingInit{}.field("field2").table("SomeCollection2")
                })
            .blended(false)
        )
        .multiple(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_CreateParserTest, singleBindingSuccess07)
{
    auto const query =
        "create collection SomeCollection based on SomeSchema"
        "    binding [ field1 from SomeCollection1, field2 from SomeCollection2 ] blended";

    auto const expected = Init::CreateInit{}
        .is_volatile(false)
        .structure_type(Primitives::EStructureType::Collection)
        .single(Init::CreateInit::SingleInit{}
            .structure_name("SomeCollection")
            .schema_name("SomeSchema")
            .bindings({
                Init::CreateInit::SingleInit::BindingInit{}.field("field1").table("SomeCollection1"),
                Init::CreateInit::SingleInit::BindingInit{}.field("field2").table("SomeCollection2")
                })
            .blended(true)
        )
        .multiple(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_CreateParserTest, singleBindingSuccess08)
{
    auto const query =
        "create volatile collection SomeCollection based on SomeSchema"
        "    binding [ field1 from SomeCollection1, field2 from SomeCollection2 ] blended";

    auto const expected = Init::CreateInit{}
        .is_volatile(true)
        .structure_type(Primitives::EStructureType::Collection)
        .single(Init::CreateInit::SingleInit{}
            .structure_name("SomeCollection")
            .schema_name("SomeSchema")
            .bindings({
                Init::CreateInit::SingleInit::BindingInit{}.field("field1").table("SomeCollection1"),
                Init::CreateInit::SingleInit::BindingInit{}.field("field2").table("SomeCollection2")
                })
            .blended(true)
        )
        .multiple(std::nullopt);

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_CreateParserTest, multiple01)
{
    auto const query = "create tables from [ Schema1, Schema2, Schema3, Schema4 ]";
    auto const expected = Init::CreateInit{}
        .is_volatile(false)
        .structure_type(Primitives::EStructureType::Table)
        .single(std::nullopt)
        .multiple(Init::CreateInit::MultipleInit{}
            .schema_names(std::vector<std::string>{"Schema1", "Schema2", "Schema3", "Schema4"})
            .structure_name_format("%TypeName%_Structure_%Hash%")
        );

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_CreateParserTest, multiple02)
{
    auto const query = R"(create tables from [ Schema1, Schema2, Schema3, Schema4 ] using format "%TypeName%Table")";
    auto const expected = Init::CreateInit{}
        .is_volatile(false)
        .structure_type(Primitives::EStructureType::Table)
        .single(std::nullopt)
        .multiple(Init::CreateInit::MultipleInit{}
            .schema_names(std::vector<std::string>{"Schema1", "Schema2", "Schema3", "Schema4"})
            .structure_name_format("%TypeName%Table")
        );

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_CreateParserTest, multiple03)
{
    auto const query = "create volatile tables from [ Schema1, Schema2, Schema3, Schema4 ]";
    auto const expected = Init::CreateInit{}
        .is_volatile(true)
        .structure_type(Primitives::EStructureType::Table)
        .single(std::nullopt)
        .multiple(Init::CreateInit::MultipleInit{}
            .schema_names(std::vector<std::string>{"Schema1", "Schema2", "Schema3", "Schema4"})
            .structure_name_format("%TypeName%_Structure_%Hash%")
        );

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_CreateParserTest, multiple04)
{
    auto const query = R"(create volatile tables from [ Schema1, Schema2, Schema3, Schema4 ] using format "%TypeName%Table")";
    auto const expected = Init::CreateInit{}
        .is_volatile(true)
        .structure_type(Primitives::EStructureType::Table)
        .single(std::nullopt)
        .multiple(Init::CreateInit::MultipleInit{}
            .schema_names(std::vector<std::string>{"Schema1", "Schema2", "Schema3", "Schema4"})
            .structure_name_format("%TypeName%Table")
        );

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_CreateParserTest, multiple05)
{
    auto const query = "create collections from [ Schema1, Schema2, Schema3, Schema4 ]";
    auto const expected = Init::CreateInit{}
        .is_volatile(false)
        .structure_type(Primitives::EStructureType::Collection)
        .single(std::nullopt)
        .multiple(Init::CreateInit::MultipleInit{}
            .schema_names(std::vector<std::string>{"Schema1", "Schema2", "Schema3", "Schema4"})
            .structure_name_format("%TypeName%_Structure_%Hash%")
        );

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_CreateParserTest, multiple06)
{
    auto const query = R"(create collections from [ Schema1, Schema2, Schema3, Schema4 ] using format "%TypeName%Collection")";
    auto const expected = Init::CreateInit{}
        .is_volatile(false)
        .structure_type(Primitives::EStructureType::Collection)
        .single(std::nullopt)
        .multiple(Init::CreateInit::MultipleInit{}
            .schema_names(std::vector<std::string>{"Schema1", "Schema2", "Schema3", "Schema4"})
            .structure_name_format("%TypeName%Collection")
        );

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_CreateParserTest, multiple07)
{
    auto const query = "create volatile collections from [ Schema1, Schema2, Schema3, Schema4 ]";
    auto const expected = Init::CreateInit{}
        .is_volatile(true)
        .structure_type(Primitives::EStructureType::Collection)
        .single(std::nullopt)
        .multiple(Init::CreateInit::MultipleInit{}
            .schema_names(std::vector<std::string>{"Schema1", "Schema2", "Schema3", "Schema4"})
            .structure_name_format("%TypeName%_Structure_%Hash%")
        );

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_CreateParserTest, multiple08)
{
    auto const query = R"(create volatile collections from [ Schema1, Schema2, Schema3, Schema4 ] using format "%TypeName%Collection")";
    auto const expected = Init::CreateInit{}
        .is_volatile(true)
        .structure_type(Primitives::EStructureType::Collection)
        .single(std::nullopt)
        .multiple(Init::CreateInit::MultipleInit{}
            .schema_names(std::vector<std::string>{"Schema1", "Schema2", "Schema3", "Schema4"})
            .structure_name_format("%TypeName%Collection")
        );

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_CreateParserTest, singleNoBindingsFail01)
{
    EXPECT_FAIL("create volatile SomeTable based on SomeSchema blended");
    EXPECT_FAIL("create volatile table based on SomeSchema blended");
    EXPECT_FAIL("create volatile table SomeTable on SomeSchema blended");
    EXPECT_FAIL("create volatile table SomeTable SomeSchema blended");
    EXPECT_FAIL("create volatile table SomeTable SomeSchema blended");
    EXPECT_FAIL("create volatile table based on SomeSchema blended");
    EXPECT_FAIL("create volatile table SomeTable based on Some Schema blended");
    EXPECT_FAIL("create volatile table Some Table based on SomeSchema blended");

    EXPECT_FAIL("create volatile SomeCollection based on SomeSchema blended");
    EXPECT_FAIL("create volatile collection based on SomeSchema blended");
    EXPECT_FAIL("create volatile collection SomeCollection on SomeSchema blended");
    EXPECT_FAIL("create volatile collection SomeCollection SomeSchema blended");
    EXPECT_FAIL("create volatile collection SomeCollection SomeSchema blended");
    EXPECT_FAIL("create volatile collection based on SomeSchema blended");
    EXPECT_FAIL("create volatile collection SomeCollection based on Some Schema blended");
    EXPECT_FAIL("create volatile collection Some Table based on SomeSchema blended");
}

TEST(Moonlight_CreateParserTest, singleBindingsFail01)
{
    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ from SomeTable1, field2 from SomeTable2 ]");
    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ field1 SomeTable1, field2 from SomeTable2 ]");
    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ field1 from, field2 from SomeTable2 ]");
    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ field1 from SomeTable1 field2 from SomeTable2 ]");
    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ field1 from SomeTable1, from SomeTable2 ]");
    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ field1 from SomeTable1, field2 SomeTable2 ]");
    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ field1 from SomeTable1, field2 from ]");
    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ field1 field2 from SomeTable2 ]");
    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ field1 from SomeTable1, field2 ]");
    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ field1, field2 from SomeTable2 ]");
    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ from, field2 from SomeTable2 ]");
    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ field1 from SomeTable1, from ]");
    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ field1 from SomeTable1, SomeTable2 ]");

    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ from SomeCollection1, field2 from SomeCollection2 ]");
    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ field1 SomeCollection1, field2 from SomeCollection2 ]");
    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ field1 from, field2 from SomeCollection2 ]");
    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ field1 from SomeCollection1 field2 from SomeCollection2 ]");
    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ field1 from SomeCollection1, from SomeCollection2 ]");
    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ field1 from SomeCollection1, field2 SomeCollection2 ]");
    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ field1 from SomeCollection1, field2 from ]");
    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ field1 field2 from SomeCollection2 ]");
    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ field1 from SomeCollection1, field2 ]");
    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ field1, field2 from SomeCollection2 ]");
    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ from, field2 from SomeCollection2 ]");
    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ field1 from SomeCollection1, from ]");
    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ field1 from SomeCollection1, SomeCollection2 ]");

    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ from SomeTable1, field2 from SomeTable2 ] blended");
    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ field1 SomeTable1, field2 from SomeTable2 ] blended");
    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ field1 from, field2 from SomeTable2 ] blended");
    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ field1 from SomeTable1 field2 from SomeTable2 ] blended");
    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ field1 from SomeTable1, from SomeTable2 ] blended");
    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ field1 from SomeTable1, field2 SomeTable2 ] blended");
    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ field1 from SomeTable1, field2 from ] blended");
    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ field1 field2 from SomeTable2 ] blended");
    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ field1 from SomeTable1, field2 ] blended");
    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ field1, field2 from SomeTable2 ] blended");
    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ from, field2 from SomeTable2 ] blended");
    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ field1 from SomeTable1, from ] blended");
    EXPECT_FAIL("create table SomeTable based on SomeSchema binding [ field1 from SomeTable1, SomeTable2 ] blended");

    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ from SomeCollection1, field2 from SomeCollection2 ] blended");
    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ field1 SomeCollection1, field2 from SomeCollection2 ] blended");
    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ field1 from, field2 from SomeCollection2 ] blended");
    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ field1 from SomeCollection1 field2 from SomeCollection2 ] blended");
    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ field1 from SomeCollection1, from SomeCollection2 ] blended");
    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ field1 from SomeCollection1, field2 SomeCollection2 ] blended");
    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ field1 from SomeCollection1, field2 from ] blended");
    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ field1 field2 from SomeCollection2 ] blended");
    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ field1 from SomeCollection1, field2 ] blended");
    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ field1, field2 from SomeCollection2 ] blended");
    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ from, field2 from SomeCollection2 ] blended");
    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ field1 from SomeCollection1, from ] blended");
    EXPECT_FAIL("create collection SomeCollection based on SomeSchema binding [ field1 from SomeCollection1, SomeCollection2 ] blended");
}

TEST(Moonlight_CreateParserTest, multipleFail01)
{
    EXPECT_FAIL(R"(create [ Schema1, Schema2, Schema3, Schema4 ] using format)");

    EXPECT_FAIL(R"(create volatile from [ Schema1, Schema2, Schema3, Schema4 ] using format "%TypeName%Table")");
    EXPECT_FAIL(R"(create volatile tables [ Schema1, Schema2, Schema3, Schema4 ] using format "%TypeName%Table")");
    EXPECT_FAIL(R"(create volatile tables from Schema1, Schema2, Schema3, Schema4 ] using format "%TypeName%Table")");
    EXPECT_FAIL(R"(create volatile tables from [ Schema1, Schema2, Schema3, Schema4 using format "%TypeName%Table")");
    EXPECT_FAIL(R"(create volatile tables from [ Schema1 Schema2, Schema3, Schema4 ] using format %TypeName%Table")");
    EXPECT_FAIL(R"(create volatile tables from [ Schema1 Schema2, Schema3, Schema4 ] using format "%TypeName%Table)");
    EXPECT_FAIL(R"(create volatile tables from [ Schema1, Schema2, Schema3, Schema4 ] format "%TypeName%Table")");
    EXPECT_FAIL(R"(create volatile tables from [ Schema1, Schema2, Schema3, Schema4 ] using "%TypeName%Table")");
    EXPECT_FAIL(R"(create volatile tables from [ Schema1, Schema2, Schema3, Schema4 ] using format %TypeName%Table")");
    EXPECT_FAIL(R"(create volatile tables from [ Schema1, Schema2, Schema3, Schema4 ] using format "%TypeName%Table)");
    EXPECT_FAIL(R"(create volatile tables from [ Schema1, Schema2, Schema3, Schema4 ] using format)");
    EXPECT_FAIL(R"(create from [ Schema1, Schema2, Schema3, Schema4 ] using format "%TypeName%Table")");
    EXPECT_FAIL(R"(create tables [ Schema1, Schema2, Schema3, Schema4 ] using format "%TypeName%Table")");
    EXPECT_FAIL(R"(create tables from Schema1, Schema2, Schema3, Schema4 ] using format "%TypeName%Table")");
    EXPECT_FAIL(R"(create tables from [ Schema1, Schema2, Schema3, Schema4 using format "%TypeName%Table")");
    EXPECT_FAIL(R"(create tables from [ Schema1 Schema2, Schema3, Schema4 ] format "%TypeName%Table")");
    EXPECT_FAIL(R"(create tables from [ Schema1, Schema2, Schema3, Schema4 ] format "%TypeName%Table")");
    EXPECT_FAIL(R"(create tables from [ Schema1, Schema2, Schema3, Schema4 ] using "%TypeName%Table")");
    EXPECT_FAIL(R"(create tables from [ Schema1, Schema2, Schema3, Schema4 ] using format %TypeName%Table")");
    EXPECT_FAIL(R"(create tables from [ Schema1, Schema2, Schema3, Schema4 ] using format "%TypeName%Table)");
    EXPECT_FAIL(R"(create tables from [ Schema1, Schema2, Schema3, Schema4 ] using format)");

    EXPECT_FAIL(R"(create volatile from [ Schema1, Schema2, Schema3, Schema4 ] using format "%TypeName%Collection")");
    EXPECT_FAIL(R"(create volatile collections [ Schema1, Schema2, Schema3, Schema4 ] using format "%TypeName%Collection")");
    EXPECT_FAIL(R"(create volatile collections from Schema1, Schema2, Schema3, Schema4 ] using format "%TypeName%Collection")");
    EXPECT_FAIL(R"(create volatile collections from [ Schema1, Schema2, Schema3, Schema4 using format "%TypeName%Collection")");
    EXPECT_FAIL(R"(create volatile collections from [ Schema1 Schema2, Schema3, Schema4 ] using format %TypeName%Collection")");
    EXPECT_FAIL(R"(create volatile collections from [ Schema1 Schema2, Schema3, Schema4 ] using format "%TypeName%Collection)");
    EXPECT_FAIL(R"(create volatile collections from [ Schema1, Schema2, Schema3, Schema4 ] format "%TypeName%Collection")");
    EXPECT_FAIL(R"(create volatile collections from [ Schema1, Schema2, Schema3, Schema4 ] using "%TypeName%Collection")");
    EXPECT_FAIL(R"(create volatile collections from [ Schema1, Schema2, Schema3, Schema4 ] using format %TypeName%Collection")");
    EXPECT_FAIL(R"(create volatile collections from [ Schema1, Schema2, Schema3, Schema4 ] using format "%TypeName%Collection)");
    EXPECT_FAIL(R"(create volatile collections from [ Schema1, Schema2, Schema3, Schema4 ] using format)");
    EXPECT_FAIL(R"(create from [ Schema1, Schema2, Schema3, Schema4 ] using format "%TypeName%Collection")");
    EXPECT_FAIL(R"(create collections [ Schema1, Schema2, Schema3, Schema4 ] using format "%TypeName%Collection")");
    EXPECT_FAIL(R"(create collections from Schema1, Schema2, Schema3, Schema4 ] using format "%TypeName%Collection")");
    EXPECT_FAIL(R"(create collections from [ Schema1, Schema2, Schema3, Schema4 using format "%TypeName%Collection")");
    EXPECT_FAIL(R"(create collections from [ Schema1 Schema2, Schema3, Schema4 ] using "%TypeName%Collection")");
    EXPECT_FAIL(R"(create collections from [ Schema1, Schema2, Schema3, Schema4 ] format "%TypeName%Collection")");
    EXPECT_FAIL(R"(create collections from [ Schema1, Schema2, Schema3, Schema4 ] using "%TypeName%Collection")");
    EXPECT_FAIL(R"(create collections from [ Schema1, Schema2, Schema3, Schema4 ] using format %TypeName%Collection")");
    EXPECT_FAIL(R"(create collections from [ Schema1, Schema2, Schema3, Schema4 ] using format "%TypeName%Collection)");
    EXPECT_FAIL(R"(create collections from [ Schema1, Schema2, Schema3, Schema4 ] using format)");
}
// clang-format on

} // namespace LunarDB::Moonlight::Implementation::Tests
