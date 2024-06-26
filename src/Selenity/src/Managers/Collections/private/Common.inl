#pragma once

#include "../Common.hpp"

#include <nlohmann/json.hpp>

#include "LunarDB/Common/QueryData/QueryData.hpp"
#include "LunarDB/Moonlight/QueryExtractor.hpp"
#include "LunarDB/Selenity/Managers/Configurations.hpp"

#include <stack>

namespace LunarDB::Selenity::API::Managers::Collections {

namespace Calculus {

template <NumericType Numeric>
Numeric applyOperation(Numeric lhs, Numeric rhs, char operation)
{
    using namespace std::string_literals;

    switch (operation)
    {
    case '+':
        return lhs + rhs;
    case '-':
        return lhs - rhs;
    case '*':
        return lhs * rhs;
    case '/':
        if (rhs == 0)
        {
            throw std::runtime_error("Divison by 0");
        }
        return lhs / rhs;
    case '%':
        if constexpr (std::is_same_v<Numeric, int>)
        {
            return lhs % rhs;
        }
        else
        {
            return std::fmod(lhs, rhs);
        }
        break;
    default:
        throw std::runtime_error("Invalid operation '"s + operation + "'");
    }
}

template <NumericType Numeric>
Numeric solveNumericExpression(std::string_view expression, std::string_view key, Numeric key_numeric)
{
    using namespace std::string_view_literals;
    using namespace std::string_literals;

    Moonlight::Implementation::QueryExtractor extractor{expression};
    assert(!extractor.empty() && "Invalid update expression");

    std::stack<Numeric> values{};
    std::stack<char> operations{};

    while (!extractor.empty())
    {
        auto const token = extractor.extractOne();

        // Current token is an opening brace, push to operators stack
        if (token.length() == 1 && token.front() == '(')
        {
            operations.push('(');
        }
        // Current token is the field that will be modified, push its numeric value to the stack
        else if (token == key)
        {
            values.push(key_numeric);
        }
        // Current token is numeric, push to stack
        else if (std::all_of(token.begin(), token.end(), [](char const c) { return std::isdigit(c); }))
        {
            if constexpr (std::is_same_v<Numeric, int>)
            {
                values.push(std::stoi(std::string(token)));
            }
            else
            {
                values.push(std::stof(std::string(token)));
            }
        }
        // Current token is a closing brace, solve entire brace
        else if (token.length() == 1 && token.front() == ')')
        {
            while (!operations.emplace() && operations.top() != '(')
            {
                auto const value2{values.top()};
                values.pop();

                auto const value1{values.top()};
                values.pop();

                auto const operation{operations.top()};
                operations.pop();

                values.push(applyOperation(value1, value2, operation));
            }

            // Pop opening brace
            if (!operations.empty())
            {
                operations.pop();
            }
        }
        // Current token is an operator
        // TODO: enforce it to be an operator
        else if (token.length() == 1)
        {
            // While top of 'operations' has same or greater precedence to current token, which is
            // an operator, apply operator on top of 'operations' to top two elements in values stack
            while (!operations.empty() && precedence(operations.top()) >= precedence(token.front()))
            {
                auto const value2{values.top()};
                values.pop();

                auto const value1{values.top()};
                values.pop();

                auto const operation{operations.top()};
                operations.pop();

                values.push(applyOperation(value1, value2, operation));
            }

            operations.push(token.front());
        }
    }

    // Entire expression has been parsed, apply remaining operations to remaining values
    while (!operations.empty())
    {
        auto const value2{values.top()};
        values.pop();

        auto const value1{values.top()};
        values.pop();

        auto const operation(operations.top());
        operations.pop();

        values.push(applyOperation(value1, value2, operation));
    }

    return values.top();
}

} // namespace Calculus

} // namespace LunarDB::Selenity::API::Managers::Collections
