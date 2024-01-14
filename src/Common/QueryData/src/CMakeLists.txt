add_lunar_common_library(
    NAME QueryData

    SOURCE_FILES
        Primitives.cpp
        Helpers/Init.cpp
        Helpers/Equality.cpp
        Helpers/Ostream.cpp
        
    DEPENDENCIES
        LunarDB_Common_CppExtensions
)
