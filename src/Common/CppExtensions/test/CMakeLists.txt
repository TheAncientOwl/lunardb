include(GoogleTest)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

add_executable(StringUtilsTest
    StringUtilsTest.cpp
)

target_link_libraries(StringUtilsTest PRIVATE
    gtest
    gtest_main
    LunarDB_Common_CppExtensions
)

gtest_discover_tests(StringUtilsTest)
