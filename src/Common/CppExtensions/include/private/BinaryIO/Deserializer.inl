#pragma once

#include <algorithm>
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

namespace Concepts {

template <typename T>
concept Reservable = requires(T obj) {
    { obj.reserve() } -> std::same_as<void>;
};

template <typename T>
concept EmplaceBackable = requires(T obj) {
    { obj.emplace_back() } -> std::same_as<typename T::reference>;
};

template <typename T>
concept BeforeBeginable = requires(T obj) {
    { obj.before_begin() } -> std::same_as<typename T::iterator>;
};

namespace Map {

template <typename T>
concept UniqueEmplaceable = requires(T obj) {
    {
        obj.emplace(std::declval<typename T::key_type>(), std::declval<typename T::mapped_type>())
    } -> std::same_as<std::pair<typename T::iterator, bool>>;
};

template <typename T>
concept MultiEmplaceable = requires(T obj) {
    {
        obj.emplace(std::declval<typename T::key_type>(), std::declval<typename T::mapped_type>())
    } -> std::same_as<typename T::iterator>;
};

template <typename T>
concept Emplaceable = UniqueEmplaceable<T> || MultiEmplaceable<T>;

} // namespace Map

namespace Set {

template <typename T>
concept UniqueEmplaceable = requires(T obj) {
    {
        obj.emplace(std::declval<typename T::key_type>())
    } -> std::same_as<std::pair<typename T::iterator, bool>>;
};

template <typename T>
concept MultiEmplaceable = requires(T obj) {
    { obj.emplace(std::declval<typename T::key_type>()) } -> std::same_as<typename T::iterator>;
};

template <typename T>
concept Emplaceable = UniqueEmplaceable<T> || MultiEmplaceable<T>;

} // namespace Set

} // namespace Concepts

template <typename T>
    requires Common::Concepts::Container<T>
void deserializeContainer(std::istream& is, T& container)
{
    typename T::size_type size{0};
    is.read(reinterpret_cast<char*>(&size), sizeof(decltype(size)));

    if constexpr (Concepts::Reservable<T>)
    {
        container.reserve(size);
    }

    if constexpr (Concepts::EmplaceBackable<T>)
    {
        for (auto const _ : std::ranges::iota_view{0u, size})
        {
            auto& obj = container.emplace_back();
            Deserializer::deserialize(is, obj);
        }
    }
    else if constexpr (Concepts::Map::Emplaceable<T>)
    {
        std::pair<typename T::key_type, typename T::mapped_type> obj{};
        for (auto const _ : std::ranges::iota_view{0u, size})
        {
            Deserializer::deserialize(is, obj);
            container.emplace(std::move(obj.first), std::move(obj.second));
        }
    }
    else if constexpr (Concepts::Set::Emplaceable<T>)
    {
        typename T::key_type obj{};
        for (auto const _ : std::ranges::iota_view{0u, size})
        {
            Deserializer::deserialize(is, obj);
            container.emplace(std::move(obj));
        }
    }
    else if constexpr (Common::Concepts::ArrayLike<T> && Common::Concepts::ContainerHelpers::Sizeable<T>)
    {
        typename T::size_type const use_size{std::min(size, container.size())};
        for (auto const index : std::ranges::iota_view{0u, use_size})
        {
            Deserializer::deserialize(is, container[index]);
        }
    }
    else
    {
        static_assert(false, "Cannot deserialize container...");
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
    else if constexpr (Common::Concepts::Enum<T>)
    {
        Internal::deserializeEnum(is, obj);
    }
    else if constexpr (Common::Concepts::Container<T> && !std::is_same_v<T, std::string> && !std::is_same_v<T, std::string_view>)
    {
        Internal::deserializeContainer(is, obj);
    }
    else if constexpr (Internal::Deserializable<T>)
    {
        Internal::deserialize(is, obj);
    }
    else
    {
        static_assert(false, "Cannot deserialize object of this type");
    }
}

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Deserializer
