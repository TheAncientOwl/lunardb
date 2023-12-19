#include <gtest/gtest.h>

#include "QueryDataHelpers/Init.hpp"
#include "QueryDataHelpers/Operators.hpp"
#include "Common/Utils.hpp"
#include "Primitives.hpp"

namespace LunarDB::Moonlight::Utils::Tests {

using Where = QueryData::Init::WhereClauseInit;
using BooleanExpression = QueryData::Init::WhereClauseInit::BooleanExpressionInit;
using BinaryExpression = QueryData::Init::WhereClauseInit::BinaryExpressionInit;
using BooleanOperator = QueryData::Primitives::EBooleanOperator;
using BinaryOperator = QueryData::Primitives::EBinaryOperator;

TEST(UtilsWhereClauseTest, parseWhereClauseSuccess01)
{
    const auto where =
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

    const auto expected = Where{}.expression(
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
                BinaryExpression{}.negated(false).lhs("birth_date").operation(BinaryOperator::GreaterThanEqualTo).rhs("10/20/1989")
            })
            })
    );

    const auto out = Utils::parseWhereClause(where);

    EXPECT_EQ(out, expected);
}

TEST(UtilsWhereClauseTest, parseWhereClauseFail01)
{
    EXPECT_THROW(Utils::parseWhereClause(
        R"(     where (                                      )"
        R"(         name liske "*escu"                        )"
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
    ), std::runtime_error);

    EXPECT_THROW(Utils::parseWhereClause(
        R"(     where                                        )"
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
    ), std::runtime_error);


}

} // namespace LunarDB::Moonlight::Utils::Tests