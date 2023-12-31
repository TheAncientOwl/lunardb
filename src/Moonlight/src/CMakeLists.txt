add_library(LunarDB_Moonlight STATIC
    ParsedQuery.cpp
    QueryExtractor.cpp
    Utils.cpp
    Errors.cpp
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
    Parsers/SchemaParser.cpp

    QueryDataHelpers/Equality.cpp
    QueryDataHelpers/Init.cpp
    QueryDataHelpers/Ostream.cpp
)

target_link_libraries(LunarDB_Moonlight simdjson)
