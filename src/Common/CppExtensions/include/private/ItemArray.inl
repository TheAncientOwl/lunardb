#pragma once

#include "LunarDB/Common/CppExtensions/ItemArray.hpp"

namespace LunarDB::Common::CppExtensions::DataStructures {

template <Item Data, std::size_t Size>
template <typename... Args>
ItemArray<Data, Size>::ItemArray(Args&&... args) : m_data{std::forward<Args>(args)...}
{
}

template <Item Data, std::size_t Size>
template <typename Callable>
std::optional<typename Data::second_type> ItemArray<Data, Size>::find_if(Callable&& callable) const
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
