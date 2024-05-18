add_lunar_library(
    NAME Celestial
    INCLUDE_PATH Celestial

    API_HEADER_FILES
        include/UsersCatalog.hpp
        include/Configuration.hpp
        include/Authentication.hpp

    PRIVATE_DEPENDENCIES
        LunarDB_Common_CppExtensions
        LunarDB_Common_Cryptography
        LunarDB_Selenity

    SOURCE_FILES
        src/Authentication.cpp
        src/Configuration.cpp
        src/UsersCatalog.cpp
)

if (LUNAR_ENABLE_TESTING AND LUNAR_BUILD_CELESTIAL_TESTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/setup_unit_tests.cmake)
endif()
