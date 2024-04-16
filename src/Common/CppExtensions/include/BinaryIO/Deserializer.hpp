#pragma once

#include "Common/CppExtensions/BinaryIO/Common.hpp"

#define PROVIDE_DESERIALIZE(type) \
template<> void deserializeImpl(std::istream& is, type& obj);

namespace LunarDB::Common::CppExtensions::BinaryIO::Deserializer {

template <typename T>
void deserializeImpl(std::istream& is, T& obj) = delete;

PROVIDE_IMPL_FOR(PROVIDE_DESERIALIZE);

template <std::size_t Index, typename... Args>
void deserializeTupleElements(std::tuple<Args...>&);

template <typename T>
concept HasDeserializeImpl = requires(std::istream & is, T obj)
{
    { deserializeImpl<T>(is, obj) } -> std::same_as<void>;
};

template <typename T>
    requires HasDeserializeImpl<T> || Common::HasMakeTuple<T>
void deserialize(std::istream & is, T & obj)
{
    if constexpr (Common::HasMakeTuple<T>)
    {
        deserializeTupleElements<0>(obj.make_tuple());
    }
    else
    {
        deserializeImpl(is, obj);
    }
}

template <std::size_t Index, typename... Args>
void deserializeTupleElements(std::tuple<Args...>& tuple)
{
    if constexpr (Index < sizeof...(Args))
    {
        deserialize(std::get<Index>(tuple));
        deserializeTupleElements<Index + 1>(tuple);
    }
}

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Deserializer
