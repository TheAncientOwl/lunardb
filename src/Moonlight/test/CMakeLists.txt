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

create_test_executable(CreateParserTest CreateParserTest.cpp)
create_test_executable(DropParserTest DropParserTest.cpp)
create_test_executable(MigrateParserTest MigrateParserTest.cpp)
create_test_executable(TruncateParserTest TruncateParserTest.cpp)
create_test_executable(RenameParserTest RenameParserTest.cpp)
create_test_executable(SelectParserTest SelectParserTest.cpp)
create_test_executable(InsertParserTest InsertParserTest.cpp)
create_test_executable(UpdateParserTest UpdateParserTest.cpp)
create_test_executable(DeleteParserTest DeleteParserTest.cpp)
create_test_executable(LockParserTest LockParserTest.cpp)
create_test_executable(GrantParserTest GrantParserTest.cpp)
create_test_executable(RevokeParserTest RevokeParserTest.cpp)
create_test_executable(CommitParserTest CommitParserTest.cpp)
create_test_executable(RollbackParserTest RollbackParserTest.cpp)
create_test_executable(SavePointParserTest SavePointParserTest.cpp)
create_test_executable(IndexParserTest IndexParserTest.cpp)
create_test_executable(DatabaseParserTest DatabaseParserTest.cpp)
create_test_executable(ViewParserTest ViewParserTest.cpp)
