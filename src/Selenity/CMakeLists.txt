add_lunar_library(
    NAME Selenity
    INCLUDE_PATH Selenity

    API_HEADER_FILES
        include/SchemasCatalog.hpp
        include/SystemCatalog.hpp

        include/Managers/Collections/AbstractManager.hpp
        include/Managers/Collections/DocumentManager.hpp
        include/Managers/Collections/EvaluateWhereClause.hpp
        include/Managers/Collections/TableManager.hpp
        include/Managers/private/CatalogManager.inl
        include/Managers/CatalogManager.hpp
        include/Managers/Configurations.hpp
        include/Managers/DatabaseManager.hpp
        
    PRIVATE_DEPENDENCIES
        LunarDB_Common_CppExtensions
        LunarDB_Moonlight
        LunarDB_BrightMoon
        
    SOURCE_FILES
        src/Managers/DatabaseManager.cpp
        src/SchemasCatalog.cpp
        src/SystemCatalog.cpp
        src/Managers/Collections/AbstractManager.cpp
        src/Managers/Collections/DocumentManager.cpp
        src/Managers/Collections/EvaluateWhereClause.cpp
        src/Managers/Collections/TableManager.cpp
        src/Managers/Configurations.cpp
)

if (LUNAR_ENABLE_TESTING AND LUNAR_BUILD_SELENITY_TESTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/setup_unit_tests.cmake)
endif()

target_link_libraries(LunarDB_Selenity PUBLIC nlohmann_json::nlohmann_json)
