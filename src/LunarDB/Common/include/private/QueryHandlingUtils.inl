#pragma once

#include <nlohmann/json.hpp>
#include <ranges>
#include <sstream>

#include "LunarDB/Astral/QueryExecutor.hpp"
#include "LunarDB/Common/CppExtensions/Timer.hpp"
#include "LunarDB/Common/CppExtensions/UniqueID.hpp"
#include "LunarDB/Moonlight/QueryParser.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"

#include "LunarDB/LunarDB/Common/QueryHandlingUtils.hpp"

namespace LunarDB::Common::QueryHandlingUtils {

std::string getSuccessMessage(LunarDB::Moonlight::API::ParsedQuery const& parsed_query);

template <typename OnSuccess, typename OnSelection, typename OnError>
void handleQuery(
    std::string_view query,
    LunarDB::Crescentum::API::ELunarModule lunar_logger_module,
    OnSuccess&& on_success,
    OnSelection&& on_selection,
    OnError&& on_error)
{
    auto const get_query_identifier = []() {
        std::ostringstream oss{};
        auto const uid{LunarDB::Common::CppExtensions::UniqueID::generate()};
        oss << "QueryID(" << uid << ")";
        return oss.str();
    };

    auto const query_identifier{get_query_identifier()};
    LunarDB::Common::CppExtensions::Timer query_timer{};

    CLOG_VERBOSE(query_identifier, "-> Processing started");

    try
    {
        LunarDB::Common::CppExtensions::Timer timer{};

        CLOG_VERBOSE("[Handler] Starting query parsing...");
        timer.reset();
        auto const parsed_query = LunarDB::Moonlight::API::parseQuery(query);
        CLOG_VERBOSE("[Handler] Finished query parsing, elapsed", timer.elapsedExtended());

        CLOG_VERBOSE("[Handler] Starting query execution...");
        timer.reset();
        LunarDB::Astral::API::executeQuery(parsed_query);
        CLOG_VERBOSE("[Handler] Finished query execution, elapsed", timer.elapsedExtended());

        if (parsed_query.type() == LunarDB::Common::QueryData::Primitives::EQueryType::Select)
        {
            auto& system_catalog{LunarDB::Selenity::API::SystemCatalog::Instance()};
            auto const& current_selection{system_catalog.getCurrentSelection()};

            CLOG_VERBOSE("[Handler] Jsonifying current selection...");
            timer.reset();
            std::stringstream oss{};
            oss << R"({ "selection": [ )";
            if (!current_selection.empty())
            {
                auto const select_fields =
                    [&fields = parsed_query.get<LunarDB::Common::QueryData::Select>().fields](
                        auto const& obj) -> nlohmann::json {
                    auto const& obj_json{obj->getJSON()};
                    nlohmann::json out{};

                    for (auto const& field : fields)
                    {
                        out[field] = obj_json[field];
                    }

                    return out;
                };

                oss << select_fields(current_selection[0]).dump();
                for (auto const index : std::ranges::iota_view{1u, current_selection.size()})
                {
                    oss << ", " << select_fields(current_selection[index]).dump();
                }
            }
            oss << "] }";
            CLOG_VERBOSE(
                "[Handler] Jsonifying current selection finished, elapsed", timer.elapsedExtended());
            auto current_selection_str{std::move(oss.str())};

            CLOG_VERBOSE("[Handler] Sending current selection:", current_selection_str);
            timer.reset();
            on_selection(current_selection_str);
            CLOG_VERBOSE(
                "[Handler] Sending current selection finished, elapsed", timer.elapsedExtended());

            CLOG_VERBOSE("Clearing current selection...");
            system_catalog.clearCurrentSelection();
            CLOG_VERBOSE("Current selection cleared");
        }
        else
        {
            auto const message{LunarDB::Common::QueryHandlingUtils::getSuccessMessage(parsed_query)};
            CLOG_VERBOSE("Execution success, sending success message:", message);
            on_success(message);
            CLOG_VERBOSE("Success message sent");
        }
    }
    catch (std::exception const& e)
    {
        CLOG_VERBOSE("Failed to handle query, cause:", e.what());
        on_error(e.what());
    }

    CLOG_VERBOSE(query_identifier, "-> Processing finished, elapsed", query_timer.elapsedExtended());
}

} // namespace LunarDB::Common::QueryHandlingUtils
