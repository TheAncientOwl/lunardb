#pragma once

#include "Astral/SelenityDependencies.hpp"
#include "Moonlight/ParsedQuery.hpp"

namespace LunarDB::Astral::API {

void executeQuery(Moonlight::API::ParsedQuery const& parsed_query, SelenityDependencies const& config);

} // namespace LunarDB::Astral::API
