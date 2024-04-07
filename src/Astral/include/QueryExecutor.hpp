#pragma once

#include "Moonlight/ParsedQuery.hpp"
#include "Astral/QueryExecutorConfig.hpp"

namespace LunarDB::Astral::API {

void executeQuery(const Moonlight::API::ParsedQuery& parsed_query, const QueryExecutorConfig& config);

} // namespace LunarDB::Astral::API
