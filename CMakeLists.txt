cmake_minimum_required(VERSION 3.27.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

project(LunarDB VERSION 0.1.0 LANGUAGES C CXX)

# Custom Includes
include(cmake-tools/macros/add_lunar_unit_test.cmake)

# Common Includes
include(FetchContent)

# GoogleTest setup
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

# Enable Testing
include(CTest)
enable_testing()

# Setup project files
add_subdirectory(src)

add_executable(LunarDB src/driver.cpp)
