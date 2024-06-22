#pragma once

#include <string>

#include "LunarDB/Crescentum/Logger.hpp"
#include "LunarDB/Moonlight/QueryParser.hpp"

namespace LunarDB::Common::QueryHandlingUtils {

std::string getSuccessMessage(LunarDB::Moonlight::API::ParsedQuery const& parsed_query);

inline void doNothing(LunarDB::Moonlight::API::ParsedQuery const&) {};

template <typename OnSuccess, typename OnSelection, typename OnError, typename AfterParsing = decltype(doNothing)>
void handleQuery(
    std::string_view query,
    LunarDB::Crescentum::API::ELunarModule lunar_logger_module,
    OnSuccess&& on_success,
    OnSelection&& on_selection,
    OnError&& on_error,
    AfterParsing&& after_parsing = doNothing);

} // namespace LunarDB::Common::QueryHandlingUtils

#include "LunarDB/LunarDB/Common/private/QueryHandlingUtils.inl"
