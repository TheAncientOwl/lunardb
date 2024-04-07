macro(add_lunar_library)
    set(options "")
    set(oneValueArgs NAME INCLUDE_PATH)
    set(multiValueArgs SOURCE_FILES API_HEADER_FILES PRIVATE_DEPENDENCIES)

    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(LIBRARY_NAME LunarDB_${ARG_NAME})

    add_library(${LIBRARY_NAME} STATIC)

    target_sources(${LIBRARY_NAME} PRIVATE ${ARG_SOURCE_FILES})

    foreach(header ${ARG_API_HEADER_FILES})
        set(abs_header_file_path ${CMAKE_CURRENT_SOURCE_DIR}/${header})
        string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/include/ "" relative_include_header_file_path ${abs_header_file_path})
        set(build_include_file_path ${BUILD_INCLUDE_DIR}/${ARG_INCLUDE_PATH}/${relative_include_header_file_path})
        get_filename_component(build_include_dir_path "${build_include_file_path}" DIRECTORY)

        file(COPY ${abs_header_file_path} DESTINATION ${build_include_dir_path})
    endforeach()

    target_link_libraries(${LIBRARY_NAME} PRIVATE ${ARG_PRIVATE_DEPENDENCIES})

    target_include_directories(${LIBRARY_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
            ${BUILD_INCLUDE_DIR}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )

    set_target_properties(${LIBRARY_NAME} PROPERTIES DEBUG_POSTFIX ".debug")

endmacro()
