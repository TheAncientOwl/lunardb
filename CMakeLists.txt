cmake_minimum_required(VERSION 3.27.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

project(LunarDB VERSION 0.1.0 LANGUAGES C CXX)

# CMake-Tools Includes
include(cmake-tools/macros/add_lunar_unit_test.cmake)
include(cmake-tools/macros/add_lunar_library.cmake)
include(cmake-tools/macros/add_lunar_common_library.cmake)

include(cmake-tools/setup/testing.cmake)

# Setup project files
add_subdirectory(src)

add_executable(LunarDB src/driver.cpp)
