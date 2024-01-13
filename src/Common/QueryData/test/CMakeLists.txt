include(GoogleTest)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

add_executable(PrimitivesTest
    PrimitivesTest.cpp
)

target_link_libraries(PrimitivesTest PRIVATE
    gtest
    gtest_main
    LunarDB_Common_QueryData
)

gtest_discover_tests(PrimitivesTest)
