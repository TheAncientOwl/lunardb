#pragma once

#include "LunarDB/Common/CppExtensions/BinaryIO/Serializer.hpp"

namespace LunarDB::Common::CppExtensions::BinaryIO::Serializer {

template <typename T>
void serialize(std::ostream&, T const&)
{
    static_assert(false, "Serializer not implemented for this type...");
}

template <typename T>
    requires Concepts::Primitive<T>
void serialize(std::ostream& os, T const& primitive)
{
    os.write(reinterpret_cast<const char*>(&primitive), sizeof(T));
}

template <typename T>
    requires Concepts::Pair<T>
void serialize(std::ostream& os, T const& pair)
{
    serialize(os, pair.first);
    serialize(os, pair.second);
}

template <std::size_t Index, typename... Args>
void serializeTupleImpl(std::ostream& os, std::tuple<Args...> const& tuple)
{
    if constexpr (Index < sizeof...(Args))
    {
        serialize(os, std::get<Index>(tuple));
        serializeTupleImpl<Index + 1>(os, tuple);
    }
}

template <typename T>
    requires Concepts::Tuple<T>
void serialize(std::ostream& os, T const& tuple)
{
    serializeTupleImpl<0>(os, tuple);
}

template <typename T>
    requires Concepts::IterableSerializable<T>
void serialize(std::ostream& os, T const& iterable)
{
    auto const size{std::size(iterable)};
    os.write(reinterpret_cast<const char*>(&size), sizeof(decltype(size)));

    for (auto const& element : iterable)
    {
        serialize(os, element);
    }
}

template <typename T>
    requires Concepts::Tupleable<T>
void serialize(std::ostream& os, T const& tupleable)
{
    auto tuple = tupleable.makeTuple();
    serialize(os, tuple);
}

template <typename T>
void serialize(std::ostream& os, std::forward_list<T> const& list)
{
    typename std::forward_list<T>::size_type size{0};
    for (auto const& _ : list)
    {
        ++size;
    }

    serialize(os, list, size);
}

template <typename T>
void serialize(std::ostream& os, std::forward_list<T> const& list, typename std::forward_list<T>::size_type size)
{
    os.write(reinterpret_cast<const char*>(&size), sizeof(decltype(size)));

    for (auto const& element : list)
    {
        serialize(os, element);
    }
}

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Serializer
