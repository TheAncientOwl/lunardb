add_lunar_library(
    NAME Astral

    SOURCE_FILES
        QueryExecutor.cpp
    
        DEPENDENCIES
            LunarDB_Common_QueryData
            LunarDB_Common_CppExtensions
)
