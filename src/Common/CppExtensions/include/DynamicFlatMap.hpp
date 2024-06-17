#pragma once

#include <algorithm>
#include <functional>
#include <optional>
#include <vector>

#include "LunarDB/Common/CppExtensions/Concepts/Item.hpp"

namespace LunarDB::Common::CppExtensions::DataStructures {

///
/// @brief Provide an array<Data, Size> with utility find method.
/// @tparam Data Items type
/// @tparam Size Number of elements
///
template <Concepts::Item Data>
class DynamicFlatMap
{
public: // methods
    ///
    /// @brief Self explanatory.
    ///
    template <typename... Args>
    DynamicFlatMap(Args&&... args);

    ///
    /// @brief Self explanatory.
    /// @tparam Callable Any type that has operator(Data const&)
    /// @param callable Condition to check if desired item exists
    /// @return Data.second value if desired item is found, empty optional otherwise
    ///
    template <typename Callable>
    std::optional<typename Data::second_type> find_if(Callable&& callable) const;

    template <typename... Args>
    void emplace(Args&&... args);

private: // fields
    std::vector<Data> m_data;
};

} // namespace LunarDB::Common::CppExtensions::DataStructures

#include "LunarDB/Common/CppExtensions/private/DynamicFlatMap.inl"
