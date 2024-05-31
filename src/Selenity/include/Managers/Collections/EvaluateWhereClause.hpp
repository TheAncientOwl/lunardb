#pragma once

#include <memory>

#include "LunarDB/Common/QueryData/QueryData.hpp"
#include "LunarDB/Selenity/Managers/Collections/AbstractManager.hpp"

namespace LunarDB::Selenity::API::Managers::Collections::WhereClause {

bool evaluate(
    std::unique_ptr<AbstractManager::ICollectionEntry> const& entry,
    Common::QueryData::WhereClause const& where_clause);

} // namespace LunarDB::Selenity::API::Managers::Collections::WhereClause
