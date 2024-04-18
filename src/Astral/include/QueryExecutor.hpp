#pragma once

#include "Astral/QueryExecutorConfig.hpp"
#include "Moonlight/ParsedQuery.hpp"

namespace LunarDB::Astral::API {

void executeQuery(const Moonlight::API::ParsedQuery& parsed_query, const QueryExecutorConfig& config);

} // namespace LunarDB::Astral::API
