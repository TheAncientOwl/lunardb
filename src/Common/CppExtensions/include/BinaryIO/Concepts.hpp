#pragma once

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <iostream>

///
/// @warning This macro should be used alone only if binary serialization is desired.
///          If you're trying to make an object both binary serializable and deserializable
/// you should use @c LUNAR_ENABLE_BINARY_IO
/// @param [in] List of desired fields to be binary serialized
///
#define LUNAR_ENABLE_BINARY_INPUT(...) \
    auto makeTuple()                   \
    {                                  \
        return std::tie(__VA_ARGS__);  \
    }

///
/// @warning This macro should be used alone only if binary deserialization is desired.
///          If you're trying to make an object both binary serializable and deserializable
/// @param [in] List of desired fields to be binary deserialized
/// you should use @c LUNAR_ENABLE_BINARY_IO
///
#define LUNAR_ENABLE_BINARY_OUTPUT(...) \
    auto makeTuple() const              \
    {                                   \
        return std::tie(__VA_ARGS__);   \
    }

///
/// @brief Provide makeTuple() and makeTuple() const variants required by @c
/// LunarDB::Common::CppExtensions::BinaryIO::serialize
/// @param [in] List of desired fields to be binary serialized/deserialized
///
#define LUNAR_ENABLE_BINARY_IO(...)        \
    LUNAR_ENABLE_BINARY_INPUT(__VA_ARGS__) \
    LUNAR_ENABLE_BINARY_OUTPUT(__VA_ARGS__)

namespace LunarDB::Common::CppExtensions::BinaryIO::Concepts {

namespace Helpers {

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

} // namespace Helpers

template <typename T>
concept IterableSerializable =
    Helpers::Sizeable<T> && Helpers::Beginable<T> && Helpers::Endable<T> &&
    Helpers::BeginDerefable<T> && Helpers::NeqableBeginAndEnd<T> && !Helpers::BeginDerefToVoid<T> &&
    Helpers::BeginAndEndCopyConstructibleAndDestructible<T>;

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

template <typename T>
concept Enum = std::is_enum_v<T>;

template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <typename T>
concept Primitive = Enum<T> || Arithmetic<T>;

namespace Container {

template <typename T>
concept Reservable = requires(T obj) {
    { obj.reserve() } -> std::same_as<void>;
};

template <typename T>
concept EmplaceBackable = requires(T obj) {
    requires Helpers::Sizeable<T>;
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

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Concepts
