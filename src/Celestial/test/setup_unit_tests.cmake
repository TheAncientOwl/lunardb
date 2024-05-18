set(TEST_SUITE_PREFIX Celestial)

add_lunar_unit_test(
    NAME UsersCatalogTest
    SOURCE_FILES test/UsersCatalogTest.cpp 
    DEPENDENCIES 
        LunarDB_Selenity
        LunarDB_Celestial
        LunarDB_Common_CppExtensions
)
