#pragma once

#include <algorithm>
#include <array>
#include <concepts>
#include <functional>
#include <optional>

namespace LunarDB::CppExtensions::DataStructures {

///
/// @brief Enforces .first and .second members on a type.
///
template <typename T>
concept Item = requires(T t) {
    { t.first } -> std::convertible_to<typename T::first_type>;
    { t.second } -> std::convertible_to<typename T::second_type>;
};

///
/// @brief Provide an array<Data, Size> with utility find method.
/// @tparam Data Items type
/// @tparam Size Number of elements
///
template <Item Data, std::size_t Size>
class ItemArray
{
public: // methods
    ///
    /// @brief Self explanatory.
    ///
    template <typename... Args>
    ItemArray(Args&&... args);

    ///
    /// @brief Self explanatory.
    /// @tparam Callable Any type that has operator(Data const&)
    /// @param callable Condition to check if desired item exists
    /// @return Data.second value if desired item is found, empty optional otherwise
    ///
    template <typename Callable>
    std::optional<typename Data::second_type> find_if(Callable&& callable) const;

private: // fields
    std::array<Data, Size> m_data;
};

} // namespace LunarDB::CppExtensions::DataStructures

#include "Common/CppExtensions/private/ItemArray.inl"
