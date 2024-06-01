add_lunar_executable(
    NAME CLI
    INCLUDE_PATH CLI
    
    API_HEADER_FILES

    PRIVATE_DEPENDENCIES
        LunarDB_Common_QueryData
        LunarDB_Common_CppExtensions
        LunarDB_Astral
        LunarDB_BrightMoon
        LunarDB_Celestial
        LunarDB_Crescentum
        LunarDB_Moonlight
        LunarDB_Selenity

    SOURCE_FILES
        src/main.cpp
)
