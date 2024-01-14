include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

set(TEST_SUITE_PREFIX Astral)

add_lunar_unit_test(
    NAME Dummy
    SOURCE_FILES DummyTest.cpp
    DEPENDENCIES LunarDB_Astral
)
