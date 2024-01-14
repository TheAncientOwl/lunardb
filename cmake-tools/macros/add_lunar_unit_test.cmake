include(GoogleTest)

macro(add_lunar_unit_test)
    set(options "")
    set(oneValueArgs NAME)
    set(multiValueArgs SOURCE_FILES DEPENDENCIES)
    
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    
    add_executable(${ARG_NAME} ${ARG_SOURCE_FILES})

    target_link_libraries(${ARG_NAME}
        PRIVATE
            gtest
            gtest_main
            ${ARG_DEPENDENCIES}
    )

    gtest_discover_tests(${ARG_NAME})
endmacro()
