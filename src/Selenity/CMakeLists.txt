add_lunar_library(
    NAME Selenity
    INCLUDE_PATH Selenity

    API_HEADER_FILES
        include/SystemCatalog.hpp
        include/private/SystemCatalog/DatabaseConfig.hpp

        include/private/SystemCatalog/helpers/Operators.hpp

    PRIVATE_DEPENDENCIES
        LunarDB_Common_CppExtensions

    SOURCE_FILES
        src/SystemCatalog/SystemCatalog.cpp
        src/SystemCatalog/DatabaseConfig.cpp
)

if (LUNAR_ENABLE_TESTING AND LUNAR_BUILD_SELENITY_TESTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/setup_unit_tests.cmake)
endif()
