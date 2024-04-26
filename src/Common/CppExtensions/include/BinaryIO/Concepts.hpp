#pragma once

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <tuple>

namespace LunarDB::Common::CppExtensions::BinaryIO::Concepts {
template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <typename T>
concept Enum = std::is_enum_v<T>;

template <typename T>
concept Primitive = Arithmetic<T> || Enum<T>;

template <typename T>
concept Pair = requires(T t) {
    { t.first } -> std::convertible_to<typename T::first_type>;
    { t.second } -> std::convertible_to<typename T::second_type>;
};

template <typename T>
concept ArrayLike = requires(T obj) {
    typename T::value_type;
    { std::size(obj) } -> std::convertible_to<std::size_t>;
    { obj.size() } -> std::convertible_to<std::size_t>;
    { obj[0] } -> std::same_as<typename T::value_type&>;
};

template <typename T>
concept Tuple = requires {
    typename std::tuple_size<T>::type;
    typename std::tuple_element<0, T>::type;
    requires !Pair<T>;
    requires !ArrayLike<T>;
};

template <typename T>
concept Tupleable = requires(T obj) {
    { obj.makeTuple() } -> Tuple;
};

namespace Container {

template <typename T>
concept NeqableBeginAndEnd = requires(T t) {
    { std::begin(t) != std::end(t) } -> std::same_as<bool>;
};

template <typename T>
concept Beginable = requires(T t) { std::begin(t); };

template <typename T>
concept Endable = requires(T t) { std::end(t); };

template <typename T>
concept BeginIncrementable = requires(T t) { ++std::begin(t); };

template <typename T>
concept BeginDerefable = requires(T t) { *std::begin(t); };

template <typename T>
concept BeginDerefToVoid = requires(T t) {
    { *std::begin(t) } -> std::same_as<void>;
};

template <typename T>
concept BeginAndEndCopyConstructibleAndDestructible = requires(T t) {
    requires std::destructible<decltype(std::begin(t))>;
    requires std::destructible<decltype(std::end(t))>;
    requires std::copy_constructible<decltype(std::begin(t))>;
    requires std::copy_constructible<decltype(std::end(t))>;
};

template <typename T>
concept Sizeable = requires(T t) {
    { std::size(t) } -> std::same_as<std::size_t>;
};

template <typename T>
concept Reservable = requires(T obj) {
    { obj.reserve() } -> std::same_as<void>;
};

template <typename T>
concept EmplaceBackable = requires(T obj) {
    requires Sizeable<T>;
    {
        obj.emplace_back(std::declval<typename T::value_type>)
    } -> std::same_as<typename T::reference>;
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

} // namespace Container

template <typename T>
concept IterableSerializable =
    Container::Sizeable<T> && Container::Beginable<T> && Container::Endable<T> &&
    Container::BeginDerefable<T> && Container::NeqableBeginAndEnd<T> &&
    !Container::BeginDerefToVoid<T> && Container::BeginAndEndCopyConstructibleAndDestructible<T>;

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Concepts
