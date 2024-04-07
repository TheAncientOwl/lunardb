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

    SOURCE_FILES
        src/Primitives.cpp

        src/helpers/Equality.cpp
        src/helpers/Init.cpp
        src/helpers/Ostream.cpp
)

include(${CMAKE_CURRENT_SOURCE_DIR}/test/setup_unit_tests.cmake)
