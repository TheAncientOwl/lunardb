macro(add_lunar_library_helper)
    set(options "")
    set(oneValueArgs NAME PREFIX TYPE)
    set(multiValueArgs SOURCE_FILES DEPENDENCIES)

    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(LIBRARY_NAME ${ARG_PREFIX}${ARG_NAME})

    add_library(${LIBRARY_NAME} ${ARG_TYPE} ${ARG_SOURCE_FILES})

    target_link_libraries(${LIBRARY_NAME} PRIVATE ${ARG_DEPENDENCIES})
endmacro()
