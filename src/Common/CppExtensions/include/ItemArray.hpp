#pragma once

#include <algorithm>
#include <array>
#include <concepts>
#include <functional>
#include <optional>

namespace LunarDB::CppExtensions::DataStructures {

template <typename T>
concept Item = requires(T t)
{
    { t.first } -> std::convertible_to<typename T::first_type>;
    { t.second } -> std::convertible_to<typename T::second_type>;
};

template<Item Data, std::size_t Size>
class ItemArray
{
public: // methods
    template<typename... Args>
    ItemArray(Args&&... args)
        : m_data{ std::forward<Args>(args)... }
    {}

    std::optional<typename Data::second_type> find_if(const std::function<bool(const Data&)>& func) const
    {
        const auto it = std::find_if(std::cbegin(m_data), std::cend(m_data), func);

        if (it == std::cend(m_data))
        {
            return std::nullopt;
        }
        else
        {
            return it->second;
        }
    }

private: // fields
    std::array<Data, Size> m_data;
};

} // namespace LunarDB::CppExtensions::DataStructures
