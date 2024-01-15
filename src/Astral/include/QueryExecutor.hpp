#pragma once

#include "Moonlight/include/ParsedQuery.hpp"
#include "Astral/include/QueryExecutorConfig.hpp"

namespace LunarDB::Astral::API {

void executeQuery(const Moonlight::API::ParsedQuery& parsed_query, const QueryExecutorConfig& config);

} // namespace LunarDB::Astral::API
