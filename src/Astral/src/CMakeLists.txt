add_lunar_library(
    NAME Astral

    SOURCE_FILES
        QueryExecutor.cpp

        Executors/CreateExecutor.cpp
        Executors/DropExecutor.cpp
        Executors/MigrateExecutor.cpp
        Executors/TruncateExecutor.cpp
        Executors/RenameExecutor.cpp
        Executors/SelectExecutor.cpp
        Executors/InsertExecutor.cpp
        Executors/UpdateExecutor.cpp
        Executors/DeleteExecutor.cpp
        Executors/LockExecutor.cpp
        Executors/GrantExecutor.cpp
        Executors/RevokeExecutor.cpp
        Executors/CommitExecutor.cpp
        Executors/RollbackExecutor.cpp
        Executors/SavePointExecutor.cpp
        Executors/IndexExecutor.cpp
        Executors/DatabaseExecutor.cpp
        Executors/ViewExecutor.cpp
        Executors/RebindExecutor.cpp
        Executors/SchemaExecutor.cpp
    
        DEPENDENCIES
            LunarDB_Common_QueryData
            LunarDB_Common_CppExtensions
)
