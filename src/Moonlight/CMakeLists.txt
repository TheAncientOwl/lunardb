add_lunar_library(
    NAME Moonlight
    INCLUDE_PATH Moonlight

    API_HEADER_FILES
        include/QueryParser.hpp
        include/ParsedQuery.hpp

    PRIVATE_DEPENDENCIES
        LunarDB_Common_QueryData
        LunarDB_Common_CppExtensions
        LunarDB_Common_Simdjson

    SOURCE_FILES
        src/ParsedQuery.cpp
        src/QueryParser.cpp
        src/QueryExtractor.cpp
        src/Utils.cpp
        src/Errors.cpp

        src/Parsers/CreateParser.cpp
        src/Parsers/DropParser.cpp
        src/Parsers/MigrateParser.cpp
        src/Parsers/TruncateParser.cpp
        src/Parsers/RenameParser.cpp
        src/Parsers/SelectParser.cpp
        src/Parsers/InsertParser.cpp
        src/Parsers/UpdateParser.cpp
        src/Parsers/DeleteParser.cpp
        src/Parsers/LockParser.cpp
        src/Parsers/GrantParser.cpp
        src/Parsers/RevokeParser.cpp
        src/Parsers/CommitParser.cpp
        src/Parsers/RollbackParser.cpp
        src/Parsers/SavePointParser.cpp
        src/Parsers/IndexParser.cpp
        src/Parsers/DatabaseParser.cpp
        src/Parsers/ViewParser.cpp
        src/Parsers/RebindParser.cpp
        src/Parsers/SchemaParser.cpp

)

include(${CMAKE_CURRENT_SOURCE_DIR}/test/setup_unit_tests.cmake)
