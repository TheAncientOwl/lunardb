#include <algorithm>

#include "CppExtensions/include/Errors.hpp"
#include "CppExtensions/include/StringUtils.hpp"
#include "Utils.hpp"

namespace LunarDB::Moonlight::Utils {

using namespace CppExtensions;

std::string_view extractWord(std::string_view& str, char sep, ESplitModifier modifier)
{
    std::string_view out{};

    bool quoted_string{ false };
    const auto c_end{ std::cend(str) };
    const auto c_begin{ std::cbegin(str) };

    auto word_begin{ c_begin };
    auto word_end{ c_begin };

    while (word_end != c_end)
    {
        const auto current_char{ *word_end };
        const auto prev_char{ word_end != c_begin ? *std::prev(word_end) : ' ' };

        if (modifier == ESplitModifier::EscapeQuotes && current_char == '"' && prev_char != '\\')
        {
            quoted_string = !quoted_string;
        }
        else if (current_char == sep && !quoted_string)
        {
            std::string_view word{ word_begin, word_end };

            str.remove_prefix(word.length());
            StringUtils::ltrim(str);

            StringUtils::trim(word);

            if (modifier == ESplitModifier::EscapeQuotes && word.length() > 1 &&
                word.starts_with('"') && word.ends_with('"'))
            {
                word.remove_prefix(1);
                word.remove_suffix(1);
            }

            out = word;
            break;
        }

        word_end = std::next(word_end);
    }

    if (out.empty())
    {
        if (!str.empty() && str.starts_with(','))
        {
            str.remove_prefix(1);
            StringUtils::ltrim(str);
        }

        out = str;
        StringUtils::trim(out);

        if (modifier == ESplitModifier::EscapeQuotes && out.length() > 1 &&
            out.starts_with('"') && out.ends_with('"'))
        {
            out.remove_prefix(1);
            out.remove_suffix(1);
        }

        str.remove_prefix(str.length());
        StringUtils::ltrim(str);
    }

    return out;
}

std::vector<std::string_view> split(std::string_view str, char sep, ESplitModifier modifier)
{
    std::vector<std::string_view> out{};

    StringUtils::trim(str);
    if (str.empty())
    {
        return out;
    }

    std::string_view word{};
    do
    {
        word = extractWord(str, sep, modifier);
        out.push_back(word);

        if (!str.empty() && str.front() == sep)
        {
            str.remove_prefix(1);
            StringUtils::ltrim(str);
        }
    } while (!str.empty() && !word.empty());

    return out;
}

namespace ExtractBinaryOperators {

std::string_view Equals(std::string_view& str)
{
    return extractWord(str, ' ', ESplitModifier::EscapeQuotes);
}

std::string_view GreaterThan(std::string_view& str)
{
    return extractWord(str, ' ', ESplitModifier::EscapeQuotes);
}

std::string_view GreaterThanEqualTo(std::string_view& str)
{
    return extractWord(str, ' ', ESplitModifier::EscapeQuotes);
}

std::string_view LessThan(std::string_view& str)
{
    return extractWord(str, ' ', ESplitModifier::EscapeQuotes);
}

std::string_view LessThanEqualTo(std::string_view& str)
{
    return extractWord(str, ' ', ESplitModifier::EscapeQuotes);
}

std::string_view In(std::string_view& str)
{
    std::string_view out{};

    const auto open_square_bracked_pos = str.find_first_of('[');
    const auto closed_square_bracked_pos = str.find_first_of(']');

    // TODO: provide adaptation for quoted strings

    if (open_square_bracked_pos == std::string_view::npos) { throw Errors::buildMissingError("'[' @ in operator list"); }
    if (closed_square_bracked_pos == std::string_view::npos) { throw Errors::buildMissingError("']' @ in operator list"); }
    if (open_square_bracked_pos > closed_square_bracked_pos) { throw Errors::buildError("Invalid where clause content"); }

    out = str.substr(0, closed_square_bracked_pos + 1);
    str.remove_prefix(closed_square_bracked_pos + 1);

    StringUtils::trim(out);
    StringUtils::ltrim(str);

    return out;
}

std::string_view Between(std::string_view& str)
{
    std::string_view original{ str };

    std::string_view out{};

    auto num1 = extractWord(str, ' ', ESplitModifier::None);

    auto and_ = extractWord(str, ' ', ESplitModifier::None);
    StringUtils::trim(and_);
    Errors::assertKeywordEquals(and_, "and");

    auto num2 = extractWord(str, ' ', ESplitModifier::None);

    out = original.substr(0, original.length() - str.length());

    StringUtils::ltrim(str);
    StringUtils::trim(out);

    return out;
}

std::string_view Like(std::string_view& str)
{
    return extractWord(str, ' ', ESplitModifier::EscapeQuotes);
}

} // namespace ExtractBinaryOperators

QueryData::WhereClause::BooleanExpression recursiveParseBooleanExpression(std::string_view& str)
{
    QueryData::WhereClause::BooleanExpression out{};

    if (str.starts_with('!'))
    {
        out.negated = true;
        str.remove_prefix(1);
        StringUtils::ltrim(str);
    }
    else
    {
        out.negated = false;
    }

    if (str.empty()) { throw Errors::buildMissingError("part of where clause @ '", str, "'"); }
    if (!str.starts_with('(')) { throw Errors::buildMissingError("'(' @ '", str, "'"); }

    str.remove_prefix(1);
    StringUtils::ltrim(str);

    if (str.empty()) { throw Errors::buildMissingError("part of where clause @ '", str, "'"); }

    while (!str.empty())
    {
        if (str.starts_with(')'))
        {
            str.remove_prefix(1);
            StringUtils::ltrim(str);
            break;
        }

        if (str.starts_with('!') || str.starts_with('('))
        {
            out.data.push_back(recursiveParseBooleanExpression(str));
            continue;
        }

        const auto word = extractWord(str, ' ', ESplitModifier::EscapeQuotes);

        try
        {
            auto operator_ = QueryData::Primitives::BooleanOperator::toLiteral(word);
            out.data.push_back(operator_);
            continue;
        }
        catch (const Errors::LunarError& err)
        {
            QueryData::WhereClause::BinaryExpression expression{};

            expression.lhs = word;
            expression.operation = QueryData::Primitives::BinaryOperator::toLiteral(extractWord(str, ' ', ESplitModifier::None));

            switch (expression.operation)
            {
            case QueryData::Primitives::EBinaryOperator::Equals: { expression.rhs = ExtractBinaryOperators::Equals(str); break; }
            case QueryData::Primitives::EBinaryOperator::GreaterThan: { expression.rhs = ExtractBinaryOperators::GreaterThan(str); break; }
            case QueryData::Primitives::EBinaryOperator::GreaterThanEqualTo: { expression.rhs = ExtractBinaryOperators::GreaterThanEqualTo(str); break; }
            case QueryData::Primitives::EBinaryOperator::LessThan: { expression.rhs = ExtractBinaryOperators::LessThan(str); break; }
            case QueryData::Primitives::EBinaryOperator::LessThanEqualTo: { expression.rhs = ExtractBinaryOperators::LessThanEqualTo(str); break; }
            case QueryData::Primitives::EBinaryOperator::In: { expression.rhs = ExtractBinaryOperators::In(str); break; }
            case QueryData::Primitives::EBinaryOperator::Between: { expression.rhs = ExtractBinaryOperators::Between(str); break; }
            case QueryData::Primitives::EBinaryOperator::Like: { expression.rhs = ExtractBinaryOperators::Like(str); break; }
            default: { throw Errors::buildError("Operator not implemented, please contact developer"); break; }
            }

            out.data.push_back(std::move(expression));
        }
    }

    return out;
}

QueryData::WhereClause extractWhereClause(std::string_view& str)
{
    QueryData::WhereClause out{};

    StringUtils::ltrim(str);
    const auto where = extractWord(str, ' ');
    Errors::assertKeywordEquals(where, "where");
    if (str.empty()) { throw Errors::buildMissingError("where clause content"); }

    out.expression = recursiveParseBooleanExpression(str);

    return out;
}

std::pair<std::string_view, std::string_view> parseResolutionOperator(std::string_view str)
{
    const auto first_sep_pos{ str.find_first_of(':') };
    const auto last_sep_pos{ str.find_last_of(':') };

    if (first_sep_pos == std::string_view::npos || last_sep_pos == std::string_view::npos ||
        first_sep_pos == last_sep_pos)
    {
        throw Errors::buildMissingError("':' symbol in resolution operator");
    }

    if (last_sep_pos - first_sep_pos > 1)
    {
        throw Errors::buildUnknownSequenceError(str.substr(last_sep_pos, first_sep_pos - last_sep_pos + 1));
    }

    return std::make_pair(str.substr(0, first_sep_pos), str.substr(last_sep_pos + 1, str.length() - last_sep_pos));
}

} // namespace LunarDB::Moonlight::Utils
