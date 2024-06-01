#include <ranges>
#include <string>
#include <variant>

#include "LunarDB/Selenity/Managers/Collections/EvaluateWhereClause.hpp"

using namespace std::string_literals;

namespace LunarDB::Selenity::API::Managers::Collections::WhereClause {

namespace {

using FieldData = std::variant<std::string, bool, int, float>;

FieldData convert(std::string const& value, Configurations::EFieldDataType to_type)
{
    switch (to_type)
    {
    case Configurations::EFieldDataType::Rid:
    case Configurations::EFieldDataType::String:
    case Configurations::EFieldDataType::DateTime:
        return value;
    case Configurations::EFieldDataType::Boolean:
        if (value == "true")
        {
            return true;
        }
        else if (value == "false")
        {
            return false;
        }
        assert(false && "Trying to convert unknown boolean value");
    case Configurations::EFieldDataType::Integer:
        try
        {
            return std::stoi(value);
        }
        catch (std::invalid_argument const& e)
        {
            throw std::runtime_error("Cannot convert '"s + value + "' to Integer; " + e.what());
        }
        catch (std::out_of_range const& e)
        {
            throw std::runtime_error("Value '"s + value + "' out of Integer range; " + e.what());
        }
    case Configurations::EFieldDataType::Float:
        try
        {
            return std::stof(value);
        }
        catch (std::invalid_argument const& e)
        {
            throw std::runtime_error("Cannot convert '"s + value + "' to Float; " + e.what());
        }
        catch (std::out_of_range const& e)
        {
            throw std::runtime_error("Value '"s + value + "' out of Float range; " + e.what());
        }
    case Configurations::EFieldDataType::None:
    default:
        assert(false && "Trying to convert not supported field data type");
        break;
    }
}

std::pair<FieldData, FieldData> getLhsRhs(
    nlohmann::json const& json,
    Configurations::CollectionConfiguration::Schema const& schema,
    Common::QueryData::WhereClause::BinaryExpression const& binary_expression)
{
    auto const json_end{json.end()};
    auto const contains_lhs = json.contains(binary_expression.lhs);
    auto const contains_rhs = json.contains(binary_expression.rhs);

    auto const get_type_and_value_from = [&schema](auto const& key, auto const& json) {
        return std::make_pair(schema.getField(key)->type, json[key]);
    };

    // salary == salary
    if (contains_lhs && contains_rhs)
    {
        auto const& [lhs_type, lhs_value] = get_type_and_value_from(binary_expression.lhs, json);
        auto const& [rhs_type, rhs_value] = get_type_and_value_from(binary_expression.rhs, json);

        return {convert(lhs_value, lhs_type), convert(rhs_value, rhs_type)};
    }
    // salary == 5000
    else if (contains_lhs)
    {
        auto const& [lhs_type, lhs_value] = get_type_and_value_from(binary_expression.lhs, json);
        return {convert(lhs_value, lhs_type), convert(binary_expression.rhs, lhs_type)};
    }
    // 5000 == salary
    else if (contains_rhs)
    {
        auto const& [rhs_type, rhs_value] = get_type_and_value_from(binary_expression.rhs, json);
        return {convert(binary_expression.lhs, rhs_type), convert(binary_expression.rhs, rhs_type)};
    }

    // 5000 == 5000
    return {binary_expression.lhs, binary_expression.rhs};
}

bool evaluateBinaryExpression(
    nlohmann::json const& json_entry,
    Configurations::CollectionConfiguration::Schema const& schema,
    Common::QueryData::WhereClause::BinaryExpression const& binary_expression)
{
    auto const [lhs, rhs] = getLhsRhs(json_entry, schema, binary_expression);

    switch (binary_expression.operation)
    {
    case Common::QueryData::Primitives::EBinaryOperator::Equals: {
        return lhs == rhs;
        break;
    }
    case Common::QueryData::Primitives::EBinaryOperator::GreaterThan: {
        return lhs > rhs;
        break;
    }
    case Common::QueryData::Primitives::EBinaryOperator::GreaterThanEqualTo: {
        return lhs >= rhs;
        break;
    }
    case Common::QueryData::Primitives::EBinaryOperator::LessThan: {
        return lhs < rhs;
        break;
    }
    case Common::QueryData::Primitives::EBinaryOperator::LessThanEqualTo: {
        return lhs <= rhs;
        break;
    }
    case Common::QueryData::Primitives::EBinaryOperator::In: {
        // TODO: Provide implementation
        throw std::runtime_error{
            "[~/lunardb/src/Selenity/src/Managers/Collections/"
            "EvaluateWhereClause.cpp:EBinaryOperator::In] Not implemented yet..."};
        break;
    }
    case Common::QueryData::Primitives::EBinaryOperator::Between: {
        // TODO: Provide implementation
        throw std::runtime_error{
            "[~/lunardb/src/Selenity/src/Managers/Collections/"
            "EvaluateWhereClause.cpp:EBinaryOperator::Between] Not implemented yet..."};
        break;
    }
    case Common::QueryData::Primitives::EBinaryOperator::Like: {
        // TODO: Provide implementation
        throw std::runtime_error{
            "[~/lunardb/src/Selenity/src/Managers/Collections/"
            "EvaluateWhereClause.cpp:EBinaryOperator::Like] Not implemented yet..."};
        break;
    }
    case Common::QueryData::Primitives::EBinaryOperator::None:
    default:
        break;
    }
    return true;
}

bool evaluateBooleanExpression(
    nlohmann::json const& json_entry,
    Configurations::CollectionConfiguration::Schema const& schema,
    Common::QueryData::WhereClause::BooleanExpression const& boolean_expression)
{
    auto const& data{boolean_expression.data};

    auto result{false};

    assert(!data.empty() && "Received empty where clause");

    using WhereClause = Common::QueryData::WhereClause;

    assert(
        (std::holds_alternative<WhereClause::BinaryExpression>(data[0]) ||
         std::holds_alternative<WhereClause::BooleanExpression>(data[0])) &&
        "Invalid Where clause beginning");

    if (std::holds_alternative<WhereClause::BinaryExpression>(data[0]))
    {
        result = evaluateBinaryExpression(
            json_entry, schema, std::get<WhereClause::BinaryExpression>(data[0]));
    }
    else
    {
        result = evaluateBooleanExpression(
            json_entry, schema, std::get<WhereClause::BooleanExpression>(data[0]));
    }

    for (std::size_t index = 2; index < data.size(); index += 3)
    {
        auto const& boolean_operator{data[index - 1]};
        auto const& expression{data[index]};

        assert(
            (std::holds_alternative<Common::QueryData::Primitives::EBooleanOperator>(boolean_operator)) &&
            "Invalid boolean operator found at some position in where clause");

        assert(
            (std::holds_alternative<WhereClause::BinaryExpression>(expression) ||
             std::holds_alternative<WhereClause::BooleanExpression>(expression)) &&
            "Invalid item found at some position in where clause for expression");

        bool boolean{false};
        if (std::holds_alternative<WhereClause::BinaryExpression>(expression))
        {
            boolean = evaluateBinaryExpression(
                json_entry, schema, std::get<WhereClause::BinaryExpression>(data[index]));
        }
        else
        {
            result = evaluateBooleanExpression(
                json_entry, schema, std::get<WhereClause::BooleanExpression>(data[index]));
        }

        switch (std::get<Common::QueryData::Primitives::EBooleanOperator>(boolean_operator))
        {
        case Common::QueryData::Primitives::EBooleanOperator::And:
            result = result && boolean;
            break;
        case Common::QueryData::Primitives::EBooleanOperator::Or:
            result = result || boolean;
            break;
        case Common::QueryData::Primitives::EBooleanOperator::None:
        default:
            assert(false && "Unknown boolean operator encountered");
            break;
        }
    }

    return result;
}

} // namespace

bool evaluate(
    std::unique_ptr<AbstractManager::ICollectionEntry> const& entry,
    Configurations::CollectionConfiguration::Schema const& schema,
    Common::QueryData::WhereClause const& where_clause)
{
    return evaluateBooleanExpression(entry->getJSON(), schema, where_clause.expression);
}

} // namespace LunarDB::Selenity::API::Managers::Collections::WhereClause
