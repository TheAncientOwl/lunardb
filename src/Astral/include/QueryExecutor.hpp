#pragma once

#include "Astral/QueryExecutorConfig.hpp"
#include "Moonlight/ParsedQuery.hpp"

namespace LunarDB::Astral::API {

void executeQuery(Moonlight::API::ParsedQuery const& parsed_query, QueryExecutorConfig const& config);

} // namespace LunarDB::Astral::API
