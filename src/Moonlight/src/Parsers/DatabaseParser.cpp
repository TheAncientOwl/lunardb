#include "CppExtensions/include/Errors.hpp"
#include "QueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace CppExtensions;

namespace {

constexpr auto c_query_prefix{ "database" };

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Database, c_query_prefix)
{
    DECLARE_PARSED_QUERY(Database);

    const auto [database, operation, database_name, to, disk] = extractor.extractTuple<5>();

    Errors::assertKeywordEquals(database, "database");

    Errors::assertNotEmpty(operation, "operation");
    out.operation_type = QueryData::Primitives::DatabaseOperationType::toLiteral(operation);

    out.name = Errors::assertNotEmpty(database_name, "database name");

    if (out.operation_type == QueryData::Primitives::EDatabaseOperationType::Backup)
    {
        Errors::assertKeywordEquals(to, "to");
        Errors::assertKeywordEquals(disk, "disk");

        if (extractor.empty()) { throw Errors::buildMissingError("backup path"); }

        auto backup_path = extractor.data();
        StringUtils::trim(backup_path);
        if (backup_path.empty() || backup_path.size() < 2) { throw Errors::buildMissingError("backup path"); }
        if (backup_path.front() != '"' || backup_path.back() != '"') { throw Errors::buildMissingError("\""); }
        backup_path.remove_prefix(1);
        backup_path.remove_suffix(1);
        out.backup_path = Errors::assertNotEmpty(backup_path, "backup path");
    }
    else if (!extractor.empty()) { throw Errors::buildInvalidQueryFormatError(c_query_prefix); }

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
