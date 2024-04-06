add_lunar_library(
    NAME Common_QueryData

    SOURCE_FILES
        Primitives.cpp
        Helpers/Init.cpp
        Helpers/Equality.cpp
        Helpers/Ostream.cpp
        
    DEPENDENCIES
        LunarDB_Common_CppExtensions
)
