#include "LunarDB/Selenity/Managers/Collections/EvaluateWhereClause.hpp"

namespace LunarDB::Selenity::API::Managers::Collections::WhereClause {

bool evaluate(
    std::unique_ptr<AbstractManager::ICollectionEntry> const& entry,
    Common::QueryData::WhereClause const& where_clause)
{
    return true;
}

} // namespace LunarDB::Selenity::API::Managers::Collections::WhereClause
