#pragma once

#include "Common/CppExtensions/BinaryIO/Deserializer.hpp"

#define DESERIALIZE_IMPL(type) \
    template <>                \
    void deserialize(std::istream& is, type& obj);

namespace LunarDB::Common::CppExtensions::BinaryIO::Deserializer {

template <typename T>
    requires Implementation::HasDeserializeImpl<T> || Common::IsTuple<T> || Common::HasMakeTuple<T>
void deserialize(std::istream& os, T& obj)
{
    if constexpr (Common::HasMakeTuple<T>)
    {
        auto tuple = obj.makeTuple();
        Implementation::deserializeTuple<0ul>(os, tuple);
    }
    else if constexpr (Common::IsTuple<T>)
    {
        Implementation::deserializeTuple<0ul>(os, obj);
    }
    else
    {
        Implementation::deserialize(os, obj);
    }
}

namespace Implementation {

PROVIDE_IMPL_FOR(DESERIALIZE_IMPL);

template <std::size_t Index, typename... Args>
void deserializeTuple(std::istream& os, std::tuple<Args...>& tuple)
{
    if constexpr (Index < sizeof...(Args))
    {
        deserialize(os, std::get<Index>(tuple));
        deserializeTuple<Index + 1>(os, tuple);
    }
}

} // namespace Implementation

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Deserializer
