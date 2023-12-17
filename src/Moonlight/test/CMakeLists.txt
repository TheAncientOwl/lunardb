function(create_test_executable TARGET_NAME SOURCE_FILES)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include ${CMAKE_CURRENT_SOURCE_DIR}/../src)
    add_executable(${TARGET_NAME} ${SOURCE_FILES})

    target_link_libraries(${TARGET_NAME} PRIVATE
        gtest
        gtest_main
        LunarDB_Moonlight
    )

    include(GoogleTest)
    gtest_discover_tests(${TARGET_NAME})
endfunction()

create_test_executable(ParsedQueryTest ParsedQueryTest.cpp)
create_test_executable(UtilsTest UtilsTest.cpp)
create_test_executable(QueryExtractorTest QueryExtractorTest.cpp)
create_test_executable(PrimitivesTest PrimitivesTest.cpp)

create_test_executable(CreateParserTest Parsers/CreateParserTest.cpp)
create_test_executable(DropParserTest Parsers/DropParserTest.cpp)
create_test_executable(MigrateParserTest Parsers/MigrateParserTest.cpp)
create_test_executable(TruncateParserTest Parsers/TruncateParserTest.cpp)
create_test_executable(RenameParserTest Parsers/RenameParserTest.cpp)
create_test_executable(SelectParserTest Parsers/SelectParserTest.cpp)
create_test_executable(InsertParserTest Parsers/InsertParserTest.cpp)
create_test_executable(UpdateParserTest Parsers/UpdateParserTest.cpp)
create_test_executable(DeleteParserTest Parsers/DeleteParserTest.cpp)
create_test_executable(LockParserTest Parsers/LockParserTest.cpp)
create_test_executable(GrantParserTest Parsers/GrantParserTest.cpp)
create_test_executable(RevokeParserTest Parsers/RevokeParserTest.cpp)
create_test_executable(CommitParserTest Parsers/CommitParserTest.cpp)
create_test_executable(RollbackParserTest Parsers/RollbackParserTest.cpp)
create_test_executable(SavePointParserTest Parsers/SavePointParserTest.cpp)
create_test_executable(IndexParserTest Parsers/IndexParserTest.cpp)
create_test_executable(DatabaseParserTest Parsers/DatabaseParserTest.cpp)
create_test_executable(ViewParserTest Parsers/ViewParserTest.cpp)
create_test_executable(RebindParserTest Parsers/RebindParserTest.cpp)
