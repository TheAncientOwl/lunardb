#include "Common/ParserTestIncludes.hpp"

#define QUERY_TYPE Schema

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

TEST(SchemaParserTest, success01_all_types)
{
    const auto query =
        "schema SomeSchema {"
        "   field_1 : Rid,"
        "   field_2 : String,"
        "   field_3 : Boolean,"
        "   field_4 : DateTime,"
        "   field_5 : Integer,"
        "   field_6 : Integer8,"
        "   field_7 : Integer16,"
        "   field_8 : Integer32,"
        "   field_9 : Integer64,"
        "   field_10: Float,"
        "   field_11: Float32,"
        "   field_12: Float64,"
        " "
        "   field_opt_1 : Rid?,"
        "   field_opt_2 : String?,"
        "   field_opt_3 : Boolean?,"
        "   field_opt_4 : DateTime?,"
        "   field_opt_5 : Integer?,"
        "   field_opt_6 : Integer8?,"
        "   field_opt_7 : Integer16?,"
        "   field_opt_8 : Integer32?,"
        "   field_opt_9 : Integer64?,"
        "   field_opt_10: Float?,"
        "   field_opt_11: Float32?,"
        "   field_opt_12: Float64?,"
        " "
        "   field_arr_1 : ArrayOf<Rid>,"
        "   field_arr_2 : ArrayOf<String>,"
        "   field_arr_3 : ArrayOf<Boolean>,"
        "   field_arr_4 : ArrayOf<DateTime>,"
        "   field_arr_5 : ArrayOf<Integer>,"
        "   field_arr_6 : ArrayOf<Integer8>,"
        "   field_arr_7 : ArrayOf<Integer16>,"
        "   field_arr_8 : ArrayOf<Integer32>,"
        "   field_arr_9 : ArrayOf<Integer64>,"
        "   field_arr_10: ArrayOf<Float>,"
        "   field_arr_11: ArrayOf<Float32>,"
        "   field_arr_12: ArrayOf<Float64>,"
        " "
        "}";
    const auto expected = Init::SchemaInit{}
        .name("SomeSchema")
        .fields(std::vector<Schema::Field>{
        Init::SchemaInit::FieldInit{}.name("field_1").type("Rid").optional(false).array(false),
            Init::SchemaInit::FieldInit{}.name("field_2").type("String").optional(false).array(false),
            Init::SchemaInit::FieldInit{}.name("field_3").type("Boolean").optional(false).array(false),
            Init::SchemaInit::FieldInit{}.name("field_4").type("DateTime").optional(false).array(false),
            Init::SchemaInit::FieldInit{}.name("field_5").type("Integer").optional(false).array(false),
            Init::SchemaInit::FieldInit{}.name("field_6").type("Integer8").optional(false).array(false),
            Init::SchemaInit::FieldInit{}.name("field_7").type("Integer16").optional(false).array(false),
            Init::SchemaInit::FieldInit{}.name("field_8").type("Integer32").optional(false).array(false),
            Init::SchemaInit::FieldInit{}.name("field_9").type("Integer64").optional(false).array(false),
            Init::SchemaInit::FieldInit{}.name("field_10").type("Float").optional(false).array(false),
            Init::SchemaInit::FieldInit{}.name("field_11").type("Float32").optional(false).array(false),
            Init::SchemaInit::FieldInit{}.name("field_12").type("Float64").optional(false).array(false),

            Init::SchemaInit::FieldInit{}.name("field_1").type("Rid").optional(true).array(false),
            Init::SchemaInit::FieldInit{}.name("field_2").type("String").optional(true).array(false),
            Init::SchemaInit::FieldInit{}.name("field_3").type("Boolean").optional(true).array(false),
            Init::SchemaInit::FieldInit{}.name("field_4").type("DateTime").optional(true).array(false),
            Init::SchemaInit::FieldInit{}.name("field_5").type("Integer").optional(true).array(false),
            Init::SchemaInit::FieldInit{}.name("field_6").type("Integer8").optional(true).array(false),
            Init::SchemaInit::FieldInit{}.name("field_7").type("Integer16").optional(true).array(false),
            Init::SchemaInit::FieldInit{}.name("field_8").type("Integer32").optional(true).array(false),
            Init::SchemaInit::FieldInit{}.name("field_9").type("Integer64").optional(true).array(false),
            Init::SchemaInit::FieldInit{}.name("field_10").type("Float").optional(true).array(false),
            Init::SchemaInit::FieldInit{}.name("field_11").type("Float32").optional(true).array(false),
            Init::SchemaInit::FieldInit{}.name("field_12").type("Float64").optional(true).array(false),

            Init::SchemaInit::FieldInit{}.name("field_1").type("Rid").optional(false).array(true),
            Init::SchemaInit::FieldInit{}.name("field_2").type("String").optional(false).array(true),
            Init::SchemaInit::FieldInit{}.name("field_3").type("Boolean").optional(false).array(true),
            Init::SchemaInit::FieldInit{}.name("field_4").type("DateTime").optional(false).array(true),
            Init::SchemaInit::FieldInit{}.name("field_5").type("Integer").optional(false).array(true),
            Init::SchemaInit::FieldInit{}.name("field_6").type("Integer8").optional(false).array(true),
            Init::SchemaInit::FieldInit{}.name("field_7").type("Integer16").optional(false).array(true),
            Init::SchemaInit::FieldInit{}.name("field_8").type("Integer32").optional(false).array(true),
            Init::SchemaInit::FieldInit{}.name("field_9").type("Integer64").optional(false).array(true),
            Init::SchemaInit::FieldInit{}.name("field_10").type("Float").optional(false).array(true),
            Init::SchemaInit::FieldInit{}.name("field_11").type("Float32").optional(false).array(true),
            Init::SchemaInit::FieldInit{}.name("field_12").type("Float64").optional(false).array(true) });

    EXPECT_SUCCESS(query, expected);
}

TEST(SchemaParserTest, success02)
{
    const auto query =
        "schema SomeSchema {"
        "   field_1 : Rid,"
        "   field_2 : String,"
        "   field_3 : Boolean,"
        "   field_4 : DateTime,"
        "   field_5 : Integer,"
        "   field_6 : Integer8,"
        "   field_7 : Integer16,"
        "   field_8 : Integer32,"
        "   field_9 : Integer64,"
        "   field_10: Float,"
        "   field_11: Float32,"
        "   field_12: Float64,"
        "}";
    const auto expected = Init::SchemaInit{}
        .name("SomeSchema")
        .fields(std::vector<Schema::Field>{
        Init::SchemaInit::FieldInit{}.name("field_1").type("Rid").optional(false).array(false),
            Init::SchemaInit::FieldInit{}.name("field_2").type("String").optional(false).array(false),
            Init::SchemaInit::FieldInit{}.name("field_3").type("Boolean").optional(false).array(false),
            Init::SchemaInit::FieldInit{}.name("field_4").type("DateTime").optional(false).array(false),
            Init::SchemaInit::FieldInit{}.name("field_5").type("Integer").optional(false).array(false),
            Init::SchemaInit::FieldInit{}.name("field_6").type("Integer8").optional(false).array(false),
            Init::SchemaInit::FieldInit{}.name("field_7").type("Integer16").optional(false).array(false),
            Init::SchemaInit::FieldInit{}.name("field_8").type("Integer32").optional(false).array(false),
            Init::SchemaInit::FieldInit{}.name("field_9").type("Integer64").optional(false).array(false),
            Init::SchemaInit::FieldInit{}.name("field_10").type("Float").optional(false).array(false),
            Init::SchemaInit::FieldInit{}.name("field_11").type("Float32").optional(false).array(false),
            Init::SchemaInit::FieldInit{}.name("field_12").type("Float64").optional(false).array(false)});

    EXPECT_SUCCESS(query, expected);
}

TEST(SchemaParserTest, success03)
{
    const auto query =
        "schema SomeSchema {"
        "   field_opt_1 : Rid?,"
        "   field_opt_2 : String?,"
        "   field_opt_3 : Boolean?,"
        "   field_opt_4 : DateTime?,"
        "   field_opt_5 : Integer?,"
        "   field_opt_6 : Integer8?,"
        "   field_opt_7 : Integer16?,"
        "   field_opt_8 : Integer32?,"
        "   field_opt_9 : Integer64?,"
        "   field_opt_10: Float?,"
        "   field_opt_11: Float32?,"
        "   field_opt_12: Float64?,"
        "}";
    const auto expected = Init::SchemaInit{}
        .name("SomeSchema")
        .fields(std::vector<Schema::Field>{
        Init::SchemaInit::FieldInit{}.name("field_1").type("Rid").optional(true).array(false),
            Init::SchemaInit::FieldInit{}.name("field_2").type("String").optional(true).array(false),
            Init::SchemaInit::FieldInit{}.name("field_3").type("Boolean").optional(true).array(false),
            Init::SchemaInit::FieldInit{}.name("field_4").type("DateTime").optional(true).array(false),
            Init::SchemaInit::FieldInit{}.name("field_5").type("Integer").optional(true).array(false),
            Init::SchemaInit::FieldInit{}.name("field_6").type("Integer8").optional(true).array(false),
            Init::SchemaInit::FieldInit{}.name("field_7").type("Integer16").optional(true).array(false),
            Init::SchemaInit::FieldInit{}.name("field_8").type("Integer32").optional(true).array(false),
            Init::SchemaInit::FieldInit{}.name("field_9").type("Integer64").optional(true).array(false),
            Init::SchemaInit::FieldInit{}.name("field_10").type("Float").optional(true).array(false),
            Init::SchemaInit::FieldInit{}.name("field_11").type("Float32").optional(true).array(false),
            Init::SchemaInit::FieldInit{}.name("field_12").type("Float64").optional(true).array(false)});

    EXPECT_SUCCESS(query, expected);
}

TEST(SchemaParserTest, success04)
{
    const auto query =
        "schema SomeSchema {"
        "   field_arr_1 : ArrayOf<Rid>,"
        "   field_arr_2 : ArrayOf<String>,"
        "   field_arr_3 : ArrayOf<Boolean>,"
        "   field_arr_4 : ArrayOf<DateTime>,"
        "   field_arr_5 : ArrayOf<Integer>,"
        "   field_arr_6 : ArrayOf<Integer8>,"
        "   field_arr_7 : ArrayOf<Integer16>,"
        "   field_arr_8 : ArrayOf<Integer32>,"
        "   field_arr_9 : ArrayOf<Integer64>,"
        "   field_arr_10: ArrayOf<Float>,"
        "   field_arr_11: ArrayOf<Float32>,"
        "   field_arr_12: ArrayOf<Float64>,"
        " "
        "}";
    const auto expected = Init::SchemaInit{}
        .name("SomeSchema")
        .fields(std::vector<Schema::Field>{
        Init::SchemaInit::FieldInit{}.name("field_1").type("Rid").optional(false).array(false),
            Init::SchemaInit::FieldInit{}.name("field_1").type("Rid").optional(false).array(true),
            Init::SchemaInit::FieldInit{}.name("field_2").type("String").optional(false).array(true),
            Init::SchemaInit::FieldInit{}.name("field_3").type("Boolean").optional(false).array(true),
            Init::SchemaInit::FieldInit{}.name("field_4").type("DateTime").optional(false).array(true),
            Init::SchemaInit::FieldInit{}.name("field_5").type("Integer").optional(false).array(true),
            Init::SchemaInit::FieldInit{}.name("field_6").type("Integer8").optional(false).array(true),
            Init::SchemaInit::FieldInit{}.name("field_7").type("Integer16").optional(false).array(true),
            Init::SchemaInit::FieldInit{}.name("field_8").type("Integer32").optional(false).array(true),
            Init::SchemaInit::FieldInit{}.name("field_9").type("Integer64").optional(false).array(true),
            Init::SchemaInit::FieldInit{}.name("field_10").type("Float").optional(false).array(true),
            Init::SchemaInit::FieldInit{}.name("field_11").type("Float32").optional(false).array(true),
            Init::SchemaInit::FieldInit{}.name("field_12").type("Float64").optional(false).array(true)});

    EXPECT_SUCCESS(query, expected);
}

TEST(SchemaParserTest, success05)
{
    const auto query =
        "schema SomeSchema {"
        "   field_1: SomeOtherSchema1,"
        "   field_2: SomeOtherSchema2?,"
        "   field_3: ArrayOf<SomeOtherSchema3>,"
        "}";
    const auto expected = Init::SchemaInit{}
        .name("SomeSchema")
        .fields(std::vector<Schema::Field>{
        Init::SchemaInit::FieldInit{}.name("field_1").type("SomeOtherSchema1").optional(false).array(false),
            Init::SchemaInit::FieldInit{}.name("field_1").type("SomeOtherSchema2").optional(true).array(false),
            Init::SchemaInit::FieldInit{}.name("field_1").type("SomeOtherSchema3").optional(false).array(true) });

    EXPECT_SUCCESS(query, expected);
}

TEST(SchemaParserTest, fail01)
{
    // missing {
    EXPECT_FAIL(
        "schema SomeSchema "
        "   field_1 : Rid,"
        "   field_2 : String,"
        "   field_3 : Boolean,"
        "   field_4 : DateTime,"
        "   field_5 : Integer,"
        "   field_6 : Integer8,"
        "   field_7 : Integer16,"
        "   field_8 : Integer32,"
        "   field_9 : Integer64,"
        "   field_10: Float,"
        "   field_11: Float32,"
        "   field_12: Float64,"
        " "
        "   field_opt_1 : Rid?,"
        "   field_opt_2 : String?,"
        "   field_opt_3 : Boolean?,"
        "   field_opt_4 : DateTime?,"
        "   field_opt_5 : Integer?,"
        "   field_opt_6 : Integer8?,"
        "   field_opt_7 : Integer16?,"
        "   field_opt_8 : Integer32?,"
        "   field_opt_9 : Integer64?,"
        "   field_opt_10: Float?,"
        "   field_opt_11: Float32?,"
        "   field_opt_12: Float64?,"
        " "
        "   field_arr_1 : ArrayOf<Rid>,"
        "   field_arr_2 : ArrayOf<String>,"
        "   field_arr_3 : ArrayOf<Boolean>,"
        "   field_arr_4 : ArrayOf<DateTime>,"
        "   field_arr_5 : ArrayOf<Integer>,"
        "   field_arr_6 : ArrayOf<Integer8>,"
        "   field_arr_7 : ArrayOf<Integer16>,"
        "   field_arr_8 : ArrayOf<Integer32>,"
        "   field_arr_9 : ArrayOf<Integer64>,"
        "   field_arr_10: ArrayOf<Float>,"
        "   field_arr_11: ArrayOf<Float32>,"
        "   field_arr_12: ArrayOf<Float64>,"
        " "
        "}"
    );

    // missing }
    EXPECT_FAIL(
        "schema SomeSchema {"
        "   field_1 : Rid,"
        "   field_2 : String,"
        "   field_3 : Boolean,"
        "   field_4 : DateTime,"
        "   field_5 : Integer,"
        "   field_6 : Integer8,"
        "   field_7 : Integer16,"
        "   field_8 : Integer32,"
        "   field_9 : Integer64,"
        "   field_10: Float,"
        "   field_11: Float32,"
        "   field_12: Float64,"
        " "
        "   field_opt_1 : Rid?,"
        "   field_opt_2 : String?,"
        "   field_opt_3 : Boolean?,"
        "   field_opt_4 : DateTime?,"
        "   field_opt_5 : Integer?,"
        "   field_opt_6 : Integer8?,"
        "   field_opt_7 : Integer16?,"
        "   field_opt_8 : Integer32?,"
        "   field_opt_9 : Integer64?,"
        "   field_opt_10: Float?,"
        "   field_opt_11: Float32?,"
        "   field_opt_12: Float64?,"
        " "
        "   field_arr_1 : ArrayOf<Rid>,"
        "   field_arr_2 : ArrayOf<String>,"
        "   field_arr_3 : ArrayOf<Boolean>,"
        "   field_arr_4 : ArrayOf<DateTime>,"
        "   field_arr_5 : ArrayOf<Integer>,"
        "   field_arr_6 : ArrayOf<Integer8>,"
        "   field_arr_7 : ArrayOf<Integer16>,"
        "   field_arr_8 : ArrayOf<Integer32>,"
        "   field_arr_9 : ArrayOf<Integer64>,"
        "   field_arr_10: ArrayOf<Float>,"
        "   field_arr_11: ArrayOf<Float32>,"
        "   field_arr_12: ArrayOf<Float64>,"
        " "
        ""
    );

    // invalid type Float16
    EXPECT_FAIL(
        "schema SomeSchema {"
        "   field_1 : Rid,"
        "   field_2 : String,"
        "   field_3 : Boolean,"
        "   field_4 : DateTime,"
        "   field_5 : Integer,"
        "   field_6 : Integer8,"
        "   field_7 : Integer16,"
        "   field_8 : Integer32,"
        "   field_9 : Integer64,"
        "   field_10: Float,"
        "   field_11: Float16,"
        "   field_12: Float64,"
        " "
        "   field_opt_1 : Rid?,"
        "   field_opt_2 : String?,"
        "   field_opt_3 : Boolean?,"
        "   field_opt_4 : DateTime?,"
        "   field_opt_5 : Integer?,"
        "   field_opt_6 : Integer8?,"
        "   field_opt_7 : Integer16?,"
        "   field_opt_8 : Integer32?,"
        "   field_opt_9 : Integer64?,"
        "   field_opt_10: Float?,"
        "   field_opt_11: Float32?,"
        "   field_opt_12: Float64?,"
        " "
        "   field_arr_1 : ArrayOf<Rid>,"
        "   field_arr_2 : ArrayOf<String>,"
        "   field_arr_3 : ArrayOf<Boolean>,"
        "   field_arr_4 : ArrayOf<DateTime>,"
        "   field_arr_5 : ArrayOf<Integer>,"
        "   field_arr_6 : ArrayOf<Integer8>,"
        "   field_arr_7 : ArrayOf<Integer16>,"
        "   field_arr_8 : ArrayOf<Integer32>,"
        "   field_arr_9 : ArrayOf<Integer64>,"
        "   field_arr_10: ArrayOf<Float>,"
        "   field_arr_11: ArrayOf<Float32>,"
        "   field_arr_12: ArrayOf<Float64>,"
        " "
        "}"
    );

    // invalid type specifier '!'
    EXPECT_FAIL(
        "schema SomeSchema {"
        "   field_1 : Rid,"
        "   field_2 : String,"
        "   field_3 : Boolean,"
        "   field_4 : DateTime,"
        "   field_5 : Integer,"
        "   field_6 : Integer8,"
        "   field_7  Integer16,"
        "   field_8 : Integer32,"
        "   field_9 : Integer64,"
        "   field_10: Float,"
        "   field_11: Float32,"
        "   field_12: Float64,"
        " "
        "   field_opt_1 : Rid?,"
        "   field_opt_2 : String?,"
        "   field_opt_3 : Boolean?,"
        "   field_opt_4 : DateTime?,"
        "   field_opt_5 : Integer?,"
        "   field_opt_6 : Integer8?,"
        "   field_opt_7 : Integer16?,"
        "   field_opt_8 : Integer32?,"
        "   field_opt_9 : Integer64!,"
        "   field_opt_10: Float?,"
        "   field_opt_11: Float32??,"
        "   field_opt_12: Float64?,"
        " "
        "   field_arr_1 : ArrayOf<Rid>,"
        "   field_arr_2 : ArrayOf<String>,"
        "   field_arr_3 : ArrayOf<Boolean>,"
        "   field_arr_4 : ArrayOf<DateTime>,"
        "   field_arr_5 : ArrayOf<Integer>,"
        "   field_arr_6 : ArrayOf<Integer8>,"
        "   field_arr_7 : ArrayOf<Integer16>,"
        "   field_arr_8 : ArrayOf<Integer32>,"
        "   field_arr_9 : ArrayOf<Integer64>,"
        "   field_arr_10: ArrayOf<Float>,"
        "   field_arr_11: ArrayOf<Float32>,"
        "   field_arr_12: ArrayOf<Float64>,"
        " "
        "}"
    );

    // missing ',' (Boolean)
    EXPECT_FAIL(
        "schema SomeSchema {"
        "   field_1 : Rid,"
        "   field_2 : String,"
        "   field_3 : Boolean"
        "   field_4 : DateTime,"
        "   field_5 : Integer,"
        "   field_6 : Integer8,"
        "   field_7 : Integer16,"
        "   field_8 : Integer32,"
        "   field_9 : Integer64,"
        "   field_10: Float,"
        "   field_11: Float32,"
        "   field_12: Float64,"
        " "
        "   field_opt_1 : Rid?,"
        "   field_opt_2 : String?,"
        "   field_opt_3 : Boolean?,"
        "   field_opt_4 : DateTime?,"
        "   field_opt_5 : Integer?,"
        "   field_opt_6 : Integer8?,"
        "   field_opt_7 : Integer16?,"
        "   field_opt_8 : Integer32?,"
        "   field_opt_9 : Integer64?,"
        "   field_opt_10: Float?,"
        "   field_opt_11: Float32?,"
        "   field_opt_12: Float64?,"
        " "
        "   field_arr_1 : ArrayOf<Rid>,"
        "   field_arr_2 : ArrayOf<String>,"
        "   field_arr_3 : ArrayOf<Boolean>,"
        "   field_arr_4 : ArrayOf<DateTime>,"
        "   field_arr_5 : ArrayOf<Integer>,"
        "   field_arr_6 : ArrayOf<Integer8>,"
        "   field_arr_7 : ArrayOf<Integer16>,"
        "   field_arr_8 : ArrayOf<Integer32>,"
        "   field_arr_9 : ArrayOf<Integer64>,"
        "   field_arr_10: ArrayOf<Float>,"
        "   field_arr_11: ArrayOf<Float32>,"
        "   field_arr_12: ArrayOf<Float64>,"
        " "
        "}"
    );

    // missing '<'
    EXPECT_FAIL(
        "schema SomeSchema {"
        "   field_1 : Rid,"
        "   field_2 : String,"
        "   field_3 : Boolean"
        "   field_4 : DateTime,"
        "   field_5 : Integer,"
        "   field_6 : Integer8,"
        "   field_7 : Integer16,"
        "   field_8 : Integer32,"
        "   field_9 : Integer64,"
        "   field_10: Float,"
        "   field_11: Float32,"
        "   field_12: Float64,"
        " "
        "   field_opt_1 : Rid?,"
        "   field_opt_2 : String?,"
        "   field_opt_3 : Boolean?,"
        "   field_opt_4 : DateTime?,"
        "   field_opt_5 : Integer?,"
        "   field_opt_6 : Integer8?,"
        "   field_opt_7 : Integer16?,"
        "   field_opt_8 : Integer32?,"
        "   field_opt_9 : Integer64?,"
        "   field_opt_10: Float?,"
        "   field_opt_11: Float32?,"
        "   field_opt_12: Float64?,"
        " "
        "   field_arr_1 : ArrayOf<Rid>,"
        "   field_arr_2 : ArrayOf<String>,"
        "   field_arr_3 : ArrayOf<Boolean,"
        "   field_arr_4 : ArrayOf<DateTime>,"
        "   field_arr_5 : ArrayOf<Integer>,"
        "   field_arr_6 : ArrayOf Integer8>,"
        "   field_arr_7 : ArrayOf<Integer16>,"
        "   field_arr_8 : ArrayOf<Integer32>,"
        "   field_arr_9 : ArrayOf<Integer64>,"
        "   field_arr_10: ArrayOf<Float>,"
        "   field_arr_11: ArrayOf<Float32>,"
        "   field_arr_12: ArrayOf<Float64>,"
        " "
        "}"
    );

    // missing '>'
    EXPECT_FAIL(
        "schema SomeSchema {"
        "   field_1 : Rid,"
        "   field_2 : String,"
        "   field_3 : Boolean"
        "   field_4 : DateTime,"
        "   field_5 : Integer,"
        "   field_6 : Integer8,"
        "   field_7 : Integer16,"
        "   field_8 : Integer32,"
        "   field_9 : Integer64,"
        "   field_10: Float,"
        "   field_11: Float32,"
        "   field_12: Float64,"
        " "
        "   field_opt_1 : Rid?,"
        "   field_opt_2 : String?,"
        "   field_opt_3 : Boolean?,"
        "   field_opt_4 : DateTime?,"
        "   field_opt_5 : Integer?,"
        "   field_opt_6 : Integer8?,"
        "   field_opt_7 : Integer16?,"
        "   field_opt_8 : Integer32?,"
        "   field_opt_9 : Integer64?,"
        "   field_opt_10: Float?,"
        "   field_opt_11: Float32?,"
        "   field_opt_12: Float64?,"
        " "
        "   field_arr_1 : ArrayOf<Rid>,"
        "   field_arr_2 : ArrayOf<String>,"
        "   field_arr_3 : ArrayOf<Boolean>,"
        "   field_arr_4 : ArrayOf<DateTime>,"
        "   field_arr_5 : ArrayOf<Integer>,"
        "   field_arr_6 : ArrayOf<Integer8>,"
        "   field_arr_7 : ArrayOf<Integer16>,"
        "   field_arr_8 : ArrayOf<Integer32>,"
        "   field_arr_9 : ArrayOf<Integer64>,"
        "   field_arr_10: ArrayOf<Float,"
        "   field_arr_11: ArrayOf<Float32>,"
        "   field_arr_12: ArrayOf<Float64>,"
        " "
        "}"
    );

    // missing 'of'
    EXPECT_FAIL(
        "schema SomeSchema {"
        "   field_1 : Rid,"
        "   field_2 : String,"
        "   field_3 : Boolean"
        "   field_4 : DateTime,"
        "   field_5 : Integer,"
        "   field_6 : Integer8,"
        "   field_7 : Integer16,"
        "   field_8 : Integer32,"
        "   field_9 : Integer64,"
        "   field_10: Float,"
        "   field_11: Float32,"
        "   field_12: Float64,"
        " "
        "   field_opt_1 : Rid?,"
        "   field_opt_2 : String?,"
        "   field_opt_3 : Boolean?,"
        "   field_opt_4 : DateTime?,"
        "   field_opt_5 : Integer?,"
        "   field_opt_6 : Integer8?,"
        "   field_opt_7 : Integer16?,"
        "   field_opt_8 : Integer32?,"
        "   field_opt_9 : Integer64?,"
        "   field_opt_10: Float?,"
        "   field_opt_11: Float32?,"
        "   field_opt_12: Float64?,"
        " "
        "   field_arr_1 : ArrayOf<Rid>,"
        "   field_arr_2 : ArrayOf<String>,"
        "   field_arr_3 : ArrayOf<Boolean>,"
        "   field_arr_4 : ArrayOf<DateTime>,"
        "   field_arr_5 : ArrayOf<Integer>,"
        "   field_arr_6 : ArrayOf<Integer8>,"
        "   field_arr_7 : ArrayOf<Integer16>,"
        "   field_arr_8 : ArrayOf<Integer32>,"
        "   field_arr_9 : ArrayOf<Integer64>,"
        "   field_arr_10: ArrayOf<Float>,"
        "   field_arr_11: Array <Float32>,"
        "   field_arr_12: ArrayOf<Float64>,"
        " "
        "}"
    );

    // invalid 'of'
    EXPECT_FAIL(
        "schema SomeSchema {"
        "   field_1 : Rid,"
        "   field_2 : String,"
        "   field_3 : Boolean"
        "   field_4 : DateTime,"
        "   field_5 : Integer,"
        "   field_6 : Integer8,"
        "   field_7 : Integer16,"
        "   field_8 : Integer32,"
        "   field_9 : Integer64,"
        "   field_10: Float,"
        "   field_11: Float32,"
        "   field_12: Float64,"
        " "
        "   field_opt_1 : Rid?,"
        "   field_opt_2 : String?,"
        "   field_opt_3 : Boolean?,"
        "   field_opt_4 : DateTime?,"
        "   field_opt_5 : Integer?,"
        "   field_opt_6 : Integer8?,"
        "   field_opt_7 : Integer16?,"
        "   field_opt_8 : Integer32?,"
        "   field_opt_9 : Integer64?,"
        "   field_opt_10: Float?,"
        "   field_opt_11: Float32?,"
        "   field_opt_12: Float64?,"
        " "
        "   field_arr_1 : ArrayOf<Rid>,"
        "   field_arr_2 : ArrayOf<String>,"
        "   field_arr_3 : ArrayOf<Boolean>,"
        "   field_arr_4 : ArrayOf<DateTime>,"
        "   field_arr_5 : ArrayOf<Integer>,"
        "   field_arr_6 : Array<Integer8>,"
        "   field_arr_7 : ArrayOf<Integer16>,"
        "   field_arr_8 : ArrayOf<Integer32>,"
        "   field_arr_9 : ArrayOf<Integer64>,"
        "   field_arr_10: ArrayOf<Float>,"
        "   field_arr_11: ArrayOf<Float32>,"
        "   field_arr_12: ArrayOf<Float64>,"
        " "
        "}"
    );

    // missing ':'
    EXPECT_FAIL(
        "schema SomeSchema {"
        "   field_1 : Rid,"
        "   field_2 : String,"
        "   field_3 : Boolean"
        "   field_4 : DateTime,"
        "   field_5 : Integer,"
        "   field_6 : Integer8,"
        "   field_7 : Integer16,"
        "   field_8 : Integer32,"
        "   field_9 : Integer64,"
        "   field_10: Float,"
        "   field_11: Float32,"
        "   field_12: Float64,"
        " "
        "   field_opt_1 : Rid?,"
        "   field_opt_2 : String?,"
        "   field_opt_3 : Boolean?,"
        "   field_opt_4  DateTime?,"
        "   field_opt_5 : Integer?,"
        "   field_opt_6 : Integer8?,"
        "   field_opt_7 : Integer16?,"
        "   field_opt_8 : Integer32?,"
        "   field_opt_9 : Integer64?,"
        "   field_opt_10: Float?,"
        "   field_opt_11: Float32?,"
        "   field_opt_12: Float64?,"
        " "
        "   field_arr_1 : ArrayOf<Rid>,"
        "   field_arr_2 : ArrayOf<String>,"
        "   field_arr_3 : ArrayOf<Boolean>,"
        "   field_arr_4 : ArrayOf<DateTime>,"
        "   field_arr_5 : ArrayOf<Integer>,"
        "   field_arr_6 : ArrayOf<Integer8>,"
        "   field_arr_7 : ArrayOf<Integer16>,"
        "   field_arr_8 : ArrayOf<Integer32>,"
        "   field_arr_9 : ArrayOf<Integer64>,"
        "   field_arr_10: ArrayOf<Float>,"
        "   field_arr_11: ArrayOf<Float32>,"
        "   field_arr_12: ArrayOf<Float64>,"
        " "
        "}"
    );
}

} // namespace LunarDB::Moonlight::Implementation::Tests
