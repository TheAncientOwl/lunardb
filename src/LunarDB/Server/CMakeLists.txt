add_lunar_executable(
    NAME Server
    INCLUDE_PATH Server
    
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
        Boost::system

    SOURCE_FILES
        src/main.cpp
)
