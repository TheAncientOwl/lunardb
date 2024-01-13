add_library(LunarDB_Common_QueryData STATIC
    Primitives.cpp
    Helpers/Init.cpp
    Helpers/Equality.cpp
    Helpers/Ostream.cpp
)

target_link_libraries(LunarDB_Common_QueryData 
    PRIVATE 
        LunarDB_Common_CppExtensions
)
