include_directories(include)
include_directories(include/private)

add_subdirectory(src)

if (LUNAR_ENABLE_TESTING AND LUNAR_BUILD_ASTRAL_TESTS)
    add_subdirectory(test)
endif()
