#include "Common.hpp"

namespace LunarDB::Selenity::API::Managers::Collections {

void jsonify(
    LunarDB::Common::QueryData::Insert::Object const& in_obj,
    nlohmann::json& out_obj,
    Configurations::CollectionConfiguration::Schema const& collection_schema,
    bool permissive)
{
    // TODO: Add new field when jsonifying collections.
    using Object = Common::QueryData::Insert::Object;

    for (auto const& [key, value] : in_obj.entries)
    {
        auto const& field_config = collection_schema.getField(key);

        if (std::holds_alternative<std::string>(value))
        {
            auto value_str = std::get<std::string>(value);

            switch (field_config->type)
            {
            case Configurations::EFieldDataType::String:
                break;
            case Configurations::EFieldDataType::DateTime:
                break;
            case Configurations::EFieldDataType::Boolean:
                if (!(LunarDB::Common::CppExtensions::StringUtils::equalsIgnoreCase(
                          value_str, "true") ||
                      LunarDB::Common::CppExtensions::StringUtils::equalsIgnoreCase(
                          value_str, "false")))
                {
                    throw std::runtime_error{LunarDB::Common::CppExtensions::StringUtils::stringify(
                        "Field",
                        std::string(key),
                        "should be boolean, found '",
                        value_str,
                        "' instead")};
                }
                break;
            case Configurations::EFieldDataType::Float:
                try
                {
                    std::ignore = std::stof(value_str);
                }
                catch (std::invalid_argument const& e)
                {
                    throw std::runtime_error{LunarDB::Common::CppExtensions::StringUtils::stringify(
                        "Cannot convert", value_str, "to Float", e.what())};
                }
                catch (std::out_of_range const& e)
                {
                    throw std::runtime_error{LunarDB::Common::CppExtensions::StringUtils::stringify(
                        "Value", value_str, "out of Float range", e.what())};
                }
                break;
            case Configurations::EFieldDataType::Integer:
                try
                {
                    std::ignore = std::stoi(value_str);
                }
                catch (std::invalid_argument const& e)
                {
                    throw std::runtime_error{LunarDB::Common::CppExtensions::StringUtils::stringify(
                        "Cannot convert", value_str, "to Integer", e.what())};
                }
                catch (std::out_of_range const& e)
                {
                    throw std::runtime_error{LunarDB::Common::CppExtensions::StringUtils::stringify(
                        "Value", value_str, "out of Integer range", e.what())};
                }
                break;
            case Configurations::EFieldDataType::Rid:
                [[fallthrough]];
            case Configurations::EFieldDataType::None:
                [[fallthrough]];
            default:
                throw std::runtime_error{LunarDB::Common::CppExtensions::StringUtils::stringify(
                    "Field",
                    std::string(key),
                    "should be",
                    Configurations::FieldDataType::toString(field_config->type),
                    "found object instead")};
                break;
            }

            out_obj[key] = std::move(value_str);
        }
        else if (std::holds_alternative<Object>(value))
        {
            if (field_config->type != Configurations::EFieldDataType::Rid)
            {
                throw std::runtime_error{LunarDB::Common::CppExtensions::StringUtils::stringify(
                    "Field", std::string(key), "is not an object")};
            }
            jsonify(std::get<Object>(value), out_obj[key], collection_schema);
        }
        else if (std::holds_alternative<std::vector<std::string>>(value))
        {
            if (!field_config->array)
            {
                throw std::runtime_error{LunarDB::Common::CppExtensions::StringUtils::stringify(
                    "Field", std::string(key), "is not an array")};
            }
            out_obj[key] = std::get<std::vector<std::string>>(value);
        }
        else if (std::holds_alternative<std::vector<Object>>(value))
        {
            if (!field_config->array)
            {
                throw std::runtime_error{LunarDB::Common::CppExtensions::StringUtils::stringify(
                    "Field", std::string(key), "is not an array")};
            }

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
