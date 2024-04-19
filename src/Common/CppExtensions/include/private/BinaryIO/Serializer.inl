#pragma once

#include "Common/CppExtensions/BinaryIO/Serializer.hpp"

#define SERIALIZE_IMPL(type) \
    template <>              \
    void serialize(std::ostream& os, type const& obj);

namespace LunarDB::Common::CppExtensions::BinaryIO::Serializer {

template <typename T>
    requires Implementation::HasSerializeImpl<T> || Common::IsTuple<T> || Common::HasMakeTuple<T>
void serialize(std::ostream& os, T const& obj)
{
    if constexpr (Common::HasMakeTuple<T>)
    {
        Implementation::serializeTuple<0ul>(os, obj.makeTuple());
    }
    else if constexpr (Common::IsTuple<T>)
    {
        Implementation::serializeTuple<0ul>(os, obj);
    }
    else
    {
        Implementation::serialize(os, obj);
    }
}

namespace Implementation {

PROVIDE_IMPL_FOR(SERIALIZE_IMPL);

template <std::size_t Index, typename... Args>
void serializeTuple(std::ostream& os, std::tuple<Args...> const& tuple)
{
    if constexpr (Index < sizeof...(Args))
    {
        serialize(os, std::get<Index>(tuple));
        serializeTuple<Index + 1>(os, tuple);
    }
}

} // namespace Implementation

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Serializer
