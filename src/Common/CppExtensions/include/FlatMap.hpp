#pragma once

#include <algorithm>
#include <array>
#include <functional>
#include <optional>

#include "LunarDB/Common/CppExtensions/Concepts/Item.hpp"

namespace LunarDB::Common::CppExtensions::DataStructures {

///
/// @brief Provide an array<Data, Size> with utility find method.
/// @tparam Data Items type
/// @tparam Size Number of elements
///
template <Concepts::Item Data, std::size_t Size>
class FlatMap
{
public: // methods
    ///
    /// @brief Self explanatory.
    ///
    template <typename... Args>
    FlatMap(Args&&... args);

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

} // namespace LunarDB::Common::CppExtensions::DataStructures

#include "LunarDB/Common/CppExtensions/private/FlatMap.inl"
