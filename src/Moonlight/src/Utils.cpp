#include "Utils.hpp"

#include <algorithm>

namespace LunarDB::Moonlight::Utils {

void ltrim(std::string_view& str)
{
    if (!str.empty())
    {
        const auto begin{ str.find_first_not_of(c_whitespace) };

        str = str.substr(std::min(begin, str.length()));
    }
}

void rtrim(std::string_view& str)
{
    if (!str.empty())
    {
        const auto end{ str.find_last_not_of(c_whitespace) };

        str = str.substr(0, end + 1);
    }
}

void trim(std::string_view& str)
{
    ltrim(str);
    rtrim(str);
}

bool equalsIgnoreCase(std::string_view s1, std::string_view s2)
{
    if (s1.length() != s2.length())
    {
        return false;
    }

    for (std::size_t i = 0, length = s1.length(); i < length; i++)
    {
        if (toupper(s1[i]) != toupper(s2[i]))
        {
            return false;
        }
    }

    return true;
}

bool startsWithIgnoreCase(std::string_view src, std::string_view what)
{
    if (what.length() > src.length())
    {
        return false;
    }

    return equalsIgnoreCase(src.substr(0, what.length()), what);
}

std::vector<std::string_view> splitAtComma(std::string_view str, ESplitModifier modifier)
{
    std::vector<std::string_view> out{};

    trim(str);
    if (str.empty())
    {
        return out;
    }

    bool quoted_string{ false };
    const auto c_end{ std::cend(str) };
    const auto c_begin{ std::cbegin(str) };

    auto word_begin{ c_begin };
    auto word_end{ c_begin };

    const auto update_output = [&out, modifier](const char* word_begin, const char* word_end) {
        std::string_view word{ word_begin, static_cast<std::string_view::size_type>(std::distance(word_begin, word_end)) };
        trim(word);

        if (modifier == ESplitModifier::EscapeQuotes && word.length() > 1 &&
            word.starts_with('"') && word.ends_with('"'))
        {
            word.remove_prefix(1);
            word.remove_suffix(1);
        }

        if (!word.empty())
        {
            out.push_back(word);
        }
        };

    while (word_end != c_end)
    {
        const auto current_char{ *word_end };
        const auto prev_char{ word_end != c_begin ? *std::prev(word_end) : ' ' };

        if (modifier == ESplitModifier::EscapeQuotes && current_char == '"' && prev_char != '\\')
        {
            quoted_string = !quoted_string;
        }
        else if (current_char == ',' && !quoted_string)
        {
            quoted_string = false;

            update_output(word_begin, word_end);

            word_begin = std::next(word_end);
        }

        word_end = std::next(word_end);
    }

    if (word_begin != word_end)
    {
        update_output(word_begin, word_end);
    }

    return out;
}

QueryData::WhereClause parseWhereClause(std::string_view where)
{
    QueryData::WhereClause out{};

    // TODO: Provide implementation

    return out;
}

} // namespace LunarDB::Moonlight::Utils
