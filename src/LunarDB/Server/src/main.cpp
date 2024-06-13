#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <string>

#include "LunarDB/Crescentum/Logger.hpp"
#include "LunarDB/LunarDB/Common/QueryHandlingUtils.hpp"
#include "LunarDB/Selenity/SchemasCatalog.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"

LUNAR_DECLARE_LOGGER_MODULE(MODULE_LUNARDB_SRV)

int main()
{
    LunarDB::Selenity::API::SystemCatalog::Instance().loadConfigs();
    LunarDB::Selenity::API::SchemasCatalog::Instance().clearCache();

    auto const address = boost::asio::ip::make_address("127.0.0.1");
    auto const port = static_cast<unsigned short>(8083);

    boost::asio::io_context ioc{1};
    boost::asio::ip::tcp::acceptor acceptor{ioc, {address, port}};

    CLOG_INFO("Server started on 127.0.0.1:8083");

    while (true)
    {
        try
        {
            boost::asio::ip::tcp::socket socket{ioc};

            CLOG_INFO("Waiting for client socket connection...");
            acceptor.accept(socket);
            CLOG_INFO("Client socket connected");

            boost::beast::websocket::stream<boost::asio::ip::tcp::socket> ws{std::move(socket)};

            CLOG_VERBOSE("Waiting for client websocket connection...");
            ws.accept();
            CLOG_INFO("Client websocket socket connected");

            while (true)
            {
                boost::beast::flat_buffer buffer{};

                CLOG_INFO("Waiting for query...");
                ws.read(buffer);

                auto const query = boost::beast::buffers_to_string(buffer.cdata());
                CLOG_VERBOSE("Received query ->", query);

                auto on_success = [&ws](auto message) mutable {
                    ws.write(boost::beast::net::buffer(message));
                };

                auto on_selection = [&ws](auto message, auto fields) mutable {
                    ws.write(boost::beast::net::buffer(message));
                };

                auto& on_error = on_success;

                LunarDB::Common::QueryHandlingUtils::handleQuery(
                    query, lunar_logger_module, on_success, on_selection, on_error);
            }
        }
        catch (boost::system::system_error const& e)
        {
            if (e.code() == boost::beast::websocket::error::closed)
            {
                CLOG_INFO("Socket connection ended gracefully");
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
