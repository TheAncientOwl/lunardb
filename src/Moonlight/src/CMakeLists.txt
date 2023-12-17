include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

add_library(LunarDB_Moonlight SHARED
    ParsedQuery.cpp
    QueryExtractor.cpp
    Utils.cpp
    Primitives.cpp

    Parsers/CreateParser.cpp
    Parsers/DropParser.cpp
    Parsers/MigrateParser.cpp
    Parsers/TruncateParser.cpp
    Parsers/RenameParser.cpp
    Parsers/SelectParser.cpp
    Parsers/InsertParser.cpp
    Parsers/UpdateParser.cpp
    Parsers/DeleteParser.cpp
    Parsers/LockParser.cpp
    Parsers/GrantParser.cpp
    Parsers/RevokeParser.cpp
    Parsers/CommitParser.cpp
    Parsers/RollbackParser.cpp
    Parsers/SavePointParser.cpp
    Parsers/IndexParser.cpp
    Parsers/DatabaseParser.cpp
    Parsers/ViewParser.cpp
    Parsers/RebindParser.cpp
)
