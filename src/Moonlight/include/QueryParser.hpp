#pragma once

#include "ParsedQuery.hpp"

namespace LunarDB::Moonlight::API {

///
/// @brief Self explanatory.
/// @param [in] query -> String representation of a query
/// @return @c Moonlight::API::ParsedQuery
///
ParsedQuery parseQuery(std::string_view query);

} // namespace LunarDB::Moonlight::API
