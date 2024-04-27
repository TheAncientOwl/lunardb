set(TEST_SUITE_PREFIX Astral)

add_lunar_unit_test(
    NAME CreateExecutorTest 
    SOURCE_FILES test/Executors/CreateExecutorTest.cpp 
    DEPENDENCIES 
        LunarDB_Astral
        LunarDB_Moonlight
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
)

add_lunar_unit_test(
    NAME DropExecutorTest 
    SOURCE_FILES test/Executors/DropExecutorTest.cpp 
    DEPENDENCIES 
        LunarDB_Astral
        LunarDB_Moonlight
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
)

add_lunar_unit_test(
    NAME MigrateExecutorTest 
    SOURCE_FILES test/Executors/MigrateExecutorTest.cpp 
    DEPENDENCIES 
        LunarDB_Astral
        LunarDB_Moonlight
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
)

add_lunar_unit_test(
    NAME TruncateExecutorTest 
    SOURCE_FILES test/Executors/TruncateExecutorTest.cpp 
    DEPENDENCIES 
        LunarDB_Astral
        LunarDB_Moonlight
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
)

add_lunar_unit_test(
    NAME RenameExecutorTest 
    SOURCE_FILES test/Executors/RenameExecutorTest.cpp 
    DEPENDENCIES 
        LunarDB_Astral
        LunarDB_Moonlight
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
)

add_lunar_unit_test(
    NAME SelectExecutorTest 
    SOURCE_FILES test/Executors/SelectExecutorTest.cpp 
    DEPENDENCIES 
        LunarDB_Astral
        LunarDB_Moonlight
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
)

add_lunar_unit_test(
    NAME InsertExecutorTest 
    SOURCE_FILES test/Executors/InsertExecutorTest.cpp 
    DEPENDENCIES 
        LunarDB_Astral
        LunarDB_Moonlight
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
)

add_lunar_unit_test(
    NAME UpdateExecutorTest 
    SOURCE_FILES test/Executors/UpdateExecutorTest.cpp 
    DEPENDENCIES 
        LunarDB_Astral
        LunarDB_Moonlight
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
)

add_lunar_unit_test(
    NAME DeleteExecutorTest 
    SOURCE_FILES test/Executors/DeleteExecutorTest.cpp 
    DEPENDENCIES 
        LunarDB_Astral
        LunarDB_Moonlight
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
)

add_lunar_unit_test(
    NAME LockExecutorTest 
    SOURCE_FILES test/Executors/LockExecutorTest.cpp 
    DEPENDENCIES 
        LunarDB_Astral
        LunarDB_Moonlight
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
)

add_lunar_unit_test(
    NAME GrantExecutorTest 
    SOURCE_FILES test/Executors/GrantExecutorTest.cpp 
    DEPENDENCIES 
        LunarDB_Astral
        LunarDB_Moonlight
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
)

add_lunar_unit_test(
    NAME RevokeExecutorTest 
    SOURCE_FILES test/Executors/RevokeExecutorTest.cpp 
    DEPENDENCIES 
        LunarDB_Astral
        LunarDB_Moonlight
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
)

add_lunar_unit_test(
    NAME CommitExecutorTest 
    SOURCE_FILES test/Executors/CommitExecutorTest.cpp 
    DEPENDENCIES 
        LunarDB_Astral
        LunarDB_Moonlight
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
)

add_lunar_unit_test(
    NAME RollbackExecutorTest 
    SOURCE_FILES test/Executors/RollbackExecutorTest.cpp 
    DEPENDENCIES 
        LunarDB_Astral
        LunarDB_Moonlight
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
)

add_lunar_unit_test(
    NAME SavePointExecutorTest 
    SOURCE_FILES test/Executors/SavePointExecutorTest.cpp 
    DEPENDENCIES 
        LunarDB_Astral
        LunarDB_Moonlight
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
)

add_lunar_unit_test(
    NAME IndexExecutorTest 
    SOURCE_FILES test/Executors/IndexExecutorTest.cpp 
    DEPENDENCIES 
        LunarDB_Astral
        LunarDB_Moonlight
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
)

add_lunar_unit_test(
    NAME DatabaseExecutorTest 
    SOURCE_FILES test/Executors/DatabaseExecutorTest.cpp 
    DEPENDENCIES 
        LunarDB_Astral
        LunarDB_Moonlight
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
)

add_lunar_unit_test(
    NAME ViewExecutorTest 
    SOURCE_FILES test/Executors/ViewExecutorTest.cpp 
    DEPENDENCIES 
        LunarDB_Astral
        LunarDB_Moonlight
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
)

add_lunar_unit_test(
    NAME RebindExecutorTest 
    SOURCE_FILES test/Executors/RebindExecutorTest.cpp 
    DEPENDENCIES 
        LunarDB_Astral
        LunarDB_Moonlight
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
)

add_lunar_unit_test(
    NAME SchemaExecutorTest 
    SOURCE_FILES test/Executors/SchemaExecutorTest.cpp 
    DEPENDENCIES 
        LunarDB_Astral
        LunarDB_Moonlight
        LunarDB_Selenity
        LunarDB_Common_CppExtensions
)
