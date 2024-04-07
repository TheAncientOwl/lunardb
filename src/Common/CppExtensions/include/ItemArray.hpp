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
    ItemArray(Args&&... args);

    template<typename Callable>
    std::optional<typename Data::second_type> find_if(Callable&& callable) const;

private: // fields
    std::array<Data, Size> m_data;
};

} // namespace LunarDB::CppExtensions::DataStructures

#include "Common/CppExtensions/private/ItemArray.inl"
