#include "LunarDB/LunarDB/Common/QueryHandlingUtils.hpp"

using namespace std::string_literals;

namespace LunarDB::Common::QueryHandlingUtils {

std::string getSuccessMessage(LunarDB::Moonlight::API::ParsedQuery const& parsed_query)
{
    using EQueryType = LunarDB::Common::QueryData::Primitives::EQueryType;

    switch (parsed_query.type())
    {
    case EQueryType::Create: {
        auto const& query_data = parsed_query.get<LunarDB::Common::QueryData::Create>();
        if (static_cast<bool>(query_data.single))
        {
            return "Collection created successfully";
        }
        else if (static_cast<bool>(query_data.multiple))
        {
            return "Collections created successfully";
        }
        return "Done";
    }
    case EQueryType::Drop: {
        return "Collection dropped successfully";
    }
    case EQueryType::Migrate: {
        return "Collection migrated successfully";
    }
    case EQueryType::Truncate: {
        return "Collection truncated successfully";
    }
    case EQueryType::Rename: {
        return "Rename successfully";
    }
    case EQueryType::Select: {
        return "Selection finished successfully";
    }
    case EQueryType::Insert: {
        return "Objects inserted successfully";
    }
    case EQueryType::Update: {
        return "Objects updated successfully";
    }
    case EQueryType::Delete: {
        return "Objects deleted successfully";
    }
    case EQueryType::Grant: {
        return "Grant finished successfully";
    }
    case EQueryType::Revoke: {
        return "Revoke finished successfully";
    }
    case EQueryType::Commit: {
        return "Changes commited successfully";
    }
    case EQueryType::Rollback: {
        return "Rollback finished successfully";
    }
    case EQueryType::SavePoint: {
        return "SavePoint finished successfully";
    }
    case EQueryType::Database: {
        auto const& query_data = parsed_query.get<LunarDB::Common::QueryData::Database>();
        switch (query_data.operation_type)
        {
        case LunarDB::Common::QueryData::Primitives::EDatabaseOperationType::Create:
            return "Database created successfully";
            break;
        case LunarDB::Common::QueryData::Primitives::EDatabaseOperationType::Drop:
            return "Database dropped successfully";
            break;
        case LunarDB::Common::QueryData::Primitives::EDatabaseOperationType::Use:
            return "Using database '"s + query_data.name + "' for following transactions";
            break;
        default:
            return "Done";
            break;
        }
    }
    case EQueryType::Rebind: {
        return "Rebind successfully";
    }
    case EQueryType::Schema: {
        return "Schema created successfully";
    }
    case EQueryType::User: {
        return "User operation effectuated successfully";
    }
    case EQueryType::Auth: {
        return "Authentication: OK";
    }
    default:
        return "Done";
        break;
    }
}

} // namespace LunarDB::Common::QueryHandlingUtils
