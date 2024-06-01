add_lunar_library(
    NAME Common_CppExtensions
    INCLUDE_PATH Common/CppExtensions

    API_HEADER_FILES
        include/BinaryIO/Concepts.hpp
        include/BinaryIO/Deserializer.hpp
        include/BinaryIO/Serializer.hpp
        include/BinaryIO.hpp

        include/DefinePrimitive.hpp
        include/ItemArray.hpp
        include/LiteralToStringMap.hpp
        include/Singleton.hpp
        include/StringUtils.hpp
        include/UniqueID.hpp

        include/private/BinaryIO/Deserializer.inl
        include/private/BinaryIO/Serializer.inl
        include/private/ItemArray.inl
        include/private/LiteralToStringMap.inl
        include/private/Singleton.inl
        include/private/StringUtils.inl

        include/Testing/LunarTestGuard.hpp

    SOURCE_FILES
        src/StringUtils.cpp
        src/BinaryIO.cpp
        src/UniqueID.cpp
)

if (LUNAR_ENABLE_TESTING AND LUNAR_BUILD_COMMON_CPP_EXTENSION_TESTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/setup_unit_tests.cmake)
endif()
