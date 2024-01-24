add_subdirectory(src)

if (LUNAR_ENABLE_TESTING AND LUNAR_BUILD_COMMON_QUERY_DATA_TESTS)
    add_subdirectory(test)
endif()
