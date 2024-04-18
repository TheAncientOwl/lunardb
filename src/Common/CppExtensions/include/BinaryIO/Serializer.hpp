#pragma once

#include "Common/CppExtensions/BinaryIO/Common.hpp"

#define SERIALIZE_IMPL(type) \
    template <>              \
    void serializeImpl(std::ostream& os, type const& obj);

namespace LunarDB::Common::CppExtensions::BinaryIO::Serializer {

template <typename T>
void serializeImpl(std::ostream& os, T const& obj) = delete;

PROVIDE_IMPL_FOR(SERIALIZE_IMPL);

template <std::size_t Index, typename... Args>
void serializeTupleElements(std::tuple<Args...> const&);

template <typename T>
concept HasSerializeImpl = requires(std::ostream& os, T obj) {
    { serializeImpl<T>(os, obj) } -> std::same_as<void>;
};

template <typename T>
    requires HasSerializeImpl<T> || Common::HasMakeTuple<T>
void serialize(std::ostream& os, T const& obj)
{
    if constexpr (Common::HasMakeTuple<T>)
    {
        serializeTupleElements<0>(obj.make_tuple());
    }
    else
    {
        serializeImpl(os, obj);
    }
}

template <std::size_t Index, typename... Args>
void serializeTupleElements(std::tuple<Args...> const& tuple)
{
    if constexpr (Index < sizeof...(Args))
    {
        serialize(std::get<Index>(tuple));
        serializeTupleElements<Index + 1>(tuple);
    }
}

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Serializer
