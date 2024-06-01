#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

#include "LunarDB/Astral/QueryExecutor.hpp"
#include "LunarDB/Common/CppExtensions/ConsoleColorOutput.hpp"
#include "LunarDB/Common/CppExtensions/StringUtils.hpp"
#include "LunarDB/Moonlight/QueryParser.hpp"
#include "LunarDB/Selenity/SchemasCatalog.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"

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

int main(int argc, char const* argv[])
{
    std::cout << ccolor::dark_gray << "[" << ccolor::purple << "LunarDB" << ccolor::dark_gray
              << "]: " << ccolor::green << "Version alpha.1.0_rc01" << ccolor::reset << std::endl;

    LunarDB::Selenity::API::SchemasCatalog::Instance().clearCache();
    LunarDB::Selenity::API::SystemCatalog::Instance().loadConfigs();

    std::string query{};
    std::string input_line{};
    bool prompt{true};
    bool is_schema{false};
    while (true)
    {
        if (prompt)
        {
            std::cout << ccolor::dark_red << "root" << ccolor::dark_gray << "@" << ccolor::purple
                      << "lunardb" << ccolor::green << "$ " << ccolor::black << std::flush;
        }
        prompt = false;
        std::getline(std::cin, input_line);
        std::transform(input_line.begin(), input_line.end(), input_line.begin(), [](char const c) {
            return std::tolower(c);
        });

        std::string_view input_line_sv{input_line};
        LunarDB::Common::CppExtensions::StringUtils::trim(input_line_sv);
        if (input_line_sv.starts_with("schema"))
        {
            is_schema = true;
        }

        if (is_schema && input_line_sv.find('}') != std::string_view::npos)
        {
            is_schema = false;
        }

        if (input_line_sv.back() != ';' || (input_line_sv.back() == ';' && is_schema))
        {
            query += '\n';
            query += input_line;
            continue;
        }
        query += '\n';
        query += input_line;

        try
        {
            auto const parsed_query = LunarDB::Moonlight::API::parseQuery(query);
            LunarDB::Astral::API::executeQuery(parsed_query);

            std::cout << ccolor::dark_gray << "[" << ccolor::green << "Ok" << ccolor::dark_gray
                      << "]: " << ccolor::lime << getSuccessMessage(parsed_query) << "."
                      << ccolor::reset << std::endl;
        }
        catch (std::exception const& e)
        {
            std::cout << ccolor::dark_gray << "[" << ccolor::dark_red << "Error" << ccolor::dark_gray
                      << "]: " << ccolor::light_red << e.what() << "." << ccolor::reset << std::endl;
        }

        query.clear();
        prompt = true;
    }

    LunarDB::Selenity::API::SystemCatalog::Instance().saveConfigs();

    return 0;
}
