#include "Common/ParserTestIncludes.hpp"

#define QUERY_TYPE Insert

namespace LunarDB::Moonlight::Implementation::Tests {

using namespace QueryData;

TEST(InsertParserTest, success01)
{
    const auto query =
        R"(insert into SomeStructure objects [                               )"
        R"(    {                                                             )"
        R"(         "salary": "4000",                                        )"
        R"(         "name": "Bob",                                           )"
        R"(         "birth_date": "09/10/1985",                              )"
        R"(         "address": {                                             )"
        R"(             "street": "Some Street",                             )"
        R"(             "number": "5"                                        )"
        R"(         }                                                        )"
        R"(    },                                                            )"
        R"(    {                                                             )"
        R"(         "salary": "4000",                                        )"
        R"(         "name": "Bob",                                           )"
        R"(         "rank": "HeadmasterSupreme",                             )"
        R"(         "birth_date": "09/10/1985",                              )"
        R"(         "address": {                                             )"
        R"(             "street": "Some Street",                             )"
        R"(             "number": "5"                                        )"
        R"(         }                                                        )"
        R"(    },                                                            )"
        R"(    {                                                             )"
        R"(         "salary": "4000",                                        )"
        R"(         "name": "Bob",                                           )"
        "          \"rank(String)\": \"HeadmasterSupreme\",                  "
        R"(         "birth_date": "09/10/1985",                              )"
        R"(         "address": {                                             )"
        R"(             "street": "Some Street",                             )"
        R"(             "number": "5"                                        )"
        R"(         }                                                        )"
        R"(    },                                                            )"
        R"(    {                                                             )"
        R"(         "salary": "4000",                                        )"
        R"(         "name": "Bob",                                           )"
        R"(         "rank(String)" R"(): "HeadmasterSupreme",                )"
        R"(         "birth_date": "09/10/1985",                              )"
        R"(         "address": {                                             )"
        R"(             "street": "Some Street",                             )"
        R"(             "number": "5"                                        )"
        R"(         },                                                       )"
        R"(         "rands": [ "1", "11", "111" ]                            )"
        R"(    },                                                            )"
        R"(    {                                                             )"
        R"(         "salary": "4000",                                        )"
        R"(         "name": "Bob",                                           )"
        R"(         "rank(String)" R"(): "HeadmasterSupreme",                )"
        R"(         "birth_date": "09/10/1985",                              )"
        R"(         "address": {                                             )"
        R"(             "street": "Some Street",                             )"
        R"(             "number": "5"                                        )"
        R"(         },                                                       )"
        R"(         "rands": [ "1", "11", "111" ],                           )"
        R"(         "objs":  [ {"X": "1", "Y": "2" }, {"X": "1", "Y": "2"} ] )"
        R"(    }                                                             )"
        R"(]                                                                 )";

    std::vector<Insert::Object> objects{};

    auto address = Insert::Object{};
    address.entries.emplace("street", "Some Street");
    address.entries.emplace("number", "5");

    auto& obj1 = objects.emplace_back();
    obj1.entries.emplace("salary", "4000");
    obj1.entries.emplace("name", "Bob");
    obj1.entries.emplace("birth_date", "09/10/1985");
    obj1.entries.emplace("address", address);

    auto& obj2 = objects.emplace_back();
    obj2.entries.emplace("salary", "4000");
    obj2.entries.emplace("name", "Bob");
    obj2.entries.emplace("rank", "HeadmasterSupreme");
    obj2.entries.emplace("birth_date", "09/10/1985");
    obj2.entries.emplace("address", address);

    auto& obj3 = objects.emplace_back();
    obj3.entries.emplace("salary", "4000");
    obj3.entries.emplace("name", "Bob");
    obj3.entries.emplace("rank(String)", "HeadmasterSupreme");
    obj3.entries.emplace("birth_date", "09/10/1985");
    obj3.entries.emplace("address", address);

    auto& obj4 = objects.emplace_back();
    obj4.entries.emplace("salary", "4000");
    obj4.entries.emplace("name", "Bob");
    obj4.entries.emplace("rank(String)", "HeadmasterSupreme");
    obj4.entries.emplace("birth_date", "09/10/1985");
    obj4.entries.emplace("address", address);
    obj4.entries.emplace("rands", std::vector<std::string>{"1", "11", "111"});

    auto obj = Insert::Object{};
    obj.entries.emplace("X", "1");
    obj.entries.emplace("Y", "2");

    auto& obj5 = objects.emplace_back();
    obj5.entries.emplace("salary", "4000");
    obj5.entries.emplace("name", "Bob");
    obj5.entries.emplace("rank(String)", "HeadmasterSupreme");
    obj5.entries.emplace("birth_date", "09/10/1985");
    obj5.entries.emplace("address", address);
    obj5.entries.emplace("rands", std::vector<std::string>{"1", "11", "111"});
    obj5.entries.emplace("obj2", std::vector<Insert::Object>{obj, obj});

    const auto expected = Init::InsertInit{}
        .into("SomeStructure")
        .objects(objects);

    EXPECT_SUCCESS(query, expected);
}

///
/// @note All possible fails related to objects should be handled by json parser.
///       All possible fails related to Moonlight insert syntax are handlede by this test.
///
TEST(InsertParserTest, fail01)
{
    // missing '['
    EXPECT_FAIL(
        R"(insert into SomeStructure objects                  )"
        R"(    {                                              )"
        R"(         "salary": "4000",                         )"
        R"(         "name": "Bob",                            )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": "5"                         )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": "4000",                         )"
        R"(         "name": "Bob",                            )"
        R"(         "rank": "HeadmasterSupreme",              )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": "5"                         )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": "4000",                         )"
        R"(         "name": "Bob",                            )"
        R"(         "rank(String)" R"(): "HeadmasterSupreme", )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": "5"                         )"
        R"(         }                                         )"
        R"(    }                                              )"
        R"(]                                                  )"
    );

    // missing ']'
    EXPECT_FAIL(
        R"(insert into SomeStructure objects [                )"
        R"(    {                                              )"
        R"(         "salary": "4000",                         )"
        R"(         "name": "Bob",                            )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": "5"                         )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": "4000",                         )"
        R"(         "name": "Bob",                            )"
        R"(         "rank": "HeadmasterSupreme",              )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": "5"                         )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": "4000",                         )"
        R"(         "name": "Bob",                            )"
        R"(         "rank(String)" R"(): "HeadmasterSupreme", )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": "5"                         )"
        R"(         }                                         )"
        R"(    }                                              )"
        R"(                                                   )"
    );

    // missing 'into'
    EXPECT_FAIL(
        R"(insert SomeStructure objects [                     )"
        R"(    {                                              )"
        R"(         "salary": "4000",                         )"
        R"(         "name": "Bob",                            )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": "5"                         )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": "4000",                         )"
        R"(         "name": "Bob",                            )"
        R"(         "rank": "HeadmasterSupreme",              )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": "5"                         )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": "4000",                         )"
        R"(         "name": "Bob",                            )"
        R"(         "rank(String)" R"(): "HeadmasterSupreme", )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": "5"                         )"
        R"(         }                                         )"
        R"(    }                                              )"
        R"(]                                                  )"
    );

    // missing 'objects'
    EXPECT_FAIL(
        R"(insert into SomeStructure [                        )"
        R"(    {                                              )"
        R"(         "salary": "4000",                         )"
        R"(         "name": "Bob",                            )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": "5"                         )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": "4000",                         )"
        R"(         "name": "Bob",                            )"
        R"(         "rank": "HeadmasterSupreme",              )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": "5"                         )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": "4000",                         )"
        R"(         "name": "Bob",                            )"
        R"(         "rank(String)" R"(): "HeadmasterSupreme", )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": "5"                         )"
        R"(         }                                         )"
        R"(    }                                              )"
        R"(]                                                  )"
    );

    // missing structure name, should be the same case as the previous one
    // since 'objects' here will be treated as a structure name.
    EXPECT_FAIL(
        R"(insert into objects [                              )"
        R"(    {                                              )"
        R"(         "salary": "4000",                         )"
        R"(         "name": "Bob",                            )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": "5"                         )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": "4000",                         )"
        R"(         "name": "Bob",                            )"
        R"(         "rank": "HeadmasterSupreme",              )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": "5"                         )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": "4000",                         )"
        R"(         "name": "Bob",                            )"
        R"(         "rank(String)" R"(): "HeadmasterSupreme", )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": "5"                         )"
        R"(         }                                         )"
        R"(    }                                              )"
        R"(]                                                  )"
    );

    // space in structure name
    EXPECT_FAIL(
        R"(insert into Some Structure objects [               )"
        R"(    {                                              )"
        R"(         "salary": "4000",                         )"
        R"(         "name": "Bob",                            )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": "5"                         )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": "4000",                         )"
        R"(         "name": "Bob",                            )"
        R"(         "rank": "HeadmasterSupreme",              )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": "5"                         )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": "4000",                         )"
        R"(         "name": "Bob",                            )"
        R"(         "rank(String)" R"(): "HeadmasterSupreme", )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": "5"                         )"
        R"(         }                                         )"
        R"(    }                                              )"
        R"(]                                                  )"
    );

    // missing ',' in objects list
    EXPECT_FAIL(
        R"(insert into SomeStructure objects [                )"
        R"(    {                                              )"
        R"(         "salary": "4000",                         )"
        R"(         "name": "Bob",                            )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": "5"                         )"
        R"(         }                                         )"
        R"(    }                                              )"
        R"(    {                                              )"
        R"(         "salary": "4000",                         )"
        R"(         "name": "Bob",                            )"
        R"(         "rank": "HeadmasterSupreme",              )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": "5"                         )"
        R"(         }                                         )"
        R"(    },                                             )"
        R"(    {                                              )"
        R"(         "salary": "4000",                         )"
        R"(         "name": "Bob",                            )"
        R"(         "rank(String)" R"(): "HeadmasterSupreme", )"
        R"(         "birth_date": "09/10/1985",               )"
        R"(         "address": {                              )"
        R"(             "street": "Some Street",              )"
        R"(             "number": "5"                         )"
        R"(         }                                         )"
        R"(    }                                              )"
        R"(]                                                  )"
    );

    // missing ','
    EXPECT_FAIL(
        R"(insert into SomeStructure objects [                               )"
        R"(    {                                                             )"
        R"(         "salary": "4000",                                        )"
        R"(         "name": "Bob",                                           )"
        R"(         "birth_date": "09/10/1985",                              )"
        R"(         "address": {                                             )"
        R"(             "street": "Some Street",                             )"
        R"(             "number": "5"                                        )"
        R"(         }                                                        )"
        R"(    },                                                            )"
        R"(    {                                                             )"
        R"(         "salary": "4000",                                        )"
        R"(         "name": "Bob",                                           )"
        R"(         "rank": "HeadmasterSupreme",                             )"
        R"(         "birth_date": "09/10/1985",                              )"
        R"(         "address": {                                             )"
        R"(             "street": "Some Street",                             )"
        R"(             "number": "5"                                        )"
        R"(         }                                                        )"
        R"(    },                                                            )"
        R"(    {                                                             )"
        R"(         "salary": "4000",                                        )"
        R"(         "name": "Bob",                                           )"
        R"(         "rank(String)" R"(): "HeadmasterSupreme",                )"
        R"(         "birth_date": "09/10/1985",                              )"
        R"(         "address": {                                             )"
        R"(             "street": "Some Street",                             )"
        R"(             "number": "5"                                        )"
        R"(         }                                                        )"
        R"(    },                                                            )"
        R"(    {                                                             )"
        R"(         "salary": "4000",                                        )"
        R"(         "name": "Bob",                                           )"
        R"(         "rank(String)" R"(): "HeadmasterSupreme",                )"
        R"(         "birth_date": "09/10/1985",                              )"
        R"(         "address": {                                             )"
        R"(             "street": "Some Street",                             )"
        R"(             "number": "5"                                        )"
        R"(         },                                                       )"
        R"(         "rands": [ "1", "11", "111" ]                            )"
        R"(    },                                                            )"
        R"(    {                                                             )"
        R"(         "salary": "4000",                                        )"
        R"(         "name": "Bob",                                           )"
        R"(         "rank(String)" R"(): "HeadmasterSupreme",                )"
        R"(         "birth_date": "09/10/1985",                              )"
        R"(         "address": {                                             )"
        R"(             "street": "Some Street",                             )"
        R"(             "number": "5"                                        )"
        R"(         },                                                       )"
        R"(         "rands": [ "1", "11", "111" ],                           )"
        R"(         "objs":  [ {"X": "1" "Y": "2" }, {"X": "1", "Y": "2"} ]  )"
        R"(    }                                                             )"
        R"(]                                                                 )"
    );
}

} // namespace LunarDB::Moonlight::Implementation::Tests
