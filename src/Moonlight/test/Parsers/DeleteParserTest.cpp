#include "QueryParserTest.hpp"

#define QUERY_TYPE Delete

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace Common::QueryData;

using Where = Init::WhereClauseInit;
using BooleanExpression = Init::WhereClauseInit::BooleanExpressionInit;
using BinaryExpression = Init::WhereClauseInit::BinaryExpressionInit;
using BooleanOperator = Primitives::EBooleanOperator;
using BinaryOperator = Primitives::EBinaryOperator;

// clang-format off
TEST(Moonlight_DeleteParserTest, success01)
{
    auto const query =
        R"(delete from structure StructureName               )"
        R"(     where (                                      )"
        R"(         name like "*escu"                        )"
        R"(         and salary between 5500 and 6000         )"
        R"(         or (                                     )"
        R"(                !(                                )"
        R"(                   salary < 5000                  )"
        R"(                   or salary >= 5200              )"
        R"(                )                                 )"
        R"(                or salary > 6500                  )"
        R"(                and profession in [Prof1, Prof2]  )"
        R"(                or birth_date >= 10/20/1989       )"
        R"(             )                                    )"
        R"(      )                                           )";

    auto const expected = Init::DeleteInit{}
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
        ));

    EXPECT_SUCCESS(query, expected);
}

TEST(Moonlight_DeleteParserTest, fail01)
{
    EXPECT_FAIL(
        R"(delete from StructureName                         )"
        R"(     where (                                      )"
        R"(         name like "*escu"                        )"
        R"(         and salary between 5500 and 6000         )"
        R"(         or (                                     )"
        R"(                !(                                )"
        R"(                   salary < 5000                  )"
        R"(                   or salary >= 5200              )"
        R"(                )                                 )"
        R"(                or salary > 6500                  )"
        R"(                and profession in [Prof1, Prof2]  )"
        R"(                or birth_date >= 10/20/1989       )"
        R"(             )                                    )"
        R"(      )                                           )"
    );

    EXPECT_FAIL(
        R"(delete structure StructureName                    )"
        R"(     where (                                      )"
        R"(         name like "*escu"                        )"
        R"(         and salary between 5500 and 6000         )"
        R"(         or (                                     )"
        R"(                !(                                )"
        R"(                   salary < 5000                  )"
        R"(                   or salary >= 5200              )"
        R"(                )                                 )"
        R"(                or salary > 6500                  )"
        R"(                and profession in [Prof1, Prof2]  )"
        R"(                or birth_date >= 10/20/1989       )"
        R"(             )                                    )"
        R"(      )                                           )"
    );

    EXPECT_FAIL(
        R"(delete from structure                             )"
        R"(     where (                                      )"
        R"(         name like "*escu"                        )"
        R"(         and salary between 5500 and 6000         )"
        R"(         or (                                     )"
        R"(                !(                                )"
        R"(                   salary < 5000                  )"
        R"(                   or salary >= 5200              )"
        R"(                )                                 )"
        R"(                or salary > 6500                  )"
        R"(                and profession in [Prof1, Prof2]  )"
        R"(                or birth_date >= 10/20/1989       )"
        R"(             )                                    )"
        R"(      )                                           )"
    );
}
// clang-format on

} // namespace LunarDB::Moonlight::Implementation::Tests
