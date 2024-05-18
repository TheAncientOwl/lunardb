set(TEST_SUITE_PREFIX Selenity)

add_lunar_unit_test(
    NAME DatabaseCatalogTest
    SOURCE_FILES 
        test/DatabaseCatalogTest.cpp
    DEPENDENCIES 
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
)

add_lunar_unit_test(
    NAME SystemCatalogTest
    SOURCE_FILES 
        test/SystemCatalogTest.cpp
    DEPENDENCIES 
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
)

add_lunar_unit_test(
    NAME SchemasCatalogTest
    SOURCE_FILES 
        test/SchemasCatalogTest.cpp
    DEPENDENCIES 
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
        LunarDB_Common_QueryData
)
