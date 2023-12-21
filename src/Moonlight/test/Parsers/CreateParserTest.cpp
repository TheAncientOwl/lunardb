#include <gtest/gtest.h>

#include "ParsedQuery.hpp"
#include "QueryDataHelpers/Init.hpp"
#include "QueryDataHelpers/Operators.hpp"

#include "Common/Expectations.hpp"

#define QUERY_TYPE Create

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

TEST(CreateParserTest, singleNoBindingSuccess01)
{
    const auto query = "create table SomeTable based on SomeSchema";
    const auto expected = Init::CreateInit{}
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

TEST(CreateParserTest, singleNoBindingSuccess02)
{
    const auto query = "create volatile table SomeTable based on SomeSchema";
    const auto expected = Init::CreateInit{}
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

TEST(CreateParserTest, singleNoBindingSuccess03)
{
    const auto query = "create table SomeTable based on SomeSchema blended";
    const auto expected = Init::CreateInit{}
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

TEST(CreateParserTest, singleNoBindingSuccess04)
{
    const auto query = "create volatile table SomeTable based on SomeSchema blended";
    const auto expected = Init::CreateInit{}
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

TEST(CreateParserTest, singleNoBindingSuccess05)
{
    const auto query = "create collection SomeCollection based on SomeSchema";
    const auto expected = Init::CreateInit{}
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

TEST(CreateParserTest, singleNoBindingSuccess06)
{
    const auto query = "create volatile collection SomeCollection based on SomeSchema";
    const auto expected = Init::CreateInit{}
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

TEST(CreateParserTest, singleNoBindingSuccess07)
{
    const auto query = "create collection SomeCollection based on SomeSchema blended";
    const auto expected = Init::CreateInit{}
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

TEST(CreateParserTest, singleNoBindingSuccess08)
{
    const auto query = "create volatile collection SomeCollection based on SomeSchema blended";
    const auto expected = Init::CreateInit{}
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

TEST(CreateParserTest, singleBindingSuccess01)
{
    const auto query =
        "create table SomeTable based on SomeSchema"
        "    binding [ field1 from SomeTable1, field2 from SomeTable2 ]";

    const auto expected = Init::CreateInit{}
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

TEST(CreateParserTest, singleBindingSuccess02)
{
    const auto query =
        "create volatile table SomeTable based on SomeSchema"
        "    binding [ field1 from SomeTable1, field2 from SomeTable2 ]";

    const auto expected = Init::CreateInit{}
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

TEST(CreateParserTest, singleBindingSuccess03)
{
    const auto query =
        "create table SomeTable based on SomeSchema "
        "    binding [ field1 from SomeTable1, field2 from SomeTable2 ] blended";

    const auto expected = Init::CreateInit{}
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

TEST(CreateParserTest, singleBindingSuccess04)
{
    const auto query =
        "create volatile table SomeTable based on SomeSchema"
        "    binding [ field1 from SomeTable1, field2 from SomeTable2 ] blended";

    const auto expected = Init::CreateInit{}
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

TEST(CreateParserTest, singleBindingSuccess05)
{
    const auto query =
        "create collection SomeCollection based on SomeSchema"
        "    binding [ field1 from SomeCollection1, field2 from SomeCollection2 ]";

    const auto expected = Init::CreateInit{}
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

TEST(CreateParserTest, singleBindingSuccess06)
{
    const auto query =
        "create volatile collection SomeCollection based on SomeSchema"
        "    binding [ field1 from SomeCollection1, field2 from SomeCollection2 ]";

    const auto expected = Init::CreateInit{}
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

TEST(CreateParserTest, singleBindingSuccess07)
{
    const auto query =
        "create collection SomeCollection based on SomeSchema"
        "    binding [ field1 from SomeCollection1, field2 from SomeCollection2 ] blended";

    const auto expected = Init::CreateInit{}
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

TEST(CreateParserTest, singleBindingSuccess08)
{
    const auto query =
        "create volatile collection SomeCollection based on SomeSchema"
        "    binding [ field1 from SomeCollection1, field2 from SomeCollection2 ] blended";

    const auto expected = Init::CreateInit{}
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

TEST(CreateParserTest, multiple01)
{
    const auto query = "create tables from [ Schema1, Schema2, Schema3, Schema4 ]";
    const auto expected = Init::CreateInit{}
        .is_volatile(false)
        .structure_type(Primitives::EStructureType::Table)
        .single(std::nullopt)
        .multiple(Init::CreateInit::MultipleInit{}
            .schema_names(std::vector<std::string>{"Schema1", "Schema2", "Schema3", "Schema4"})
            .structure_name_format("%TypeName%_Structure_%Hash%")
        );

    EXPECT_SUCCESS(query, expected);
}

TEST(CreateParserTest, multiple02)
{
    const auto query = R"(create tables from [ Schema1, Schema2, Schema3, Schema4 ] using format "%TypeName%Table")";
    const auto expected = Init::CreateInit{}
        .is_volatile(false)
        .structure_type(Primitives::EStructureType::Table)
        .single(std::nullopt)
        .multiple(Init::CreateInit::MultipleInit{}
            .schema_names(std::vector<std::string>{"Schema1", "Schema2", "Schema3", "Schema4"})
            .structure_name_format("%TypeName%Table")
        );

    EXPECT_SUCCESS(query, expected);
}

TEST(CreateParserTest, multiple03)
{
    const auto query = "create volatile tables from [ Schema1, Schema2, Schema3, Schema4 ]";
    const auto expected = Init::CreateInit{}
        .is_volatile(true)
        .structure_type(Primitives::EStructureType::Table)
        .single(std::nullopt)
        .multiple(Init::CreateInit::MultipleInit{}
            .schema_names(std::vector<std::string>{"Schema1", "Schema2", "Schema3", "Schema4"})
            .structure_name_format("%TypeName%_Structure_%Hash%")
        );

    EXPECT_SUCCESS(query, expected);
}

TEST(CreateParserTest, multiple04)
{
    const auto query = R"(create volatile tables from [ Schema1, Schema2, Schema3, Schema4 ] using format "%TypeName%Table")";
    const auto expected = Init::CreateInit{}
        .is_volatile(true)
        .structure_type(Primitives::EStructureType::Table)
        .single(std::nullopt)
        .multiple(Init::CreateInit::MultipleInit{}
            .schema_names(std::vector<std::string>{"Schema1", "Schema2", "Schema3", "Schema4"})
            .structure_name_format("%TypeName%Table")
        );

    EXPECT_SUCCESS(query, expected);
}

TEST(CreateParserTest, multiple05)
{
    const auto query = "create collections from [ Schema1, Schema2, Schema3, Schema4 ]";
    const auto expected = Init::CreateInit{}
        .is_volatile(false)
        .structure_type(Primitives::EStructureType::Collection)
        .single(std::nullopt)
        .multiple(Init::CreateInit::MultipleInit{}
            .schema_names(std::vector<std::string>{"Schema1", "Schema2", "Schema3", "Schema4"})
            .structure_name_format("%TypeName%_Structure_%Hash%")
        );

    EXPECT_SUCCESS(query, expected);
}

TEST(CreateParserTest, multiple06)
{
    const auto query = R"(create collections from [ Schema1, Schema2, Schema3, Schema4 ] using format "%TypeName%Collection")";
    const auto expected = Init::CreateInit{}
        .is_volatile(false)
        .structure_type(Primitives::EStructureType::Collection)
        .single(std::nullopt)
        .multiple(Init::CreateInit::MultipleInit{}
            .schema_names(std::vector<std::string>{"Schema1", "Schema2", "Schema3", "Schema4"})
            .structure_name_format("%TypeName%Collection")
        );

    EXPECT_SUCCESS(query, expected);
}

TEST(CreateParserTest, multiple07)
{
    const auto query = "create volatile collections from [ Schema1, Schema2, Schema3, Schema4 ]";
    const auto expected = Init::CreateInit{}
        .is_volatile(true)
        .structure_type(Primitives::EStructureType::Collection)
        .single(std::nullopt)
        .multiple(Init::CreateInit::MultipleInit{}
            .schema_names(std::vector<std::string>{"Schema1", "Schema2", "Schema3", "Schema4"})
            .structure_name_format("%TypeName%_Structure_%Hash%")
        );

    EXPECT_SUCCESS(query, expected);
}

TEST(CreateParserTest, multiple08)
{
    const auto query = R"(create volatile collections from [ Schema1, Schema2, Schema3, Schema4 ] using format "%TypeName%Collection")";
    const auto expected = Init::CreateInit{}
        .is_volatile(true)
        .structure_type(Primitives::EStructureType::Collection)
        .single(std::nullopt)
        .multiple(Init::CreateInit::MultipleInit{}
            .schema_names(std::vector<std::string>{"Schema1", "Schema2", "Schema3", "Schema4"})
            .structure_name_format("%TypeName%Collection")
        );

    EXPECT_SUCCESS(query, expected);
}

TEST(CreateParserTest, singleNoBindingsFail01)
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

TEST(CreateParserTest, singleBindingsFail01)
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

TEST(CreateParserTest, multipleFail01)
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

} // namespace LunarDB::Moonlight::Implementation::Tests
