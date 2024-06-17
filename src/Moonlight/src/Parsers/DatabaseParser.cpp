#include "Errors.hpp"
#include "LunarDB/Moonlight/QueryParsers.hpp"
#include "Utils.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_MOONLIGHT)

namespace LunarDB::Moonlight::Implementation {

namespace StringUtils = LunarDB::Common::CppExtensions::StringUtils;

namespace {

constexpr auto c_query_prefix{"database"};

} // namespace

API::ParsedQuery Database::parse(QueryExtractor extractor)
{
    CLOG_VERBOSE("Database::parse()");

    auto out_parsed_query = API::ParsedQuery::make<Common::QueryData::Database>();
    auto& out = out_parsed_query.get<Common::QueryData::Database>();

    auto const [database, operation, database_name, to, disk] = extractor.extractTuple<5>();

    Errors::assertKeywordEquals(database, "database");

    Errors::assertNotEmpty(operation, "operation");
    out.operation_type = Common::QueryData::Primitives::DatabaseOperationType::toLiteral(operation);

    out.name = Errors::assertNotEmpty(database_name, "database name");

    if (out.operation_type == Common::QueryData::Primitives::EDatabaseOperationType::Backup)
    {
        Errors::assertKeywordEquals(to, "to");
        Errors::assertKeywordEquals(disk, "disk");

        if (extractor.empty())
        {
            throw Errors::buildMissingError("backup path");
        }

        auto backup_path = extractor.data();
        StringUtils::trim(backup_path);
        if (backup_path.empty() || backup_path.size() < 2)
        {
            throw Errors::buildMissingError("backup path");
        }
        if (backup_path.front() != '"' || backup_path.back() != '"')
        {
            throw Errors::buildMissingError("\"");
        }
        backup_path.remove_prefix(1);
        backup_path.remove_suffix(1);
        out.backup_path = Errors::assertNotEmpty(backup_path, "backup path");
    }
    else if (!extractor.empty())
    {
        throw Errors::buildInvalidQueryFormatError(c_query_prefix);
    }

    return out_parsed_query;
}

} // namespace LunarDB::Moonlight::Implementation
