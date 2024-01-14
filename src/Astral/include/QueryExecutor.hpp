#pragma once

#include "Moonlight/include/ParsedQuery.hpp"

namespace LunarDB::Astral::API::QueryExecutor {

struct Config {};

void executeQuery(const Moonlight::API::ParsedQuery& parsed_query, const Config& config);

} // namespace LunarDB::Astral::API::QueryExecutor
