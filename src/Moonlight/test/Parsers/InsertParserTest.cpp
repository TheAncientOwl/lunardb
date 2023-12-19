#include <gtest/gtest.h>

#include "QueryDataHelpers/Init.hpp"
#include "QueryDataHelpers/Operators.hpp"
#include "ParsedQuery.hpp"

#define EXPECT_SUCCESS(query, expected) \
    const auto out = API::ParsedQuery::from(query).get<Insert>(); \
    EXPECT_EQ(out, expected)

#define EXPECT_FAIL(query) \
    EXPECT_THROW(API::ParsedQuery::from(query).get<Insert>(), std::runtime_error)


namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

///
/// @note All parsing related to values should be handled by a json parser.
///
TEST(InsertParserTest, success01)
{
    const auto query =
        R"(insert into SomeStructure values [)"
        R"(    {                                              )"
        R"(         "salary": 4000,                           )"
        R"(         "name": "Bob",                            )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": 5                           )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": 4000,                           )"
        R"(         "name": "Bob",                            )"
        R"(         "rank": "HeadmasterSupreme",              )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": 5                           )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": 4000,                           )"
        R"(         "name": "Bob",                            )"
        R"(         "rank(String)" R"(): "HeadmasterSupreme", )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": 5                           )"
        R"(         }                                         )"
        R"(    }                                              )"
        R"(])";

    // TODO: use json instead of plain strings
    const auto expected = Init::InsertInit{}
        .into("SomeStructure")
        .values(std::vector<std::string>{
        R"(    {                                              )"
            R"(         "salary": 4000,                           )"
            R"(         "name": "Bob",                            )"
            R"(         "birth_date": "09/10/1985",               )"
            R"(         "address": {                              )"
            R"(             "street": "Some Street",              )"
            R"(             "number": 5                           )"
            R"(         }                                         )"
            R"(    }                                             )",

            R"(    {                                              )"
            R"(         "salary": 4000,                           )"
            R"(         "name": "Bob",                            )"
            R"(         "rank": "HeadmasterSupreme",              )"
            R"(         "birth_date": "09/10/1985",               )"
            R"(         "address": {                              )"
            R"(             "street": "Some Street",              )"
            R"(             "number": 5                           )"
            R"(         }                                         )"
            R"(    }                                              )",

            R"(    {                                              )"
            R"(         "salary": 4000,                           )"
            R"(         "name": "Bob",                            )"
            R"(         "rank(String)" R"(): "HeadmasterSupreme", )"
            R"(         "birth_date": "09/10/1985",               )"
            R"(         "address": {                              )"
            R"(             "street": "Some Street",              )"
            R"(             "number": 5                           )"
            R"(         }                                         )"
            R"(    }                                              )"
    });

    EXPECT_SUCCESS(query, expected);
}

///
/// @note All possible fails related to values should be handled by json parser.
///       All possible fails related to Moonlight insert syntax are handlede by this test.
///
TEST(InsertParserTest, fail01)
{
    // missing '['
    EXPECT_FAIL(
        R"(insert into SomeStructure values )"
        R"(    {                                              )"
        R"(         "salary": 4000,                           )"
        R"(         "name": "Bob",                            )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": 5                           )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": 4000,                           )"
        R"(         "name": "Bob",                            )"
        R"(         "rank": "HeadmasterSupreme",              )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": 5                           )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": 4000,                           )"
        R"(         "name": "Bob",                            )"
        R"(         "rank(String)" R"(): "HeadmasterSupreme", )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": 5                           )"
        R"(         }                                         )"
        R"(    }                                              )"
        R"(])"
    );

    // missing ']'
    EXPECT_FAIL(
        R"(insert into SomeStructure values [)"
        R"(    {                                              )"
        R"(         "salary": 4000,                           )"
        R"(         "name": "Bob",                            )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": 5                           )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": 4000,                           )"
        R"(         "name": "Bob",                            )"
        R"(         "rank": "HeadmasterSupreme",              )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": 5                           )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": 4000,                           )"
        R"(         "name": "Bob",                            )"
        R"(         "rank(String)" R"(): "HeadmasterSupreme", )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": 5                           )"
        R"(         }                                         )"
        R"(    }                                              )"
        R"()"
    );

    // missing 'into'
    EXPECT_FAIL(
        R"(insert SomeStructure values [)"
        R"(    {                                              )"
        R"(         "salary": 4000,                           )"
        R"(         "name": "Bob",                            )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": 5                           )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": 4000,                           )"
        R"(         "name": "Bob",                            )"
        R"(         "rank": "HeadmasterSupreme",              )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": 5                           )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": 4000,                           )"
        R"(         "name": "Bob",                            )"
        R"(         "rank(String)" R"(): "HeadmasterSupreme", )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": 5                           )"
        R"(         }                                         )"
        R"(    }                                              )"
        R"(])"
    );

    // missing 'values'
    EXPECT_FAIL(
        R"(insert into SomeStructure [)"
        R"(    {                                              )"
        R"(         "salary": 4000,                           )"
        R"(         "name": "Bob",                            )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": 5                           )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": 4000,                           )"
        R"(         "name": "Bob",                            )"
        R"(         "rank": "HeadmasterSupreme",              )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": 5                           )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": 4000,                           )"
        R"(         "name": "Bob",                            )"
        R"(         "rank(String)" R"(): "HeadmasterSupreme", )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": 5                           )"
        R"(         }                                         )"
        R"(    }                                              )"
        R"(])"
    );

    // missing structure name, should be the same case as the previous one
    // since 'values' here will be treated as a structure name.
    EXPECT_FAIL(
        R"(insert into values [)"
        R"(    {                                              )"
        R"(         "salary": 4000,                           )"
        R"(         "name": "Bob",                            )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": 5                           )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": 4000,                           )"
        R"(         "name": "Bob",                            )"
        R"(         "rank": "HeadmasterSupreme",              )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": 5                           )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": 4000,                           )"
        R"(         "name": "Bob",                            )"
        R"(         "rank(String)" R"(): "HeadmasterSupreme", )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": 5                           )"
        R"(         }                                         )"
        R"(    }                                              )"
        R"(])"
    );

    // space in structure name
    EXPECT_FAIL(
        R"(insert into Some Structure values [)"
        R"(    {                                              )"
        R"(         "salary": 4000,                           )"
        R"(         "name": "Bob",                            )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": 5                           )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": 4000,                           )"
        R"(         "name": "Bob",                            )"
        R"(         "rank": "HeadmasterSupreme",              )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": 5                           )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": 4000,                           )"
        R"(         "name": "Bob",                            )"
        R"(         "rank(String)" R"(): "HeadmasterSupreme", )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": 5                           )"
        R"(         }                                         )"
        R"(    }                                              )"
        R"(])"
    );

    // missing ',' in values list
    EXPECT_FAIL(
        R"(insert into SomeStructure values [)"
        R"(    {                                              )"
        R"(         "salary": 4000,                           )"
        R"(         "name": "Bob",                            )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": 5                           )"
        R"(         }                                         )"
        R"(    }                                              )"
        R"(    {                                              )"
        R"(         "salary": 4000,                           )"
        R"(         "name": "Bob",                            )"
        R"(         "rank": "HeadmasterSupreme",              )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": 5                           )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": 4000,                           )"
        R"(         "name": "Bob",                            )"
        R"(         "rank(String)" R"(): "HeadmasterSupreme", )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": 5                           )"
        R"(         }                                         )"
        R"(    }                                              )"
        R"(])"
    );
}

} // namespace LunarDB::Moonlight::Implementation::Tests
