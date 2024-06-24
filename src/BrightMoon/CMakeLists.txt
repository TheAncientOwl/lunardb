add_lunar_library(
    NAME BrightMoon
    INCLUDE_PATH BrightMoon

    API_HEADER_FILES
        include/WriteAheadLogger.hpp
        include/TransactionData.hpp

    PRIVATE_DEPENDENCIES
        LunarDB_Common_CppExtensions
        LunarDB_Common_QueryData
        LunarDB_Selenity

    SOURCE_FILES
        src/WriteAheadLogger.cpp
        src/TransactionData.cpp
)

if (LUNAR_ENABLE_TESTING AND LUNAR_BUILD_BRIGHTMOON_TESTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/setup_unit_tests.cmake)
endif()
