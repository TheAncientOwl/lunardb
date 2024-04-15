set(TEST_SUITE_PREFIX Celestial)

add_lunar_unit_test(
    NAME DummyTest
    SOURCE_FILES test/DummyTest.cpp 
    DEPENDENCIES 
        LunarDB_Celestial
)
