set(TEST_SUITE_PREFIX Crescentum)

add_lunar_unit_test(
    NAME LogTest
    SOURCE_FILES test/LogTest.cpp 
    DEPENDENCIES 
        LunarDB_Crescentum
        LunarDB_Common_CppExtensions
)
