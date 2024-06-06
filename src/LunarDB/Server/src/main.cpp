#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <ranges>
#include <sstream>
#include <string>
#include <thread>

#include "LunarDB/Astral/QueryExecutor.hpp"
#include "LunarDB/Common/CppExtensions/UniqueID.hpp"
#include "LunarDB/Moonlight/QueryParser.hpp"
#include "LunarDB/Selenity/SchemasCatalog.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_LUNARDB_SRV)

using namespace std::string_literals;

std::string getSuccessMessage(LunarDB::Moonlight::API::ParsedQuery const& parsed_query)
{
    switch (parsed_query.type())
    {
    case LunarDB::Common::QueryData::Primitives::EQueryType::Database: {
        auto const& query_data = parsed_query.get<LunarDB::Common::QueryData::Database>();
        switch (query_data.operation_type)
        {
        case LunarDB::Common::QueryData::Primitives::EDatabaseOperationType::Create:
            return "Database created successfully";
            break;
        case LunarDB::Common::QueryData::Primitives::EDatabaseOperationType::Drop:
            return "Database dropped successfully";
            break;
        case LunarDB::Common::QueryData::Primitives::EDatabaseOperationType::Use:
            return "Using database '"s + query_data.name + "' for following transactions";
            break;
        default:
            return "Done";
            break;
        }
    }
    case LunarDB::Common::QueryData::Primitives::EQueryType::Schema: {
        return "Schema created successfully";
    }
    case LunarDB::Common::QueryData::Primitives::EQueryType::Create: {
        auto const& query_data = parsed_query.get<LunarDB::Common::QueryData::Create>();
        if (static_cast<bool>(query_data.single))
        {
            return "Collection created successfully";
        }
        else if (static_cast<bool>(query_data.multiple))
        {
            return "Collections created successfully";
        }
        return "Done";
    }
    case LunarDB::Common::QueryData::Primitives::EQueryType::Rebind: {
        return "Rebind successfully";
    }
    case LunarDB::Common::QueryData::Primitives::EQueryType::Insert: {
        return "Objects inserted successfully";
    }
    case LunarDB::Common::QueryData::Primitives::EQueryType::Delete: {
        return "Objects deleted successfully";
    }
    case LunarDB::Common::QueryData::Primitives::EQueryType::Update: {
        return "Objects updated successfully";
    }
    case LunarDB::Common::QueryData::Primitives::EQueryType::Select: {
        return "[table]";
    }
    case LunarDB::Common::QueryData::Primitives::EQueryType::Commit: {
        return "Changes commited successfully";
    }
    default:
        return "Done";
        break;
    }
}

void handleQuery(std::string_view query, boost::beast::websocket::stream<boost::asio::ip::tcp::socket>& ws)
{
    auto const uid{LunarDB::Common::CppExtensions::UniqueID::generate()};
    CLOG_VERBOSE("Start query handling, uid:", uid);

    try
    {
        CLOG_VERBOSE("Start parsing");

        auto const parsed_query = LunarDB::Moonlight::API::parseQuery(query);

        CLOG_VERBOSE("Parsing success, start execution");

        LunarDB::Astral::API::executeQuery(parsed_query);

        if (parsed_query.type() == LunarDB::Common::QueryData::Primitives::EQueryType::Select)
        {
            auto& system_catalog{LunarDB::Selenity::API::SystemCatalog::Instance()};
            auto const& current_selection{system_catalog.getCurrentSelection()};

            CLOG_VERBOSE("Jsonifying current selection");

            std::stringstream ss{};
            ss << R"({ "selection": [ )";

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

                ss << select_fields(current_selection[0]).dump();
                for (auto const index : std::ranges::iota_view{1u, current_selection.size()})
                {
                    ss << ", " << select_fields(current_selection[index]).dump();
                }
            }
            ss << "] }";
            auto current_selection_str{std::move(ss.str())};

            CLOG_VERBOSE("Sending current selection:", current_selection_str);
            ws.write(boost::beast::net::buffer(current_selection_str));

            CLOG_VERBOSE("Clearing current selection...");
            system_catalog.clearCurrentSelection();
            CLOG_VERBOSE("Current selection cleared");
        }
        else
        {
            auto const message{getSuccessMessage(parsed_query)};
            CLOG_VERBOSE("Execution success, sending success message:", message);
            ws.write(boost::beast::net::buffer(message));
            CLOG_VERBOSE("Success message sent");
        }
    }
    catch (std::exception const& e)
    {
        CLOG_VERBOSE("Failed to handle query, cause:", e.what());
        ws.write(boost::beast::net::buffer(std::string(e.what())));
    }

    CLOG_VERBOSE("End query handling, uid", uid);
}

int main()
{
    LunarDB::Selenity::API::SchemasCatalog::Instance().clearCache();
    LunarDB::Selenity::API::SystemCatalog::Instance().loadConfigs();

    auto const address = boost::asio::ip::make_address("127.0.0.1");
    auto const port = static_cast<unsigned short>(8083);

    boost::asio::io_context ioc{1};
    boost::asio::ip::tcp::acceptor acceptor{ioc, {address, port}};

    CLOG_INFO("WebSocket started running on 127.0.0.1:8083");

    while (true)
    {
        try
        {
            boost::asio::ip::tcp::socket socket{ioc};

            CLOG_INFO("Accepting socket");
            acceptor.accept(socket);
            CLOG_INFO("Socket accepted");

            boost::beast::websocket::stream<boost::asio::ip::tcp::socket> ws{std::move(socket)};

            CLOG_VERBOSE("Accepting websocket");
            ws.accept();
            CLOG_VERBOSE("Websocket accepted");

            while (true)
            {
                boost::beast::flat_buffer buffer{};

                CLOG_INFO("Reading query");
                ws.read(buffer);

                auto const out = boost::beast::buffers_to_string(buffer.cdata());
                CLOG_VERBOSE("Received query ->", out);

                handleQuery(out, ws);
            }
        }
        catch (boost::system::system_error const& e)
        {
            if (e.code() == boost::beast::websocket::error::closed)
            {
                CLOG_INFO("Connection ended gracefully");
            }
            else
            {
                CLOG_ERROR("Boost system error: ", e.what());
            }
        }
        catch (std::exception const& e)
        {
            CLOG_ERROR(e.what());
        }
    }

    return EXIT_SUCCESS;
}
