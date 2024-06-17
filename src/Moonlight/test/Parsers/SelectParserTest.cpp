#include "QueryParserTest.hpp"

#define QUERY_TYPE Select

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace Common::QueryData;

using Where = Init::WhereClauseInit;
using BooleanExpression = Init::WhereClauseInit::BooleanExpressionInit;
using BinaryExpression = Init::WhereClauseInit::BinaryExpressionInit;
using BooleanOperator = Primitives::EBooleanOperator;
using BinaryOperator = Primitives::EBinaryOperator;

// clang-format off
TEST(Moonlight_SelectParserTest, success01)
{
    auto const query =
        R"(select from structure StructureName                    )"
        R"(     where (                                           )"
        R"(         name like "*escu"                             )"
        R"(         and salary between 5500 and 6000              )"
        R"(         or (                                          )"
        R"(                !(                                     )"
        R"(                   salary < 5000                       )"
        R"(                   or salary >= 5200                   )"
        R"(                )                                      )"
        R"(                or salary > 6500                       )"
        R"(                and profession in [Prof1, Prof2]       )"
        R"(                or birth_date >= 10/20/1989            )"
        R"(             )                                         )"
        R"(      )                                                )"
        R"(     fields [ field1, field2, field3, field4 ]         )";

    auto const expected = Init::SelectInit{}
        .from("StructureName")
        .where(Where{}.expression(
            BooleanExpression{}
            .negated(false)
            .data({
                BinaryExpression{}.negated(false).lhs("name").operation(BinaryOperator::Like).rhs("*escu"),
                BooleanOperator::And,
                BinaryExpression{}.negated(false).lhs("salary").operation(BinaryOperator::Between).rhs("5500 and 6000"),
                BooleanOperator::Or,
                BooleanExpression{}.negated(false).data({
                    BooleanExpression{}.negated(true).data({
                        BinaryExpression{}.negated(false).lhs("salary").operation(BinaryOperator::LessThan).rhs("5000"),
                        BooleanOperator::Or,
                        BinaryExpression{}.negated(false).lhs("salary").operation(BinaryOperator::GreaterThanEqualTo).rhs("5200"),
                    }),
                    BooleanOperator::Or,
                    BinaryExpression{}.negated(false).lhs("salary").operation(BinaryOperator::GreaterThan).rhs("6500"),
                    BooleanOperator::And,
                    BinaryExpression{}.negated(false).lhs("profession").operation(BinaryOperator::In).rhs("[Prof1, Prof2]"),
                    BooleanOperator::Or,
                    BinaryExpression{}.negated(false).lhs("birth_date").operation(BinaryOperator::GreaterThanEqualTo).rhs("10/20/1989")
                })
                })
        ))
        .fields(std::vector<std::string>{"field1", "field2", "field3", "field4"})
        .order_by({});

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_SelectParserTest, success02)
{
    auto const query =
        R"(select from structure StructureName                    )"
        R"(     where (                                           )"
        R"(         name like "*escu"                             )"
        R"(         and salary between 5500 and 6000              )"
        R"(         or (                                          )"
        R"(                !(                                     )"
        R"(                   salary < 5000                       )"
        R"(                   or salary >= 5200                   )"
        R"(                )                                      )"
        R"(                or salary > 6500                       )"
        R"(                and profession in [Prof1, Prof2]       )"
        R"(                or birth_date >= 10/20/1989            )"
        R"(             )                                         )"
        R"(      )                                                )"
        R"(     fields [ field1, field2, field3, field4 ]         )"
        R"(     order by [ field1 asc, field2 desc, field3 asc ]  )";

    auto const expected = Init::SelectInit{}
        .from("StructureName")
        .where(Where{}.expression(
            BooleanExpression{}
            .negated(false)
            .data({
                BinaryExpression{}.negated(false).lhs("name").operation(BinaryOperator::Like).rhs("*escu"),
                BooleanOperator::And,
                BinaryExpression{}.negated(false).lhs("salary").operation(BinaryOperator::Between).rhs("5500 and 6000"),
                BooleanOperator::Or,
                BooleanExpression{}.negated(false).data({
                    BooleanExpression{}.negated(true).data({
                        BinaryExpression{}.negated(false).lhs("salary").operation(BinaryOperator::LessThan).rhs("5000"),
                        BooleanOperator::Or,
                        BinaryExpression{}.negated(false).lhs("salary").operation(BinaryOperator::GreaterThanEqualTo).rhs("5200"),
                    }),
                    BooleanOperator::Or,
                    BinaryExpression{}.negated(false).lhs("salary").operation(BinaryOperator::GreaterThan).rhs("6500"),
                    BooleanOperator::And,
                    BinaryExpression{}.negated(false).lhs("profession").operation(BinaryOperator::In).rhs("[Prof1, Prof2]"),
                    BooleanOperator::Or,
                    BinaryExpression{}.negated(false).lhs("birth_date").operation(BinaryOperator::GreaterThanEqualTo).rhs("10/20/1989")
                })
                })
        ))
        .fields(std::vector<std::string>{"field1", "field2", "field3", "field4"})
        .order_by(std::vector<Common::QueryData::Select::Order>{
        Init::SelectInit::OrderInit{}.field("field1").type(Primitives::EOrderType::Asc),
            Init::SelectInit::OrderInit{}.field("field2").type(Primitives::EOrderType::Desc),
            Init::SelectInit::OrderInit{}.field("field3").type(Primitives::EOrderType::Asc),
    });

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_SelectParserTest, fail01)
{
    // missing from
    EXPECT_FAIL(
        R"(select structure StructureName                         )"
        R"(     where (                                           )"
        R"(         name like "*escu"                             )"
        R"(         and salary between 5500 and 6000              )"
        R"(         or (                                          )"
        R"(                !(                                     )"
        R"(                   salary < 5000                       )"
        R"(                   or salary >= 5200                   )"
        R"(                )                                      )"
        R"(                or salary > 6500                       )"
        R"(                and profession in [Prof1, Prof2]       )"
        R"(                or birth_date >= 10/20/1989            )"
        R"(             )                                         )"
        R"(      )                                                )"
        R"(     fields [ field1, field2, field3, field4 ]         )"
        R"(     order by [ field1 asc, field2 desc, field3 asc ]  )"
    );

    // missing structure
    EXPECT_FAIL(
        R"(select from StructureName                              )"
        R"(     where (                                           )"
        R"(         name like "*escu"                             )"
        R"(         and salary between 5500 and 6000              )"
        R"(         or (                                          )"
        R"(                !(                                     )"
        R"(                   salary < 5000                       )"
        R"(                   or salary >= 5200                   )"
        R"(                )                                      )"
        R"(                or salary > 6500                       )"
        R"(                and profession in [Prof1, Prof2]       )"
        R"(                or birth_date >= 10/20/1989            )"
        R"(             )                                         )"
        R"(      )                                                )"
        R"(     fields [ field1, field2, field3, field4 ]         )"
        R"(     order by [ field1 asc, field2 desc, field3 asc ]  )"
    );

    // missing structure name
    EXPECT_FAIL(
        R"(select from structure                                  )"
        R"(     where (                                           )"
        R"(         name like "*escu"                             )"
        R"(         and salary between 5500 and 6000              )"
        R"(         or (                                          )"
        R"(                !(                                     )"
        R"(                   salary < 5000                       )"
        R"(                   or salary >= 5200                   )"
        R"(                )                                      )"
        R"(                or salary > 6500                       )"
        R"(                and profession in [Prof1, Prof2]       )"
        R"(                or birth_date >= 10/20/1989            )"
        R"(             )                                         )"
        R"(      )                                                )"
        R"(     fields [ field1, field2, field3, field4 ]         )"
        R"(     order by [ field1 asc, field2 desc, field3 asc ]  )"
    );

    // whitespace in structure name
    EXPECT_FAIL(
        R"(select from structure Structure Name                   )"
        R"(     where (                                           )"
        R"(         name like "*escu"                             )"
        R"(         and salary between 5500 and 6000              )"
        R"(         or (                                          )"
        R"(                !(                                     )"
        R"(                   salary < 5000                       )"
        R"(                   or salary >= 5200                   )"
        R"(                )                                      )"
        R"(                or salary > 6500                       )"
        R"(                and profession in [Prof1, Prof2]       )"
        R"(                or birth_date >= 10/20/1989            )"
        R"(             )                                         )"
        R"(      )                                                )"
        R"(     fields [ field1, field2, field3, field4 ]         )"
        R"(     order by [ field1 asc, field2 desc, field3 asc ]  )"
    );

    // missing fields '['
    EXPECT_FAIL(
        R"(select from structure StructureName                    )"
        R"(     where (                                           )"
        R"(         name like "*escu"                             )"
        R"(         and salary between 5500 and 6000              )"
        R"(         or (                                          )"
        R"(                !(                                     )"
        R"(                   salary < 5000                       )"
        R"(                   or salary >= 5200                   )"
        R"(                )                                      )"
        R"(                or salary > 6500                       )"
        R"(                and profession in [Prof1, Prof2]       )"
        R"(                or birth_date >= 10/20/1989            )"
        R"(             )                                         )"
        R"(      )                                                )"
        R"(     fields field1, field2, field3, field4 ]           )"
        R"(     order by [ field1 asc, field2 desc, field3 asc ]  )"
    );

    // missing fields ']'
    EXPECT_FAIL(
        R"(select from structure StructureName                    )"
        R"(     where (                                           )"
        R"(         name like "*escu"                             )"
        R"(         and salary between 5500 and 6000              )"
        R"(         or (                                          )"
        R"(                !(                                     )"
        R"(                   salary < 5000                       )"
        R"(                   or salary >= 5200                   )"
        R"(                )                                      )"
        R"(                or salary > 6500                       )"
        R"(                and profession in [Prof1, Prof2]       )"
        R"(                or birth_date >= 10/20/1989            )"
        R"(             )                                         )"
        R"(      )                                                )"
        R"(     fields [ field1, field2, field3, field4           )"
        R"(     order by [ field1 asc, field2 desc, field3 asc ]  )"
    );

    // missing fields
    EXPECT_FAIL(
        R"(select from structure StructureName                    )"
        R"(     where (                                           )"
        R"(         name like "*escu"                             )"
        R"(         and salary between 5500 and 6000              )"
        R"(         or (                                          )"
        R"(                !(                                     )"
        R"(                   salary < 5000                       )"
        R"(                   or salary >= 5200                   )"
        R"(                )                                      )"
        R"(                or salary > 6500                       )"
        R"(                and profession in [Prof1, Prof2]       )"
        R"(                or birth_date >= 10/20/1989            )"
        R"(             )                                         )"
        R"(      )                                                )"
        R"(      [ field1, field2, field3, field4 ]               )"
        R"(     order by [ field1 asc, field2 desc, field3 asc ]  )"
    );

    // missing fields ','
    EXPECT_FAIL(
        R"(select from structure StructureName                    )"
        R"(     where (                                           )"
        R"(         name like "*escu"                             )"
        R"(         and salary between 5500 and 6000              )"
        R"(         or (                                          )"
        R"(                !(                                     )"
        R"(                   salary < 5000                       )"
        R"(                   or salary >= 5200                   )"
        R"(                )                                      )"
        R"(                or salary > 6500                       )"
        R"(                and profession in [Prof1, Prof2]       )"
        R"(                or birth_date >= 10/20/1989            )"
        R"(             )                                         )"
        R"(      )                                                )"
        R"(     fields [ field1 field2, field3, field4 ]          )"
        R"(     order by [ field1 asc, field2 desc, field3 asc ]  )"
    );

    // fields empty array
    EXPECT_FAIL(
        R"(select from structure StructureName                    )"
        R"(     where (                                           )"
        R"(         name like "*escu"                             )"
        R"(         and salary between 5500 and 6000              )"
        R"(         or (                                          )"
        R"(                !(                                     )"
        R"(                   salary < 5000                       )"
        R"(                   or salary >= 5200                   )"
        R"(                )                                      )"
        R"(                or salary > 6500                       )"
        R"(                and profession in [Prof1, Prof2]       )"
        R"(                or birth_date >= 10/20/1989            )"
        R"(             )                                         )"
        R"(      )                                                )"
        R"(     fields [  ]                                       )"
        R"(     order by [ field1 asc, field2 desc, field3 asc ]  )"
    );

    // missing fields entirerly
    EXPECT_FAIL(
        R"(select from structure StructureName                    )"
        R"(     where (                                           )"
        R"(         name like "*escu"                             )"
        R"(         and salary between 5500 and 6000              )"
        R"(         or (                                          )"
        R"(                !(                                     )"
        R"(                   salary < 5000                       )"
        R"(                   or salary >= 5200                   )"
        R"(                )                                      )"
        R"(                or salary > 6500                       )"
        R"(                and profession in [Prof1, Prof2]       )"
        R"(                or birth_date >= 10/20/1989            )"
        R"(             )                                         )"
        R"(      )                                                )"
        R"(     order by [ field1 asc, field2 desc, field3 asc ]  )"
    );

    // missing order
    EXPECT_FAIL(
        R"(select from structure StructureName                    )"
        R"(     where (                                           )"
        R"(         name like "*escu"                             )"
        R"(         and salary between 5500 and 6000              )"
        R"(         or (                                          )"
        R"(                !(                                     )"
        R"(                   salary < 5000                       )"
        R"(                   or salary >= 5200                   )"
        R"(                )                                      )"
        R"(                or salary > 6500                       )"
        R"(                and profession in [Prof1, Prof2]       )"
        R"(                or birth_date >= 10/20/1989            )"
        R"(             )                                         )"
        R"(      )                                                )"
        R"(     fields [ field1, field2, field3, field4 ]         )"
        R"(     by [ field1 asc, field2 desc, field3 asc ]        )"
    );

    // missing by
    EXPECT_FAIL(
        R"(select from structure StructureName                    )"
        R"(     where (                                           )"
        R"(         name like "*escu"                             )"
        R"(         and salary between 5500 and 6000              )"
        R"(         or (                                          )"
        R"(                !(                                     )"
        R"(                   salary < 5000                       )"
        R"(                   or salary >= 5200                   )"
        R"(                )                                      )"
        R"(                or salary > 6500                       )"
        R"(                and profession in [Prof1, Prof2]       )"
        R"(                or birth_date >= 10/20/1989            )"
        R"(             )                                         )"
        R"(      )                                                )"
        R"(     fields [ field1, field2, field3, field4 ]         )"
        R"(     order [ field1 asc, field2 desc, field3 asc ]     )"
    );

    // missing order by '['
    EXPECT_FAIL(
        R"(select from structure StructureName                    )"
        R"(     where (                                           )"
        R"(         name like "*escu"                             )"
        R"(         and salary between 5500 and 6000              )"
        R"(         or (                                          )"
        R"(                !(                                     )"
        R"(                   salary < 5000                       )"
        R"(                   or salary >= 5200                   )"
        R"(                )                                      )"
        R"(                or salary > 6500                       )"
        R"(                and profession in [Prof1, Prof2]       )"
        R"(                or birth_date >= 10/20/1989            )"
        R"(             )                                         )"
        R"(      )                                                )"
        R"(     fields [ field1, field2, field3, field4 ]         )"
        R"(     order by  field1 asc, field2 desc, field3 asc ]   )"
    );

    // missing order by ']'
    EXPECT_FAIL(
        R"(select from structure StructureName                    )"
        R"(     where (                                           )"
        R"(         name like "*escu"                             )"
        R"(         and salary between 5500 and 6000              )"
        R"(         or (                                          )"
        R"(                !(                                     )"
        R"(                   salary < 5000                       )"
        R"(                   or salary >= 5200                   )"
        R"(                )                                      )"
        R"(                or salary > 6500                       )"
        R"(                and profession in [Prof1, Prof2]       )"
        R"(                or birth_date >= 10/20/1989            )"
        R"(             )                                         )"
        R"(      )                                                )"
        R"(     fields [ field1, field2, field3, field4 ]         )"
        R"(     order by [ field1 asc, field2 desc, field3 asc    )"
    );

    // missing order by ','
    EXPECT_FAIL(
        R"(select from structure StructureName                    )"
        R"(     where (                                           )"
        R"(         name like "*escu"                             )"
        R"(         and salary between 5500 and 6000              )"
        R"(         or (                                          )"
        R"(                !(                                     )"
        R"(                   salary < 5000                       )"
        R"(                   or salary >= 5200                   )"
        R"(                )                                      )"
        R"(                or salary > 6500                       )"
        R"(                and profession in [Prof1, Prof2]       )"
        R"(                or birth_date >= 10/20/1989            )"
        R"(             )                                         )"
        R"(      )                                                )"
        R"(     fields [ field1, field2, field3, field4 ]         )"
        R"(     order by [ field1 asc field2 desc, field3 asc ]   )"
    );

    // missing order by field name
    EXPECT_FAIL(
        R"(select from structure StructureName                    )"
        R"(     where (                                           )"
        R"(         name like "*escu"                             )"
        R"(         and salary between 5500 and 6000              )"
        R"(         or (                                          )"
        R"(                !(                                     )"
        R"(                   salary < 5000                       )"
        R"(                   or salary >= 5200                   )"
        R"(                )                                      )"
        R"(                or salary > 6500                       )"
        R"(                and profession in [Prof1, Prof2]       )"
        R"(                or birth_date >= 10/20/1989            )"
        R"(             )                                         )"
        R"(      )                                                )"
        R"(     fields [ field1, field2, field3, field4 ]         )"
        R"(     order by [ asc, field2 desc, field3 asc ]         )"
    );

    // missing order by field order specifier
    EXPECT_FAIL(
        R"(select from structure StructureName                    )"
        R"(     where (                                           )"
        R"(         name like "*escu"                             )"
        R"(         and salary between 5500 and 6000              )"
        R"(         or (                                          )"
        R"(                !(                                     )"
        R"(                   salary < 5000                       )"
        R"(                   or salary >= 5200                   )"
        R"(                )                                      )"
        R"(                or salary > 6500                       )"
        R"(                and profession in [Prof1, Prof2]       )"
        R"(                or birth_date >= 10/20/1989            )"
        R"(             )                                         )"
        R"(      )                                                )"
        R"(     fields [ field1, field2, field3, field4 ]         )"
        R"(     order by [ field1 , field2 desc, field3 asc ]     )"
    );

    // missing order by field order specifier and ','
    EXPECT_FAIL(
        R"(select from structure StructureName                    )"
        R"(     where (                                           )"
        R"(         name like "*escu"                             )"
        R"(         and salary between 5500 and 6000              )"
        R"(         or (                                          )"
        R"(                !(                                     )"
        R"(                   salary < 5000                       )"
        R"(                   or salary >= 5200                   )"
        R"(                )                                      )"
        R"(                or salary > 6500                       )"
        R"(                and profession in [Prof1, Prof2]       )"
        R"(                or birth_date >= 10/20/1989            )"
        R"(             )                                         )"
        R"(      )                                                )"
        R"(     fields [ field1, field2, field3, field4 ]         )"
        R"(     order by [ field1  field2 desc, field3 asc ]      )"
    );

    // missing order by order ',' and field name
    EXPECT_FAIL(
        R"(select from structure StructureName                    )"
        R"(     where (                                           )"
        R"(         name like "*escu"                             )"
        R"(         and salary between 5500 and 6000              )"
        R"(         or (                                          )"
        R"(                !(                                     )"
        R"(                   salary < 5000                       )"
        R"(                   or salary >= 5200                   )"
        R"(                )                                      )"
        R"(                or salary > 6500                       )"
        R"(                and profession in [Prof1, Prof2]       )"
        R"(                or birth_date >= 10/20/1989            )"
        R"(             )                                         )"
        R"(      )                                                )"
        R"(     fields [ field1, field2, field3, field4 ]         )"
        R"(     order by [ field1 asc desc, field3 asc ]          )"
    );

    // occurence(field name) in order by > 1
    EXPECT_FAIL(
        R"(select from structure StructureName                                 )"
        R"(     where (                                                        )"
        R"(         name like "*escu"                                          )"
        R"(         and salary between 5500 and 6000                           )"
        R"(         or (                                                       )"
        R"(                !(                                                  )"
        R"(                   salary < 5000                                    )"
        R"(                   or salary >= 5200                                )"
        R"(                )                                                   )"
        R"(                or salary > 6500                                    )"
        R"(                and profession in [Prof1, Prof2]                    )"
        R"(                or birth_date >= 10/20/1989                         )"
        R"(             )                                                      )"
        R"(      )                                                             )"
        R"(     fields [ field1, field2, field3, field4 ]                      )"
        R"(     order by [ field1 asc, field2 desc, field1 desc, field3 asc ]  )"
    );
}
// clang-format on

} // namespace LunarDB::Moonlight::Implementation::Tests
