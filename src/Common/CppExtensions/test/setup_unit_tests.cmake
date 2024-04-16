set(TEST_SUITE_PREFIX Common_CppExtensions)

add_lunar_unit_test(
    NAME StringUtilsTest
    SOURCE_FILES test/StringUtilsTest.cpp
    DEPENDENCIES 
        LunarDB_Common_QueryData
)

add_lunar_unit_test(
    NAME BinaryIOTest
    SOURCE_FILES test/BinaryIOTest.cpp
    DEPENDENCIES 
        LunarDB_Common_CppExtensions
)
