#include <gtest/gtest.h>

#include "QueryDataHelpers/Init.hpp"
#include "QueryDataHelpers/Operators.hpp"
#include "ParsedQuery.hpp"

#define EXPECT_SUCCESS(query, expected) \
    const auto out = API::ParsedQuery::from(query).get<Update>(); \
    EXPECT_EQ(out, expected)

#define EXPECT_FAIL(query) \
    EXPECT_THROW(API::ParsedQuery::from(query).get<Update>(), std::runtime_error)

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

using Where = Init::WhereClauseInit;
using BooleanExpression = Init::WhereClauseInit::BooleanExpressionInit;
using BinaryExpression = Init::WhereClauseInit::BinaryExpressionInit;
using BooleanOperator = Primitives::EBooleanOperator;
using BinaryOperator = Primitives::EBinaryOperator;

TEST(UpdateParserTest, success01)
{
    const auto query =
        R"(update structure StructureName                    )"
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
        R"(     modify [                                     )"
        R"(         field1 => field1 * 1.5 + 2,              )"
        R"(         field2 => field3 + "_some_suffix"        )"
        R"(     ]                                            )";

    const auto expected = Init::UpdateInit{}
        .structure_name("StructureName")
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
                    BinaryExpression{}.negated(false).lhs("birth_date").operation(BinaryOperator::GreaterThanEqualTo).rhs("10/20/1989")
                })
                })
        ))
        .modify(std::vector<Update::Modify>{
        Init::UpdateInit::ModifyInit{}.field("field1").expression("field1 * 1.5 + 2"),
            Init::UpdateInit::ModifyInit{}.field("field2").expression(R"(field3 + "some_suffix")")
    });

    EXPECT_SUCCESS(query, expected);
}

TEST(UpdateParserTest, fail01)
{
    // same field twice
    EXPECT_FAIL(
        R"(update structure StructureName                    )"
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
        R"(     modify [                                     )"
        R"(         field1 => field1 * 1.5 + 2,              )"
        R"(         field2 => field3 + "_some_suffix",       )"
        R"(         field1 => field1 * 1.5                   )"
        R"(     ]                                            )"
    );

    // missing 'structure'
    EXPECT_FAIL(
        R"(update StructureName                              )"
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
        R"(     modify [                                     )"
        R"(         field1 => field1 * 1.5 + 2,              )"
        R"(         field2 => field3 + "_some_suffix"        )"
        R"(     ]                                            )"
    );

    // missing structure name
    EXPECT_FAIL(
        R"(update structure                                  )"
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
        R"(     modify [                                     )"
        R"(         field1 => field1 * 1.5 + 2,              )"
        R"(         field2 => field3 + "_some_suffix"        )"
        R"(     ]                                            )"
    );

    // missing 'modify'
    EXPECT_FAIL(
        R"(update structure StructureName                    )"
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
        R"(     [                                            )"
        R"(         field1 => field1 * 1.5 + 2,              )"
        R"(         field2 => field3 + "_some_suffix"        )"
        R"(     ]                                            )"
    );

    // missing modify '['
    EXPECT_FAIL(
        R"(update structure StructureName                    )"
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
        R"(     modify                                       )"
        R"(         field1 => field1 * 1.5 + 2,              )"
        R"(         field2 => field3 + "_some_suffix"        )"
        R"(     ]                                            )"
    );

    // missing modify ']'
    EXPECT_FAIL(
        R"(update structure StructureName                    )"
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
        R"(     modify [                                     )"
        R"(         field1 => field1 * 1.5 + 2,              )"
        R"(         field2 => field3 + "_some_suffix"        )"
        R"(                                                  )"
    );

    // missing modify ','
    EXPECT_FAIL(
        R"(update structure StructureName                    )"
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
        R"(     modify [                                     )"
        R"(         field1 => field1 * 1.5 + 2               )"
        R"(         field2 => field3 + "_some_suffix"        )"
        R"(     ]                                            )"
    );

    // missing modify '='
    EXPECT_FAIL(
        R"(update structure StructureName                    )"
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
        R"(     modify [                                     )"
        R"(         field1 => field1 * 1.5 + 2,              )"
        R"(         field2 > field3 + "_some_suffix"         )"
        R"(     ]                                            )"
    );

    // missing modify '>'
    EXPECT_FAIL(
        R"(update structure StructureName                    )"
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
        R"(     modify [                                     )"
        R"(         field1 = field1 * 1.5 + 2,               )"
        R"(         field2 => field3 + "_some_suffix"        )"
        R"(     ]                                            )"
    );

    // missing modify field name
    EXPECT_FAIL(
        R"(update structure StructureName                    )"
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
        R"(     modify [                                     )"
        R"(         => field1 * 1.5 + 2,                     )"
        R"(         field2 => field3 + "_some_suffix"        )"
        R"(     ]                                            )"
    );

    // missing modify expression
    EXPECT_FAIL(
        R"(update structure StructureName                    )"
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
        R"(     modify [                                     )"
        R"(         field1 => ,                              )"
        R"(         field2 => field3 + "_some_suffix"        )"
        R"(     ]                                            )"
    );

    // missing field expression and ','
    EXPECT_FAIL(
        R"(update structure StructureName                    )"
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
        R"(     modify [                                     )"
        R"(         field1 =>                                )"
        R"(         field2 => field3 + "_some_suffix"        )"
        R"(     ]                                            )"
    );

    // missing field expression and ',' and '=>'
    EXPECT_FAIL(
        R"(update structure StructureName                    )"
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
        R"(     modify [                                     )"
        R"(         field1                                   )"
        R"(         field2 => field3 + "_some_suffix"        )"
        R"(     ]                                            )"
    );

    // missing field expression at the end
    EXPECT_FAIL(
        R"(update structure StructureName                    )"
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
        R"(     modify [                                     )"
        R"(         field1 => field1 * 1.5 + 2,              )"
        R"(         field2 =>                                )"
        R"(     ]                                            )"
    );

    // missing field expression and '=>' at the end
    EXPECT_FAIL(
        R"(update structure StructureName                    )"
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
        R"(     modify [                                     )"
        R"(         field1 => field1 * 1.5 + 2,              )"
        R"(         field2                                   )"
        R"(     ]                                            )"
    );

}

} // namespace LunarDB::Moonlight::Implementation::Tests
