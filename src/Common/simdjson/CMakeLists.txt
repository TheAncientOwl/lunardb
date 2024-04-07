add_lunar_library(
    NAME Common_Simdjson
    INCLUDE_PATH Common/Simdjson

    API_HEADER_FILES
        include/simdjson.hpp

    SOURCE_FILES
        src/simdjson.cpp
)
