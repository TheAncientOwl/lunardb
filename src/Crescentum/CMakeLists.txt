add_lunar_library(
    NAME Crescentum
    INCLUDE_PATH Crescentum

    API_HEADER_FILES
        include/Logger.hpp

        include/private/Logger.inl

    PRIVATE_DEPENDENCIES
        LunarDB_Common_CppExtensions

    SOURCE_FILES
        src/Logger.cpp
)

if (LUNAR_ENABLE_TESTING AND LUNAR_BUILD_CRESCENTUM_TESTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/setup_unit_tests.cmake)
endif()
