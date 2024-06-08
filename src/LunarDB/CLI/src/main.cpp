#include <algorithm>
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <nlohmann/json.hpp>
#include <ranges>
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

auto const on_success = [](auto message) {
    std::cout << ccolor::dark_gray << "[" << ccolor::green << "Success" << ccolor::dark_gray << "] "
              << ccolor::lime << message << ccolor::reset << std::endl;
};

auto const on_selection = [](auto selection, auto fields) {
    std::cout << ccolor::dark_gray << "[" << ccolor::purple << "Selection" << ccolor::dark_gray
              << "] " << ccolor::pink << std::endl;

    nlohmann::json json{nlohmann::json::parse(selection)};
    auto& jsonArray{json[0]["selection"]};

    if (!jsonArray.is_array())
    {
        assert(false && "Received invalid JSON array");
    }

    // Determine column widths
    std::vector<size_t> column_widths{};
    column_widths.reserve(fields.size());
    for (auto const& field : fields)
    {
        column_widths.push_back(field.length());
    }

    // Update column widths based on the content in the JSON array
    for (auto const& obj : jsonArray)
    {
        for (auto const index : std::ranges::iota_view{0u, fields.size()})
        {
            if (obj.contains(fields[index]))
            {
                column_widths[index] =
                    std::max(column_widths[index], obj[fields[index]].dump().size());
            }
        }
    }

    // Print the header
    std::cout << "|";
    for (auto const index : std::ranges::iota_view{0u, fields.size()})
    {
        std::cout << std::setw(column_widths[index]) << fields[index] << " | ";
    }
    std::cout << '\n';

    // Print a separator line
    std::cout << "|";
    for (auto const index : std::ranges::iota_view{0u, fields.size()})
    {
        for (auto const _ : std::ranges::iota_view{0u, column_widths[index] + (index == 0 ? 1 : 2)})
        {
            std::cout << "-";
        }
        std::cout << "|";
    }
    std::cout << '\n';

    // Print each row
    for (auto const& obj : jsonArray)
    {
        std::cout << "|";
        for (auto const index : std::ranges::iota_view{0u, fields.size()})
        {
            if (obj.contains(fields[index]))
            {
                auto const value{obj[fields[index]].dump()};
                std::string_view value_sv{value};
                value_sv.remove_prefix(1);
                value_sv.remove_suffix(1);
                std::cout << std::setw(column_widths[index]) << value_sv << " | ";
            }
            else
            {
                std::cout << std::setw(column_widths[index]) << " " << " | ";
            }
        }
        std::cout << '\n';
    }

    std::cout << std::flush;
};

auto const on_error = [](auto error) {
    std::cout << ccolor::dark_gray << "[" << ccolor::dark_red << "Error" << ccolor::dark_gray
              << "] " << ccolor::light_red << error << ccolor::reset << std::endl;
};

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
        std::string_view query_sv{query};
        LunarDB::Common::CppExtensions::StringUtils::ltrim(query_sv);
        if (query_sv.empty())
        {
            continue;
        }

        if (input_stream_ptr == &input_file)
        {
            std::cout << query << std::endl;
        }

        LunarDB::Common::QueryHandlingUtils::handleQuery(
            query, lunar_logger_module, on_success, on_selection, on_error);
    } while (!prompt.done());

    std::cout << std::endl;

    LunarDB::Selenity::API::SystemCatalog::Instance().saveConfigs();

    return EXIT_SUCCESS;
}
