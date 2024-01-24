include_directories(include)

add_subdirectory(src)

if (LUNAR_ENABLE_TESTING AND LUNAR_BUILD_COMMON_CPP_EXTENSION_TESTS)
    add_subdirectory(test)
endif()
