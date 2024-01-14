include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

set(TEST_SUITE_PREFIX Common_CppExtensions)

add_lunar_unit_test(
    NAME StringUtilsTest
    SOURCE_FILES StringUtilsTest.cpp
    DEPENDENCIES LunarDB_Common_CppExtensions
)
