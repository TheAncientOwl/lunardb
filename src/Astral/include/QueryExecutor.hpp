#pragma once

#include "LunarDB/Moonlight/ParsedQuery.hpp"

namespace LunarDB::Astral::API {

///
/// @brief Executes parsed query
/// @param [in] parsed_query
/// @param [in] config
///
void executeQuery(Moonlight::API::ParsedQuery const& parsed_query);

} // namespace LunarDB::Astral::API
