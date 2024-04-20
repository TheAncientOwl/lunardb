#pragma once

#include "Common/CppExtensions/BinaryIO/Serializer.hpp"

#define INTERNAL_SERIALIZE(type) \
    template <>                  \
    void serialize(std::ostream& os, type const& obj);

namespace LunarDB::Common::CppExtensions::BinaryIO::Serializer {

namespace Internal {

PROVIDE_IMPL_FOR(INTERNAL_SERIALIZE);

template <typename T>
    requires Common::Concepts::Enum<T>
void serializeEnum(std::ostream& os, T const& obj)
{
    os.write(reinterpret_cast<const char*>(&obj), sizeof(decltype(obj)));
}

template <typename First, typename Second>
void serializePair(std::ostream& os, std::pair<First, Second> const& pair)
{
    Serializer::serialize(os, pair.first);
    Serializer::serialize(os, pair.second);
}

template <std::size_t Index, typename... Args>
void serializeTuple(std::ostream& os, std::tuple<Args...> const& tuple)
{
    if constexpr (Index < sizeof...(Args))
    {
        Serializer::serialize(os, std::get<Index>(tuple));
        Internal::serializeTuple<Index + 1>(os, tuple);
    }
}

template <typename T>
    requires Common::Concepts::Container<T>
void serializeContainer(std::ostream& os, T const& container)
{
    auto const size{std::size(container)};
    os.write(reinterpret_cast<const char*>(&size), sizeof(decltype(size)));

    for (auto const& element : container)
    {
        Serializer::serialize(os, element);
    }
}

} // namespace Internal

template <typename T>
    requires Serializer::Serializable<T>
void serialize(std::ostream& os, T const& obj)
{
    if constexpr (Common::Concepts::Pair<T>)
    {
        Internal::serializePair(os, obj);
    }
    else if constexpr (Common::Concepts::Tupleable<T>)
    {
        Internal::serializeTuple<0>(os, obj.makeTuple());
    }
    else if constexpr (Common::Concepts::Tuple<T>)
    {
        Internal::serializeTuple<0>(os, obj);
    }
    else if constexpr (Common::Concepts::Container<T>)
    {
        Internal::serializeContainer(os, obj);
    }
    else if constexpr (Common::Concepts::Enum<T>)
    {
        Internal::serializeEnum(os, obj);
    }
    else
    {
        Internal::serialize(os, obj);
    }
}

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Serializer
