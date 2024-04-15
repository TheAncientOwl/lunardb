add_lunar_library(
    NAME Celestial
    INCLUDE_PATH Celestial

    API_HEADER_FILES

    PRIVATE_DEPENDENCIES

    SOURCE_FILES
        src/main.cpp
)

if (LUNAR_ENABLE_TESTING AND LUNAR_BUILD_CELESTIAL_TESTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/setup_unit_tests.cmake)
endif()
