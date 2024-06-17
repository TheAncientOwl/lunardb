#pragma once

#include "LunarDB/Common/CppExtensions/FlatMap.hpp"

namespace LunarDB::Common::CppExtensions::DataStructures {

template <Concepts::Item Data, std::size_t Size>
template <typename... Args>
FlatMap<Data, Size>::FlatMap(Args&&... args) : m_data{std::forward<Args>(args)...}
{
}

template <Concepts::Item Data, std::size_t Size>
template <typename Callable>
std::optional<typename Data::second_type> FlatMap<Data, Size>::find_if(Callable&& callable) const
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

} // namespace LunarDB::Common::CppExtensions::DataStructures
