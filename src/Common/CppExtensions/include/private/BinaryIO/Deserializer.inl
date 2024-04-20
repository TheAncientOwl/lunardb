#pragma once

#include <ranges>

#include "Common/CppExtensions/BinaryIO/Deserializer.hpp"

#define INTERNAL_DESERIALIZE(type) \
    template <>                    \
    void deserialize(std::istream& is, type& obj);

namespace LunarDB::Common::CppExtensions::BinaryIO::Deserializer {

namespace Internal {

PROVIDE_IMPL_FOR(INTERNAL_DESERIALIZE);

template <typename T>
    requires Common::Concepts::Enum<T>
void deserializeEnum(std::istream& is, T& obj)
{
    is.read(reinterpret_cast<char*>(&obj), sizeof(decltype(obj)));
}

template <typename First, typename Second>
void deserializePair(std::istream& is, std::pair<First, Second>& pair)
{
    Deserializer::deserialize(is, pair.first);
    Deserializer::deserialize(is, pair.second);
}

template <std::size_t Index, typename... Args>
void deserializeTuple(std::istream& is, std::tuple<Args...>& tuple)
{
    if constexpr (Index < sizeof...(Args))
    {
        Deserializer::deserialize(is, std::get<Index>(tuple));
        Internal::deserializeTuple<Index + 1>(is, tuple);
    }
}

template <typename T>
concept Reservable = requires(T obj) {
    { obj.reserve() } -> std::same_as<void>;
};

template <typename T>
concept EmplaceBackable = requires(T obj, typename T::value_type&& value) {
    { obj.emplace_back(value) } -> std::same_as<typename T::reference>;
};

template <typename T>
concept Emplaceable = requires(T obj, typename T::value_type&& value) {
    { obj.emplace(value) } -> std::same_as<void>;
};

template <typename T>
    requires Common::Concepts::Container<T>
void deserializeContainer(std::istream& is, T& container)
{
    typename T::size_type size{0};
    is.read(reinterpret_cast<char*>(&size), sizeof(decltype(size)));

    if constexpr (Reservable<T>)
    {
        container.reserve(size);
    }

    if constexpr (EmplaceBackable<T>)
    {
        for (auto const _ : std::ranges::iota_view{0u, size})
        {
            auto& obj = container.emplace_back();
            Deserializer::deserialize(is, obj);
        }
    }
    else if constexpr (Emplaceable<T>)
    {
        T obj{};
        for (auto const _ : std::ranges::iota_view{0u, size})
        {
            Deserializer::deserialize(is, obj);
            container.emplace(std::move(obj));
        }
    }
}

} // namespace Internal

template <typename T>
    requires Deserializer::Deserializable<T>
void deserialize(std::istream& is, T& obj)
{
    if constexpr (Common::Concepts::Pair<T>)
    {
        Internal::deserializePair(is, obj);
    }
    else if constexpr (Common::Concepts::Tupleable<T>)
    {
        auto tuple = obj.makeTuple();
        Internal::deserializeTuple<0>(is, tuple);
    }
    else if constexpr (Common::Concepts::Tuple<T>)
    {
        Internal::deserializeTuple<0>(is, obj);
    }
    else if constexpr (Common::Concepts::Container<T> && !std::is_same_v<T, std::string> && !std::is_same_v<T, std::string_view>)
    {
        Internal::deserializeContainer(is, obj);
    }
    else if constexpr (Common::Concepts::Enum<T>)
    {
        Internal::deserializeEnum(is, obj);
    }
    else
    {
        Internal::deserialize(is, obj);
    }
}

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Deserializer
