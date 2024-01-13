include(GoogleTest)

macro(add_lunar_unit_test)
    set(options "")
    set(oneValueArgs NAME)
    set(multiValueArgs SOURCE_FILES DEPENDENCIES)
    
    cmake_parse_arguments(ADD_LUNAR_UNIT_TEST "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    
    add_executable(${ADD_LUNAR_UNIT_TEST_NAME} ${ADD_LUNAR_UNIT_TEST_SOURCE_FILES})

    target_link_libraries(${ADD_LUNAR_UNIT_TEST_NAME}
        PRIVATE
            gtest
            gtest_main
            ${ADD_LUNAR_UNIT_TEST_DEPENDENCIES}
    )

    gtest_discover_tests(${ADD_LUNAR_UNIT_TEST_NAME})
endmacro()
