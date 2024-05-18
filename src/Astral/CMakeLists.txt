add_lunar_library(
    NAME Astral
    INCLUDE_PATH Astral

    API_HEADER_FILES
        include/QueryExecutor.hpp

    PRIVATE_DEPENDENCIES
        LunarDB_Common_QueryData
        LunarDB_Common_CppExtensions
        LunarDB_Selenity
        LunarDB_Crescentum

    SOURCE_FILES
        src/QueryExecutor.cpp

        src/Executors/CreateExecutor.cpp
        src/Executors/DropExecutor.cpp
        src/Executors/MigrateExecutor.cpp
        src/Executors/TruncateExecutor.cpp
        src/Executors/RenameExecutor.cpp
        src/Executors/SelectExecutor.cpp
        src/Executors/InsertExecutor.cpp
        src/Executors/UpdateExecutor.cpp
        src/Executors/DeleteExecutor.cpp
        src/Executors/GrantExecutor.cpp
        src/Executors/RevokeExecutor.cpp
        src/Executors/CommitExecutor.cpp
        src/Executors/RollbackExecutor.cpp
        src/Executors/SavePointExecutor.cpp
        src/Executors/DatabaseExecutor.cpp
        src/Executors/RebindExecutor.cpp
        src/Executors/SchemaExecutor.cpp
)

if (LUNAR_ENABLE_TESTING AND LUNAR_BUILD_ASTRAL_TESTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/setup_unit_tests.cmake)
endif()
