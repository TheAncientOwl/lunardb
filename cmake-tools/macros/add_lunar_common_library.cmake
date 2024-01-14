macro(add_lunar_common_library)
    set(options "")
    set(oneValueArgs NAME)
    set(multiValueArgs SOURCE_FILES DEPENDENCIES)

    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    add_lunar_library_helper(
        PREFIX LunarDB_Common_
        NAME ${ARG_NAME}
        TYPE STATIC
        SOURCE_FILES ${ARG_SOURCE_FILES}
        DEPENDENCIES ${ARG_DEPENDENCIES}
    )
endmacro()
