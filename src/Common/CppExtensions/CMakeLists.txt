add_lunar_library(
    NAME Common_CppExtensions
    INCLUDE_PATH Common/CppExtensions

    API_HEADER_FILES
        include/BinaryIO/Concepts.hpp
        include/BinaryIO/Deserializer.hpp
        include/BinaryIO/Serializer.hpp
        include/BinaryIO.hpp

        include/Concepts/Item.hpp

        include/DefinePrimitive.hpp
        include/FlatMap.hpp
        include/DynamicFlatMap.hpp
        include/LiteralToStringMap.hpp
        include/Singleton.hpp
        include/StringUtils.hpp
        include/Timer.hpp
        include/UniqueID.hpp

        include/private/BinaryIO/Deserializer.inl
        include/private/BinaryIO/Serializer.inl
        include/private/FlatMap.inl
        include/private/DynamicFlatMap.inl
        include/private/LiteralToStringMap.inl
        include/private/Singleton.inl
        include/private/StringUtils.inl

        include/Testing/LunarTestGuard.hpp

        include/ConsoleColorOutput.hpp
        
    SOURCE_FILES
        src/BinaryIO.cpp
        src/ConsoleColorOutput.cpp
        src/StringUtils.cpp
        src/Timer.cpp
        src/UniqueID.cpp
)
        
if (LUNAR_ENABLE_TESTING AND LUNAR_BUILD_COMMON_CPP_EXTENSION_TESTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/setup_unit_tests.cmake)
endif()
        
        
add_lunar_executable(
    NAME Common_ConsoleColorOutput_Showcase
    INCLUDE_PATH Common/ConsoleColorOutput_Showcase
    
    API_HEADER_FILES

    PRIVATE_DEPENDENCIES
        LunarDB_Common_CppExtensions
    
    SOURCE_FILES
        test/ConsoleColorOutputShowcase.cpp
)
