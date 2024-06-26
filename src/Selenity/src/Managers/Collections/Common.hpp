#pragma once

#include <nlohmann/json.hpp>

#include "LunarDB/Common/QueryData/QueryData.hpp"
#include "LunarDB/Selenity/Managers/Configurations.hpp"

namespace LunarDB::Selenity::API::Managers::Collections {

void jsonify(
    LunarDB::Common::QueryData::Insert::Object const& in_obj,
    nlohmann::json& out_obj,
    Configurations::CollectionConfiguration::Schema const& collection_schema,
    bool permissive = false);

namespace Calculus {

std::uint8_t precedence(char operation);

template <typename T>
concept NumericType = requires() { std::is_same_v<T, int> || std::is_same_v<T, float>; };

template <NumericType Numeric>
Numeric applyOperation(Numeric lhs, Numeric rhs, char operation);

template <NumericType Numeric>
Numeric solveNumericExpression(std::string_view expression, std::string_view key, Numeric key_numeric);

} // namespace Calculus

} // namespace LunarDB::Selenity::API::Managers::Collections

#include "./private/Common.inl"
