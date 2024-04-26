set(TEST_SUITE_PREFIX Selenity)

add_lunar_unit_test(
    NAME DatabaseConfigTest
    SOURCE_FILES 
        test/SystemCatalog/DatabaseConfigTest.cpp
    DEPENDENCIES 
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
)

add_lunar_unit_test(
    NAME SystemCatalogTest
    SOURCE_FILES 
        test/SystemCatalog/SystemCatalogTest.cpp
    DEPENDENCIES 
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
)
