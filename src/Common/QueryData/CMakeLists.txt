add_lunar_library(
    NAME Common_QueryData
    INCLUDE_PATH Common/QueryData

    API_HEADER_FILES
        include/Primitives.hpp
        include/QueryData.hpp

        include/helpers/Init.hpp
        include/helpers/Operators.hpp

    PRIVATE_DEPENDENCIES
        LunarDB_Common_CppExtensions
        LunarDB_Selenity
        
    SOURCE_FILES
        src/Primitives.cpp
        
        src/helpers/Equality.cpp
        src/helpers/Init.cpp
        src/helpers/Ostream.cpp
)

if (LUNAR_ENABLE_TESTING AND LUNAR_BUILD_COMMON_QUERY_DATA_TESTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/setup_unit_tests.cmake)
endif()
