#pragma once

#include "LunarDB/Common/CppExtensions/DynamicFlatMap.hpp"

namespace LunarDB::Common::CppExtensions::DataStructures {

template <Concepts::Item Data>
template <typename... Args>
DynamicFlatMap<Data>::DynamicFlatMap(Args&&... args) : m_data{std::forward<Args>(args)...}
{
}

template <Concepts::Item Data>
template <typename Callable>
std::optional<typename Data::second_type> DynamicFlatMap<Data>::find_if(Callable&& callable) const
{
    auto const it = std::find_if(std::cbegin(m_data), std::cend(m_data), callable);

    if (it == std::cend(m_data))
    {
        return std::nullopt;
    }
    else
    {
        return it->second;
    }
}

template <Concepts::Item Data>
template <typename... Args>
void DynamicFlatMap<Data>::emplace(Args&&... args)
{
    m_data.emplace_back(std::forward<Args>(args)...);
}

} // namespace LunarDB::Common::CppExtensions::DataStructures
