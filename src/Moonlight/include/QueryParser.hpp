#pragma once

#include "Moonlight/ParsedQuery.hpp"

namespace LunarDB::Moonlight::API {

ParsedQuery parseQuery(std::string_view query);

} // namespace LunarDB::Moonlight::API
