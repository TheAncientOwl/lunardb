#pragma once

#include "Moonlight/include/ParsedQuery.hpp"

namespace LunarDB::Astral::API::QueryExecutor {

void executeQuery(const Moonlight::API::ParsedQuery& parsed_query);

} // namespace LunarDB::Astral::API::QueryExecutor
