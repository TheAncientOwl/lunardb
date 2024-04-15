set(TEST_SUITE_PREFIX Selenity)

add_lunar_unit_test(
    NAME DummyTest
    SOURCE_FILES test/DummyTest.cpp 
    DEPENDENCIES 
        LunarDB_Selenity
)
