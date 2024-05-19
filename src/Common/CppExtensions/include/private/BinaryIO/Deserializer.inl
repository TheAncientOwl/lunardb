#pragma once

#include <algorithm>
#include <ranges>

#include "LunarDB/Common/CppExtensions/BinaryIO/Deserializer.hpp"

#define INTERNAL_DESERIALIZE(type) \
    template <>                    \
    void deserialize(std::istream& is, type& obj);

namespace LunarDB::Common::CppExtensions::BinaryIO::Deserializer {

template <typename T>
void deserialize(std::istream&, T&)
{
    static_assert(
        Concepts::StopCompilationIf<T>::value, "Deserializer not implemented for this type...");
}

template <typename T>
    requires Concepts::Primitive<T>
void deserialize(std::istream& is, T& primitive)
{
    is.read(reinterpret_cast<char*>(&primitive), sizeof(T));
}

template <typename T>
    requires Concepts::Pair<T>
void deserialize(std::istream& is, T& pair)
{
    deserialize(is, pair.first);
    deserialize(is, pair.second);
}

template <std::size_t Index, typename... Args>
void deserializeTupleImpl(std::istream& is, std::tuple<Args...>& tuple)
{
    if constexpr (Index < sizeof...(Args))
    {
        deserialize(is, std::get<Index>(tuple));
        deserializeTupleImpl<Index + 1>(is, tuple);
    }
}

template <typename T>
    requires Concepts::Tuple<T>
void deserialize(std::istream& is, T& tuple)
{
    deserializeTupleImpl<0>(is, tuple);
}

template <typename T>
    requires Concepts::Tupleable<T>
void deserialize(std::istream& is, T& tupleable)
{
    auto tuple = tupleable.makeTuple();
    deserializeTupleImpl<0>(is, tuple);
}

template <typename T>
    requires Concepts::Container::EmplaceBackable<T>
void deserializeEmplaceBackable(std::istream& is, T& container, typename T::size_type const size)
{
    typename T::value_type obj{};
    for (auto const _ : std::ranges::iota_view{0u, size})
    {
        deserialize(is, obj);
        container.emplace_back(std::move(obj));
    }
}

template <typename T>
    requires Concepts::Container::Map::Emplaceable<T>
void deserializeMap(std::istream& is, T& map, typename T::size_type const size)
{
    std::pair<typename T::key_type, typename T::mapped_type> obj{};
    for (auto const _ : std::ranges::iota_view{0u, size})
    {
        deserialize(is, obj);
        map.emplace(std::move(obj.first), std::move(obj.second));
    }
}

template <typename T>
    requires Concepts::Container::Set::Emplaceable<T>
void deserializeSet(std::istream& is, T& set, typename T::size_type const size)
{
    typename T::key_type obj{};
    for (auto const _ : std::ranges::iota_view{0u, size})
    {
        deserialize(is, obj);
        set.emplace(std::move(obj));
    }
}

template <typename T>
    requires AnyContainer<T>
void deserialize(std::istream& is, T& container)
{
    typename T::size_type size{0};
    is.read(reinterpret_cast<char*>(&size), sizeof(decltype(size)));

    if constexpr (Concepts::Container::Reservable<T>)
    {
        container.reserve(size);
    }

    if constexpr (Concepts::Container::EmplaceBackable<T>)
    {
        deserializeEmplaceBackable(is, container, size);
    }
    else if constexpr (Concepts::Container::Map::Emplaceable<T>)
    {
        deserializeMap(is, container, size);
    }
    else if constexpr (Concepts::Container::Set::Emplaceable<T>)
    {
        deserializeSet(is, container, size);
    }
    else
    {
        static_assert(
            Concepts::StopCompilationIf<T>::value, "Deserializer not implemented for this type...");
    }
}

template <typename T, std::size_t Size>
void deserialize(std::istream& is, std::array<T, Size>& array)
{
    using size_type = std::array<T, Size>::size_type;

    size_type size{0};
    is.read(reinterpret_cast<char*>(&size), sizeof(decltype(size)));

    size_type const use_size{std::min(size, Size)};
    for (auto const index : std::ranges::iota_view{0u, use_size})
    {
        deserialize(is, array[index]);
    }
}

template <typename T>
void deserialize(std::istream& is, std::forward_list<T>& list)
{
    typename std::forward_list<T>::size_type size{0};
    is.read(reinterpret_cast<char*>(&size), sizeof(decltype(size)));

    T obj{};
    auto it = list.before_begin();
    for (auto const _ : std::ranges::iota_view{0u, size})
    {
        deserialize(is, obj);
        it = list.emplace_after(it, std::move(obj));
    }
}

template <typename T>
void deserialize(std::istream& is, std::optional<T>& opt)
{
    bool exists{false};
    deserialize(is, exists);

    if (exists)
    {
        opt.emplace();
        deserialize(is, *opt);
    }
    else
    {
        opt = std::nullopt;
    }
}

template <typename T>
void deserialize(std::istream& is, std::shared_ptr<T>& ptr)
{
    if (ptr == nullptr)
    {
        ptr = std::make_shared<T>();
    }

    deserialize(is, *ptr);
}

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Deserializer
