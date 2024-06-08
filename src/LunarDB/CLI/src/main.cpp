#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

#include "LunarDB/Astral/QueryExecutor.hpp"
#include "LunarDB/Common/CppExtensions/ConsoleColorOutput.hpp"
#include "LunarDB/Common/CppExtensions/StringUtils.hpp"
#include "LunarDB/Crescentum/Logger.hpp"
#include "LunarDB/LunarDB/Common/QueryHandlingUtils.hpp"
#include "LunarDB/Moonlight/QueryParser.hpp"
#include "LunarDB/Selenity/SchemasCatalog.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"
#include "QueryPrompt.hpp"

LUNAR_DECLARE_LOGGER_MODULE(MODULE_LUNARDB_SRV);

void writeMessage(std::string const& message)
{
    std::cout << ccolor::dark_gray << "[" << ccolor::green << "Success" << ccolor::dark_gray << "] "
              << ccolor::lime << message << ccolor::reset << std::endl;
}

void writeSelection(std::string const& selection)
{
    std::cout << ccolor::dark_gray << "[" << ccolor::purple << "Selection" << ccolor::dark_gray
              << "] " << ccolor::pink << selection << ccolor::reset << std::endl;
}

void writeError(std::string const& error)
{
    std::cout << ccolor::dark_gray << "[" << ccolor::dark_red << "Error" << ccolor::dark_gray
              << "] " << ccolor::light_red << error << ccolor::reset << std::endl;
}

int main(int argc, char const* argv[])
{
    LunarDB::Selenity::API::SchemasCatalog::Instance().clearCache();
    LunarDB::Selenity::API::SystemCatalog::Instance().loadConfigs();

    std::istream* input_stream_ptr{&std::cin};
    std::ifstream input_file{};
    if (argc >= 2)
    {
        input_file.open(argv[1]);
        input_stream_ptr = &input_file;
    }
    LunarDB::CLI::QueryPrompt prompt{*input_stream_ptr};

    do
    {
        std::cout << ccolor::dark_red << "root" << ccolor::dark_gray << "@" << ccolor::purple
                  << "lunardb" << ccolor::dark_gray << "$ " << ccolor::light_gray;

        auto const query = prompt.readQuery();

        if (input_stream_ptr == &input_file)
        {
            std::cout << query << std::endl;
        }

        auto message_writer = [](std::string const& message) { std::cout << message << std::endl; };

        LunarDB::Common::QueryHandlingUtils::handleQuery(
            query, lunar_logger_module, writeMessage, writeSelection, writeError);
    } while (!prompt.done());

    LunarDB::Selenity::API::SystemCatalog::Instance().saveConfigs();

    return EXIT_SUCCESS;
}
