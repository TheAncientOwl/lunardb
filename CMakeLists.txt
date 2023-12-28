cmake_minimum_required(VERSION 3.27.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(LunarDB VERSION 0.1.0 LANGUAGES C CXX)

include(GoogleTest)

include(CTest)
enable_testing()

add_subdirectory(src)

add_executable(LunarDB src/driver.cpp)
