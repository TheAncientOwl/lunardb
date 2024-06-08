#pragma once

#include <string>

#include "LunarDB/Crescentum/Logger.hpp"
#include "LunarDB/Moonlight/QueryParser.hpp"

namespace LunarDB::Common::QueryHandlingUtils {

std::string getSuccessMessage(LunarDB::Moonlight::API::ParsedQuery const& parsed_query);

template <typename OnSuccess, typename OnSelection, typename OnError>
void handleQuery(
    std::string_view query,
    LunarDB::Crescentum::API::ELunarModule lunar_logger_module,
    OnSuccess&& on_success,
    OnSelection&& on_selection,
    OnError&& on_error);

} // namespace LunarDB::Common::QueryHandlingUtils

#include "LunarDB/LunarDB/Common/private/QueryHandlingUtils.inl"
