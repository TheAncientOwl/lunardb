macro(add_lunar_executable)
    set(options "")
    set(oneValueArgs NAME INCLUDE_PATH)
    set(multiValueArgs SOURCE_FILES API_HEADER_FILES PRIVATE_DEPENDENCIES)

    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(EXECUTABLE_NAME LunarDB_${ARG_NAME})

    add_executable(${EXECUTABLE_NAME})

    target_sources(${EXECUTABLE_NAME} PRIVATE ${ARG_SOURCE_FILES})

    foreach(header ${ARG_API_HEADER_FILES})
        set(abs_header_file_path ${CMAKE_CURRENT_SOURCE_DIR}/${header})
        string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/include/ "" relative_include_header_file_path ${abs_header_file_path})
        set(build_include_file_path ${LUNAR_BUILD_INCLUDE_DIR}/LunarDB/${ARG_INCLUDE_PATH}/${relative_include_header_file_path})
        get_filename_component(LUNAR_BUILD_INCLUDE_DIR_path "${build_include_file_path}" DIRECTORY)

        file(COPY ${abs_header_file_path} DESTINATION ${LUNAR_BUILD_INCLUDE_DIR_path})
    endforeach()

    target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${ARG_PRIVATE_DEPENDENCIES})

    target_include_directories(${EXECUTABLE_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
            ${LUNAR_BUILD_INCLUDE_DIR}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )

    set_target_properties(${EXECUTABLE_NAME} PROPERTIES DEBUG_POSTFIX ".debug")

endmacro()
