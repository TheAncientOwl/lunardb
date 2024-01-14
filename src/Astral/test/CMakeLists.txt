include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

set(TEST_SUITE_PREFIX Astral)

add_lunar_unit_test(
    NAME CreateExecutorTest 
    SOURCE_FILES Executors/CreateExecutorTest.cpp 
    DEPENDENCIES LunarDB_Astral
)

add_lunar_unit_test(
    NAME DropExecutorTest 
    SOURCE_FILES Executors/DropExecutorTest.cpp 
    DEPENDENCIES LunarDB_Astral
)

add_lunar_unit_test(
    NAME MigrateExecutorTest 
    SOURCE_FILES Executors/MigrateExecutorTest.cpp 
    DEPENDENCIES LunarDB_Astral
)

add_lunar_unit_test(
    NAME TruncateExecutorTest 
    SOURCE_FILES Executors/TruncateExecutorTest.cpp 
    DEPENDENCIES LunarDB_Astral
)

add_lunar_unit_test(
    NAME RenameExecutorTest 
    SOURCE_FILES Executors/RenameExecutorTest.cpp 
    DEPENDENCIES LunarDB_Astral
)

add_lunar_unit_test(
    NAME SelectExecutorTest 
    SOURCE_FILES Executors/SelectExecutorTest.cpp 
    DEPENDENCIES LunarDB_Astral
)

add_lunar_unit_test(
    NAME InsertExecutorTest 
    SOURCE_FILES Executors/InsertExecutorTest.cpp 
    DEPENDENCIES LunarDB_Astral
)

add_lunar_unit_test(
    NAME UpdateExecutorTest 
    SOURCE_FILES Executors/UpdateExecutorTest.cpp 
    DEPENDENCIES LunarDB_Astral
)

add_lunar_unit_test(
    NAME DeleteExecutorTest 
    SOURCE_FILES Executors/DeleteExecutorTest.cpp 
    DEPENDENCIES LunarDB_Astral
)

add_lunar_unit_test(
    NAME LockExecutorTest 
    SOURCE_FILES Executors/LockExecutorTest.cpp 
    DEPENDENCIES LunarDB_Astral
)

add_lunar_unit_test(
    NAME GrantExecutorTest 
    SOURCE_FILES Executors/GrantExecutorTest.cpp 
    DEPENDENCIES LunarDB_Astral
)

add_lunar_unit_test(
    NAME RevokeExecutorTest 
    SOURCE_FILES Executors/RevokeExecutorTest.cpp 
    DEPENDENCIES LunarDB_Astral
)

add_lunar_unit_test(
    NAME CommitExecutorTest 
    SOURCE_FILES Executors/CommitExecutorTest.cpp 
    DEPENDENCIES LunarDB_Astral
)

add_lunar_unit_test(
    NAME RollbackExecutorTest 
    SOURCE_FILES Executors/RollbackExecutorTest.cpp 
    DEPENDENCIES LunarDB_Astral
)

add_lunar_unit_test(
    NAME SavePointExecutorTest 
    SOURCE_FILES Executors/SavePointExecutorTest.cpp 
    DEPENDENCIES LunarDB_Astral
)

add_lunar_unit_test(
    NAME IndexExecutorTest 
    SOURCE_FILES Executors/IndexExecutorTest.cpp 
    DEPENDENCIES LunarDB_Astral
)

add_lunar_unit_test(
    NAME DatabaseExecutorTest 
    SOURCE_FILES Executors/DatabaseExecutorTest.cpp 
    DEPENDENCIES LunarDB_Astral
)

add_lunar_unit_test(
    NAME ViewExecutorTest 
    SOURCE_FILES Executors/ViewExecutorTest.cpp 
    DEPENDENCIES LunarDB_Astral
)

add_lunar_unit_test(
    NAME RebindExecutorTest 
    SOURCE_FILES Executors/RebindExecutorTest.cpp 
    DEPENDENCIES LunarDB_Astral
)

add_lunar_unit_test(
    NAME SchemaExecutorTest 
    SOURCE_FILES Executors/SchemaExecutorTest.cpp 
    DEPENDENCIES LunarDB_Astral
)

