include(GoogleTest)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

set(TEST_SUITE_PREFIX Moonlight)

add_lunar_unit_test(
    NAME ParsedQueryTest 
    SOURCE_FILES ParsedQueryTest.cpp 
    DEPENDENCIES LunarDB_Moonlight
)

add_lunar_unit_test(
    NAME UtilsTest 
    SOURCE_FILES UtilsTest.cpp 
    DEPENDENCIES LunarDB_Moonlight
)

add_lunar_unit_test(
    NAME UtilsWhereClauseTest 
    SOURCE_FILES UtilsWhereClauseTest.cpp 
    DEPENDENCIES LunarDB_Moonlight
)

add_lunar_unit_test(
    NAME QueryExtractorTest 
    SOURCE_FILES QueryExtractorTest.cpp 
    DEPENDENCIES LunarDB_Moonlight
)


add_lunar_unit_test(
    NAME CreateParserTest 
    SOURCE_FILES Parsers/CreateParserTest.cpp 
    DEPENDENCIES LunarDB_Moonlight
)

add_lunar_unit_test(
    NAME DropParserTest 
    SOURCE_FILES Parsers/DropParserTest.cpp 
    DEPENDENCIES LunarDB_Moonlight
)

add_lunar_unit_test(
    NAME MigrateParserTest 
    SOURCE_FILES Parsers/MigrateParserTest.cpp 
    DEPENDENCIES LunarDB_Moonlight
)

add_lunar_unit_test(
    NAME TruncateParserTest 
    SOURCE_FILES Parsers/TruncateParserTest.cpp 
    DEPENDENCIES LunarDB_Moonlight
)

add_lunar_unit_test(
    NAME RenameParserTest 
    SOURCE_FILES Parsers/RenameParserTest.cpp 
    DEPENDENCIES LunarDB_Moonlight
)

add_lunar_unit_test(
    NAME SelectParserTest 
    SOURCE_FILES Parsers/SelectParserTest.cpp 
    DEPENDENCIES LunarDB_Moonlight
)

add_lunar_unit_test(
    NAME InsertParserTest 
    SOURCE_FILES Parsers/InsertParserTest.cpp 
    DEPENDENCIES LunarDB_Moonlight
)

add_lunar_unit_test(
    NAME UpdateParserTest 
    SOURCE_FILES Parsers/UpdateParserTest.cpp 
    DEPENDENCIES LunarDB_Moonlight
)

add_lunar_unit_test(
    NAME DeleteParserTest 
    SOURCE_FILES Parsers/DeleteParserTest.cpp 
    DEPENDENCIES LunarDB_Moonlight
)

add_lunar_unit_test(
    NAME LockParserTest 
    SOURCE_FILES Parsers/LockParserTest.cpp 
    DEPENDENCIES LunarDB_Moonlight
)

add_lunar_unit_test(
    NAME GrantParserTest 
    SOURCE_FILES Parsers/GrantParserTest.cpp 
    DEPENDENCIES LunarDB_Moonlight
)

add_lunar_unit_test(
    NAME RevokeParserTest 
    SOURCE_FILES Parsers/RevokeParserTest.cpp 
    DEPENDENCIES LunarDB_Moonlight
)

add_lunar_unit_test(
    NAME CommitParserTest 
    SOURCE_FILES Parsers/CommitParserTest.cpp 
    DEPENDENCIES LunarDB_Moonlight
)

add_lunar_unit_test(
    NAME RollbackParserTest 
    SOURCE_FILES Parsers/RollbackParserTest.cpp 
    DEPENDENCIES LunarDB_Moonlight
)

add_lunar_unit_test(
    NAME SavePointParserTest 
    SOURCE_FILES Parsers/SavePointParserTest.cpp 
    DEPENDENCIES LunarDB_Moonlight
)

add_lunar_unit_test(
    NAME IndexParserTest 
    SOURCE_FILES Parsers/IndexParserTest.cpp 
    DEPENDENCIES LunarDB_Moonlight
)

add_lunar_unit_test(
    NAME DatabaseParserTest 
    SOURCE_FILES Parsers/DatabaseParserTest.cpp 
    DEPENDENCIES LunarDB_Moonlight
)

add_lunar_unit_test(
    NAME ViewParserTest 
    SOURCE_FILES Parsers/ViewParserTest.cpp 
    DEPENDENCIES LunarDB_Moonlight
)

add_lunar_unit_test(
    NAME RebindParserTest 
    SOURCE_FILES Parsers/RebindParserTest.cpp 
    DEPENDENCIES LunarDB_Moonlight
)

add_lunar_unit_test(
    NAME SchemaParserTest 
    SOURCE_FILES Parsers/SchemaParserTest.cpp 
    DEPENDENCIES LunarDB_Moonlight
)

