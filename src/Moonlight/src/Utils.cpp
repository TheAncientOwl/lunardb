#include <algorithm>

#include "Errors.hpp"
#include "LunarDB/Common/CppExtensions/StringUtils.hpp"
#include "Utils.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_MOONLIGHT)

namespace LunarDB::Moonlight::Utils {

namespace CppExtensions = LunarDB::Common::CppExtensions;
namespace StringUtils = CppExtensions::StringUtils;

std::string_view extractWord(std::string_view& str, char sep, ESplitModifier modifier, bool raw_percent_percent)
{
    std::string_view out{};

    bool is_quoted_string{false};
    bool is_percent_percent{false};
    auto const c_end{std::cend(str)};
    auto const c_begin{std::cbegin(str)};

    auto word_begin{c_begin};
    auto word_end{c_begin};

    while (word_end != c_end)
    {
        auto const current_char{*word_end};
        auto const prev_char{word_end != c_begin ? *std::prev(word_end) : ' '};

        if (raw_percent_percent && current_char == '%' && prev_char == '%')
        {
            is_percent_percent = !is_percent_percent;
        }
        else if (modifier == ESplitModifier::EscapeQuotes && current_char == '"' && prev_char != '\\')
        {
            is_quoted_string = !is_quoted_string;
        }
        else if (current_char == sep && !(is_quoted_string || is_percent_percent))
        {
            std::string_view word{word_begin, word_end};

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

        if (modifier == ESplitModifier::EscapeQuotes && out.length() > 1 && out.starts_with('"') &&
            out.ends_with('"'))
        {
            out.remove_prefix(1);
            out.remove_suffix(1);
        }

        str.remove_prefix(str.length());
        StringUtils::ltrim(str);
    }

    return out;
}

std::vector<std::string_view> split(std::string_view str, char sep, ESplitModifier modifier, bool raw_percent_percent)
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
        word = extractWord(str, sep, modifier, raw_percent_percent);
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

    auto const open_square_bracked_pos = str.find_first_of('[');
    auto const closed_square_bracked_pos = str.find_first_of(']');

    // TODO: provide adaptation for quoted strings

    if (open_square_bracked_pos == std::string_view::npos)
    {
        throw Errors::buildMissingError("'[' @ in operator list");
    }
    if (closed_square_bracked_pos == std::string_view::npos)
    {
        throw Errors::buildMissingError("']' @ in operator list");
    }
    if (open_square_bracked_pos > closed_square_bracked_pos)
    {
        throw Errors::buildError("Invalid where clause content");
    }

    out = str.substr(0, closed_square_bracked_pos + 1);
    str.remove_prefix(closed_square_bracked_pos + 1);

    StringUtils::trim(out);
    StringUtils::ltrim(str);

    return out;
}

std::string_view Between(std::string_view& str)
{
    std::string_view original{str};

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

Common::QueryData::WhereClause::BooleanExpression recursiveParseBooleanExpression(std::string_view& str)
{
    Common::QueryData::WhereClause::BooleanExpression out{};

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

    if (str.empty())
    {
        throw Errors::buildMissingError("part of where clause @ '", str, "'");
    }
    if (!str.starts_with('('))
    {
        throw Errors::buildMissingError("'(' @ '", str, "'");
    }

    str.remove_prefix(1);
    StringUtils::ltrim(str);

    if (str.empty())
    {
        throw Errors::buildMissingError("part of where clause @ '", str, "'");
    }

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

        auto const word = extractWord(str, ' ', ESplitModifier::EscapeQuotes);

        try
        {
            auto operator_ = Common::QueryData::Primitives::BooleanOperator::toLiteral(word);
            out.data.push_back(operator_);
            continue;
        }
        catch (Errors::ParserError const& err)
        {
            Common::QueryData::WhereClause::BinaryExpression expression{};

            expression.lhs = word;
            expression.operation = Common::QueryData::Primitives::EBinaryOperator::Equals;
            expression.operation = Common::QueryData::Primitives::BinaryOperator::toLiteral(
                extractWord(str, ' ', ESplitModifier::None));

            switch (expression.operation)
            {
            case Common::QueryData::Primitives::EBinaryOperator::Equals: {
                expression.rhs = ExtractBinaryOperators::Equals(str);
                break;
            }
            case Common::QueryData::Primitives::EBinaryOperator::GreaterThan: {
                expression.rhs = ExtractBinaryOperators::GreaterThan(str);
                break;
            }
            case Common::QueryData::Primitives::EBinaryOperator::GreaterThanEqualTo: {
                expression.rhs = ExtractBinaryOperators::GreaterThanEqualTo(str);
                break;
            }
            case Common::QueryData::Primitives::EBinaryOperator::LessThan: {
                expression.rhs = ExtractBinaryOperators::LessThan(str);
                break;
            }
            case Common::QueryData::Primitives::EBinaryOperator::LessThanEqualTo: {
                expression.rhs = ExtractBinaryOperators::LessThanEqualTo(str);
                break;
            }
            case Common::QueryData::Primitives::EBinaryOperator::In: {
                expression.rhs = ExtractBinaryOperators::In(str);
                break;
            }
            case Common::QueryData::Primitives::EBinaryOperator::Between: {
                expression.rhs = ExtractBinaryOperators::Between(str);
                break;
            }
            case Common::QueryData::Primitives::EBinaryOperator::Like: {
                expression.rhs = ExtractBinaryOperators::Like(str);
                break;
            }
            default: {
                CLOG_WARN(
                    "Operator", static_cast<std::int64_t>(expression.operation), "not implemented");
                throw Errors::buildError("Operator not implemented, please contact developer");
                break;
            }
            }

            out.data.push_back(std::move(expression));
        }
    }

    return out;
}

Common::QueryData::WhereClause extractWhereClause(std::string_view& str)
{
    Common::QueryData::WhereClause out{};

    StringUtils::ltrim(str);
    auto const where = extractWord(str, ' ');
    Errors::assertKeywordEquals(where, "where");
    if (str.empty())
    {
        throw Errors::buildMissingError("where clause content");
    }

    out.expression = recursiveParseBooleanExpression(str);

    return out;
}

std::pair<std::string_view, std::string_view> parseResolutionOperator(std::string_view str)
{
    auto const first_sep_pos{str.find_first_of(':')};
    auto const last_sep_pos{str.find_last_of(':')};

    if (first_sep_pos == std::string_view::npos || last_sep_pos == std::string_view::npos ||
        first_sep_pos == last_sep_pos)
    {
        throw Errors::buildMissingError("':' symbol in resolution operator");
    }

    if (last_sep_pos - first_sep_pos > 1)
    {
        throw Errors::buildUnknownSequenceError(
            str.substr(last_sep_pos, first_sep_pos - last_sep_pos + 1));
    }

    return std::make_pair(
        str.substr(0, first_sep_pos), str.substr(last_sep_pos + 1, str.length() - last_sep_pos));
}

} // namespace LunarDB::Moonlight::Utils
