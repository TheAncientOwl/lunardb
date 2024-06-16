cmake_minimum_required(VERSION 3.27.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

project(LunarDB VERSION 1.0.0 LANGUAGES C CXX)

include(cmake-tools/setup/cpm.cmake)
include(cmake-tools/setup/ccache.cmake)

include(cmake-tools/setup/boost.cmake)
include(cmake-tools/setup/nlohmann.cmake)
include(cmake-tools/setup/openssl.cmake)
include(cmake-tools/setup/simdjson.cmake)
include(cmake-tools/setup/testing.cmake)

include(cmake-tools/macros/add_lunar_unit_test.cmake)
include(cmake-tools/macros/add_lunar_library.cmake)
include(cmake-tools/macros/add_lunar_executable.cmake)

set(LUNAR_BUILD_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/include)

add_subdirectory(src)
