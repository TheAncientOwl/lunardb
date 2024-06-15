add_lunar_library(
  NAME Common_Utils
  INCLUDE_PATH LunarDB/Common

  API_HEADER_FILES
    include/QueryHandlingUtils.hpp

    include/private/QueryHandlingUtils.inl

  PRIVATE_DEPENDENCIES
    LunarDB_Common_QueryData
    LunarDB_Common_CppExtensions
    LunarDB_Astral
    LunarDB_BrightMoon
    # LunarDB_Celestial
    LunarDB_Crescentum
    LunarDB_Moonlight
    LunarDB_Selenity

  SOURCE_FILES
    src/QueryHandlingUtils.cpp
)
