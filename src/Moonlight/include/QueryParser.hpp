#pragma once

#include <string>

#include "ParsedQuery.hpp"

namespace LunarDB::Moonlight::API {

ParsedQuery parseQuery(std::string query);

} // namespace LunarDB::Moonlight::API
