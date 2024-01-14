include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

set(TEST_SUITE_PREFIX Common_QueryData)

add_lunar_unit_test(
    NAME PrimitivesTest
    SOURCE_FILES PrimitivesTest.cpp
    DEPENDENCIES LunarDB_Common_QueryData
)
