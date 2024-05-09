set(TEST_SUITE_PREFIX Moonlight)

add_lunar_unit_test(
    NAME ParsedQueryTest 
    SOURCE_FILES test/ParsedQueryTest.cpp 
    DEPENDENCIES 
        LunarDB_Moonlight
        LunarDB_Common_QueryData
)

add_lunar_unit_test(
    NAME UtilsTest 
    SOURCE_FILES test/UtilsTest.cpp 
    DEPENDENCIES 
        LunarDB_Moonlight
        LunarDB_Common_QueryData
)

add_lunar_unit_test(
    NAME UtilsWhereClauseTest 
    SOURCE_FILES test/UtilsWhereClauseTest.cpp 
    DEPENDENCIES 
        LunarDB_Moonlight
        LunarDB_Common_QueryData
)

add_lunar_unit_test(
    NAME QueryExtractorTest 
    SOURCE_FILES test/QueryExtractorTest.cpp 
    DEPENDENCIES 
        LunarDB_Moonlight
        LunarDB_Common_QueryData
)


add_lunar_unit_test(
    NAME CreateParserTest 
    SOURCE_FILES test/Parsers/CreateParserTest.cpp 
    DEPENDENCIES 
        LunarDB_Moonlight
        LunarDB_Common_QueryData
)

add_lunar_unit_test(
    NAME DropParserTest 
    SOURCE_FILES test/Parsers/DropParserTest.cpp 
    DEPENDENCIES 
        LunarDB_Moonlight
        LunarDB_Common_QueryData
)

add_lunar_unit_test(
    NAME MigrateParserTest 
    SOURCE_FILES test/Parsers/MigrateParserTest.cpp 
    DEPENDENCIES 
        LunarDB_Moonlight
        LunarDB_Common_QueryData
)

add_lunar_unit_test(
    NAME TruncateParserTest 
    SOURCE_FILES test/Parsers/TruncateParserTest.cpp 
    DEPENDENCIES 
        LunarDB_Moonlight
        LunarDB_Common_QueryData
)

add_lunar_unit_test(
    NAME RenameParserTest 
    SOURCE_FILES test/Parsers/RenameParserTest.cpp 
    DEPENDENCIES 
        LunarDB_Moonlight
        LunarDB_Common_QueryData
)

add_lunar_unit_test(
    NAME SelectParserTest 
    SOURCE_FILES test/Parsers/SelectParserTest.cpp 
    DEPENDENCIES 
        LunarDB_Moonlight
        LunarDB_Common_QueryData
)

add_lunar_unit_test(
    NAME InsertParserTest 
    SOURCE_FILES test/Parsers/InsertParserTest.cpp 
    DEPENDENCIES 
        LunarDB_Moonlight
        LunarDB_Common_QueryData
)

add_lunar_unit_test(
    NAME UpdateParserTest 
    SOURCE_FILES test/Parsers/UpdateParserTest.cpp 
    DEPENDENCIES 
        LunarDB_Moonlight
        LunarDB_Common_QueryData
)

add_lunar_unit_test(
    NAME DeleteParserTest 
    SOURCE_FILES test/Parsers/DeleteParserTest.cpp 
    DEPENDENCIES 
        LunarDB_Moonlight
        LunarDB_Common_QueryData
)

add_lunar_unit_test(
    NAME GrantParserTest 
    SOURCE_FILES test/Parsers/GrantParserTest.cpp 
    DEPENDENCIES 
        LunarDB_Moonlight
        LunarDB_Common_QueryData
)

add_lunar_unit_test(
    NAME RevokeParserTest 
    SOURCE_FILES test/Parsers/RevokeParserTest.cpp 
    DEPENDENCIES 
        LunarDB_Moonlight
        LunarDB_Common_QueryData
)

add_lunar_unit_test(
    NAME CommitParserTest 
    SOURCE_FILES test/Parsers/CommitParserTest.cpp 
    DEPENDENCIES 
        LunarDB_Moonlight
        LunarDB_Common_QueryData
)

add_lunar_unit_test(
    NAME RollbackParserTest 
    SOURCE_FILES test/Parsers/RollbackParserTest.cpp 
    DEPENDENCIES 
        LunarDB_Moonlight
        LunarDB_Common_QueryData
)

add_lunar_unit_test(
    NAME SavePointParserTest 
    SOURCE_FILES test/Parsers/SavePointParserTest.cpp 
    DEPENDENCIES 
        LunarDB_Moonlight
        LunarDB_Common_QueryData
)

add_lunar_unit_test(
    NAME IndexParserTest 
    SOURCE_FILES test/Parsers/IndexParserTest.cpp 
    DEPENDENCIES 
        LunarDB_Moonlight
        LunarDB_Common_QueryData
)

add_lunar_unit_test(
    NAME DatabaseParserTest 
    SOURCE_FILES test/Parsers/DatabaseParserTest.cpp 
    DEPENDENCIES 
        LunarDB_Moonlight
        LunarDB_Common_QueryData
)

add_lunar_unit_test(
    NAME RebindParserTest 
    SOURCE_FILES test/Parsers/RebindParserTest.cpp 
    DEPENDENCIES 
        LunarDB_Moonlight
        LunarDB_Common_QueryData
)

add_lunar_unit_test(
    NAME SchemaParserTest 
    SOURCE_FILES test/Parsers/SchemaParserTest.cpp 
    DEPENDENCIES 
        LunarDB_Moonlight
        LunarDB_Common_QueryData
)
