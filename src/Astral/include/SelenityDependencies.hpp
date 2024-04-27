#pragma once

#include "LunarDB/Moonlight/ParsedQuery.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"

namespace LunarDB::Astral::API {

struct SelenityDependencies
{
    Selenity::API::SystemCatalog& db_catalog;
};

} // namespace LunarDB::Astral::API
