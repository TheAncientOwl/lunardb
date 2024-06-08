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

int main(int argc, char const* argv[])
{
    std::cout << ccolor::dark_gray << "[" << ccolor::purple << "LunarDB" << ccolor::dark_gray
              << "]: " << ccolor::green << "Version alpha.1.0_rc01" << ccolor::reset << std::endl;

    LunarDB::Selenity::API::SchemasCatalog::Instance().clearCache();
    LunarDB::Selenity::API::SystemCatalog::Instance().loadConfigs();

    while (true)
    {
        std::cout << ccolor::dark_red << "root" << ccolor::dark_gray << "@" << ccolor::purple
                  << "lunardb" << ccolor::dark_gray << "$ " << ccolor::light_gray;
        auto const query = LunarDB::CLI::readQuery();

        LunarDB::Common::QueryHandlingUtils::handleQuery(
            query, lunar_logger_module, [](std::string const& message) {
                std::cout << message << std::endl;
            });
    }

    LunarDB::Selenity::API::SystemCatalog::Instance().saveConfigs();

    return EXIT_SUCCESS;
}
