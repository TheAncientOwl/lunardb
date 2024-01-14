add_lunar_library(
    NAME Moonlight

    SOURCE_FILES
        ParsedQuery.cpp
        QueryExtractor.cpp
        Utils.cpp
        Errors.cpp

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

    DEPENDENCIES
        LunarDB_Common_QueryData
        LunarDB_Common_CppExtensions
        LunarDB_Common_Simdjson
)
