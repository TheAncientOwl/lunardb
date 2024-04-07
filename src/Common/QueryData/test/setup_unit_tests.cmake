set(TEST_SUITE_PREFIX Common_QueryData)

add_lunar_unit_test(
    NAME PrimitivesTest
    SOURCE_FILES test/PrimitivesTest.cpp
    DEPENDENCIES LunarDB_Common_QueryData
)
