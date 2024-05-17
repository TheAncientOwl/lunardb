set(TEST_SUITE_PREFIX Selenity)

add_lunar_unit_test(
    NAME DatabaseCatalogTest
    SOURCE_FILES 
        test/SystemCatalog/DatabaseCatalogTest.cpp
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
