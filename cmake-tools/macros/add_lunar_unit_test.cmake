macro(add_lunar_unit_test)
    if (NOT DEFINED TEST_SUITE_PREFIX)
        message(FATAL_ERROR "Test suite prefix not defined")
    endif()

    set(options "")
    set(oneValueArgs NAME)
    set(multiValueArgs SOURCE_FILES DEPENDENCIES)
    
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    
    set(TEST_NAME ${TEST_SUITE_PREFIX}_${ARG_NAME})

    add_executable(${TEST_NAME} ${ARG_SOURCE_FILES})

    target_link_libraries(${TEST_NAME}
        PRIVATE
            gtest
            gtest_main
            ${ARG_DEPENDENCIES}
    )

    gtest_discover_tests(${TEST_NAME})
endmacro()
