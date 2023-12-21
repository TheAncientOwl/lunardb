#include "QueryParsers.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "database" };

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Database, c_query_prefix)
{
    DECLARE_PARSED_QUERY(Database);

    const auto [database, operation, database_name, to, disk] = extractor.extractTuple<5>();

    Utils::checkKeywordEquals(database, "database");

    Utils::checkNotEmpty(operation, "operation");
    out.operation_type = QueryData::Primitives::DatabaseOperationType::toLiteral(operation);

    out.name = Utils::checkNotEmpty(database_name, "database name");

    if (out.operation_type == QueryData::Primitives::EDatabaseOperationType::Backup)
    {
        Utils::checkKeywordEquals(to, "to");
        Utils::checkKeywordEquals(disk, "disk");

        if (extractor.empty()) { throw Utils::buildMissingError("backup path"); }

        auto backup_path = extractor.data();
        Utils::trim(backup_path);
        if (backup_path.empty() || backup_path.size() < 2) { throw Utils::buildMissingError("backup path"); }
        if (backup_path.front() != '"' || backup_path.back() != '"') { throw Utils::buildMissingError("\""); }
        backup_path.remove_prefix(1);
        backup_path.remove_suffix(1);
        out.backup_path = Utils::checkNotEmpty(backup_path, "backup path");
    }
    else if (!extractor.empty()) { throw Utils::buildInvalidQueryFormatError(c_query_prefix); }

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
