#include "Common.hpp"

namespace LunarDB::Selenity::API::Managers::Collections {

void jsonify(
    LunarDB::Common::QueryData::Insert::Object const& in_obj,
    nlohmann::json& out_obj,
    Configurations::CollectionConfiguration::Schema const& collection_schema)
{
    // TODO: Check object structure with schema and add to schema where necessary
    using Object = Common::QueryData::Insert::Object;

    for (auto const& [key, value] : in_obj.entries)
    {
        if (std::holds_alternative<std::string>(value))
        {
            out_obj[key] = std::get<std::string>(value);
        }
        else if (std::holds_alternative<Object>(value))
        {
            jsonify(std::get<Object>(value), out_obj[key], collection_schema);
        }
        else if (std::holds_alternative<std::vector<std::string>>(value))
        {
            out_obj[key] = std::get<std::vector<std::string>>(value);
        }
        else if (std::holds_alternative<std::vector<Object>>(value))
        {
            nlohmann::json array = nlohmann::json::array();

            for (auto const& arr_object : std::get<std::vector<Object>>(value))
            {
                auto& arr_json_item = array.emplace_back();
                jsonify(arr_object, arr_json_item, collection_schema);
            }

            out_obj[key] = std::move(array);
        }
        else
        {
            // TODO: Log error
            assert(false && "Object writing failure, unknown variant alternative");
        }
    }
}

namespace Calculus {

std::uint8_t precedence(char operation)
{
    if (operation == '+' || operation == '-')
    {
        return 1;
    }
    if (operation == '*' || operation == '/')
    {
        return 2;
    }
    return 0;
}

} // namespace Calculus

} // namespace LunarDB::Selenity::API::Managers::Collections
