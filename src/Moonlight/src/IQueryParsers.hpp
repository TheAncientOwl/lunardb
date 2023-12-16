#pragma once

#include "ParsedQuery.hpp"

#define PROVIDE_QUERY_PARSER(Specialization) \
class Specialization ## Parser : public IQueryParser { \
public: \
    inline const char* queryPrefix() const override; \
    API::ParsedQuery parse(std::string_view query) const override; \
};

#define PROVIDE_QUERY_PARSER_IMPL(Specialization, QueryPrefix) \
inline const char* Specialization ## Parser::queryPrefix() const { return QueryPrefix; } \
API::ParsedQuery Specialization ## Parser::parse(std::string_view query) const

#define DECLARE_PARSED_QUERY(name, type) \
API::ParsedQuery parsed_query = API::ParsedQuery::make<QueryData::type>(); \
auto& name = parsed_query.get<QueryData::type>()

#define RETURN_PARSED_QUERY \
return parsed_query

namespace LunarDB::Moonlight::Implementation {

class IQueryParser
{
public: // methods
    virtual inline const char* queryPrefix() const = 0;
    virtual API::ParsedQuery parse(std::string_view query) const = 0;

public:
    IQueryParser() = default;

    IQueryParser(const IQueryParser&) = delete;
    IQueryParser& operator=(const IQueryParser&) = delete;

    IQueryParser(IQueryParser&&) noexcept = delete;
    IQueryParser& operator=(IQueryParser&&) noexcept = delete;

    virtual ~IQueryParser() = default;
};

PROVIDE_QUERY_PARSER(Create)
PROVIDE_QUERY_PARSER(Drop)
PROVIDE_QUERY_PARSER(Migrate)
PROVIDE_QUERY_PARSER(Truncate)
PROVIDE_QUERY_PARSER(Rename)
PROVIDE_QUERY_PARSER(Select)
PROVIDE_QUERY_PARSER(Insert)
PROVIDE_QUERY_PARSER(Update)
PROVIDE_QUERY_PARSER(Delete)
PROVIDE_QUERY_PARSER(Lock)
PROVIDE_QUERY_PARSER(Grant)
PROVIDE_QUERY_PARSER(Revoke)
PROVIDE_QUERY_PARSER(Commit)
PROVIDE_QUERY_PARSER(Rollback)
PROVIDE_QUERY_PARSER(SavePoint)
PROVIDE_QUERY_PARSER(Index)
PROVIDE_QUERY_PARSER(Database)
PROVIDE_QUERY_PARSER(View)

#define QUERY_PARSERS \
    CreateParser, \
    DropParser, \
    MigrateParser, \
    TruncateParser, \
    RenameParser, \
    SelectParser, \
    InsertParser, \
    UpdateParser, \
    DeleteParser, \
    LockParser, \
    GrantParser, \
    RevokeParser, \
    CommitParser, \
    RollbackParser, \
    SavePointParser, \
    IndexParser, \
    DatabaseParser, \
    ViewParser

} // namespace LunarDB::Moonlight::Implementation