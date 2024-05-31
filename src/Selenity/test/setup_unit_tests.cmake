set(TEST_SUITE_PREFIX Selenity)

add_lunar_unit_test(
    NAME DatabaseManagerTest
    SOURCE_FILES 
        test/DatabaseManagerTest.cpp
    DEPENDENCIES 
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
        LunarDB_Common_QueryData
)

add_lunar_unit_test(
    NAME SystemCatalogTest
    SOURCE_FILES 
        test/SystemCatalogTest.cpp
    DEPENDENCIES 
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
        LunarDB_Common_QueryData
)

add_lunar_unit_test(
    NAME SchemasCatalogTest
    SOURCE_FILES 
        test/SchemasCatalogTest.cpp
    DEPENDENCIES 
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
        LunarDB_Common_QueryData
        LunarDB_Common_QueryData
)
