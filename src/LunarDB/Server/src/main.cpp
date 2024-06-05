#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <iostream>
#include <string>
#include <thread>

using tcp = boost::asio::ip::tcp;

int main()
{
    auto const address = boost::asio::ip::make_address("127.0.0.1");
    auto const port = static_cast<unsigned short>(8083);

    boost::asio::io_context ioc{1};
    tcp::acceptor acceptor{ioc, {address, port}};

    while (true)
    {
        try
        {
            tcp::socket socket{ioc};

            std::cout << "[INFO] Accepting socket" << std::endl;
            acceptor.accept(socket);
            std::cout << "[INFO] Socket accepted" << std::endl;

            boost::beast::websocket::stream<tcp::socket> ws{std::move(socket)};

            std::cout << "[INFO] Accepting websocket" << std::endl;
            ws.accept();
            std::cout << "[INFO] Websocket accepted" << std::endl;

            while (true)
            {
                std::cout << "Reading..." << std::endl;
                boost::beast::flat_buffer buffer{};

                ws.read(buffer);

                auto const out = boost::beast::buffers_to_string(buffer.cdata());
                std::cout << "[MESSAGE] " << out << std::endl;

                // ws.write(buffer.data());
                std::cout << "Writing..." << std::endl;
                ws.write(boost::beast::net::buffer("Hello from C++!"));
                std::cout << "===================================" << std::endl;
            }
            std::cout << "--------------" << std::endl;
        }
        catch (std::exception const& e)
        {
            std::cout << "[ERROR] " << e.what() << std::endl;
        }
    }
}
