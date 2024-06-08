#include <algorithm>
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
              << ccolor::lime << message << std::endl;
}

void writeSelection(std::string const& selection)
{
    std::cout << ccolor::dark_gray << "[" << ccolor::purple << "Selection" << ccolor::dark_gray
              << "] " << ccolor::pink << selection << std::endl;
}

void writeError(std::string const& error)
{
    std::cout << ccolor::dark_gray << "[" << ccolor::dark_red << "Error" << ccolor::dark_gray
              << "] " << ccolor::light_red << error << std::endl;
}

int main(int argc, char const* argv[])
{
    std::cout << ccolor::dark_gray << "[" << ccolor::purple << "LunarDB" << ccolor::dark_gray
              << "]: " << ccolor::green << "Version alpha.1.0_rc01" << ccolor::reset << std::endl;

    LunarDB::Selenity::API::SchemasCatalog::Instance().clearCache();
    LunarDB::Selenity::API::SystemCatalog::Instance().loadConfigs();

    LunarDB::CLI::QueryPrompt prompt{std::cin};

    while (true)
    {
        std::cout << ccolor::dark_red << "root" << ccolor::dark_gray << "@" << ccolor::purple
                  << "lunardb" << ccolor::dark_gray << "$ " << ccolor::light_gray;

        auto const query = prompt.readQuery();

        auto message_writer = [](std::string const& message) { std::cout << message << std::endl; };

        LunarDB::Common::QueryHandlingUtils::handleQuery(
            query, lunar_logger_module, writeMessage, writeSelection, writeError);
    }

    LunarDB::Selenity::API::SystemCatalog::Instance().saveConfigs();

    return EXIT_SUCCESS;
}
