#pragma once

#include <string>

#include "LunarDB/Crescentum/Logger.hpp"
#include "LunarDB/Moonlight/QueryParser.hpp"

namespace LunarDB::Common::QueryHandlingUtils {

std::string getSuccessMessage(LunarDB::Moonlight::API::ParsedQuery const& parsed_query);

template <typename MessageWriter>
void handleQuery(
    std::string_view query,
    LunarDB::Crescentum::API::ELunarModule lunar_logger_module,
    MessageWriter&& message_writer);

} // namespace LunarDB::Common::QueryHandlingUtils

#include "LunarDB/LunarDB/Common/private/QueryHandlingUtils.inl"
