#pragma once

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <string_view>
#include <tuple>

#define PROVIDE_IMPL_FOR_PODS(MACRO) \
    MACRO(std::int8_t)               \
    MACRO(std::int16_t)              \
    MACRO(std::int32_t)              \
    MACRO(std::int64_t)              \
    MACRO(std::uint8_t)              \
    MACRO(std::uint16_t)             \
    MACRO(std::uint32_t)             \
    MACRO(std::uint64_t)             \
    MACRO(char)                      \
    MACRO(bool)                      \
    MACRO(float)                     \
    MACRO(double)

#define PROVIDE_IMPL_FOR_OBJECTS(MACRO) \
    MACRO(std::string)                  \
    MACRO(std::string_view)

#define PROVIDE_IMPL_FOR(MACRO)  \
    PROVIDE_IMPL_FOR_PODS(MACRO) \
    PROVIDE_IMPL_FOR_OBJECTS(MACRO)

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

namespace LunarDB::Common::CppExtensions::BinaryIO::Common {

namespace Concepts {

namespace ContainerHelpers {

template <typename T>
concept NeqableBeginAndEnd = requires(T t) {
    { std::begin(t) != std::end(t) } -> std::same_as<bool>;
};

template <typename T>
concept Beginable = requires(T t) { std::begin(t); };

template <typename T>
concept Endable = requires(T t) { std::end(t); };

template <typename T>
concept Sizeable = requires(T t) {
    { std::size(t) } -> std::same_as<std::size_t>;
};

template <typename T>
concept BeginIncrementable = requires(T t) { std::begin(t)++; };

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

} // namespace ContainerHelpers

template <typename T>
concept Container = ContainerHelpers::Beginable<T> && ContainerHelpers::Endable<T> &&
                    ContainerHelpers::Sizeable<T> && ContainerHelpers::BeginIncrementable<T> &&
                    ContainerHelpers::BeginDerefable<T> && ContainerHelpers::NeqableBeginAndEnd<T> &&
                    !ContainerHelpers::BeginDerefToVoid<T> &&
                    ContainerHelpers::BeginAndEndCopyConstructibleAndDestructible<T>;

template <typename T>
concept Pair = requires(T t) {
    { t.first } -> std::convertible_to<typename T::first_type>;
    { t.second } -> std::convertible_to<typename T::second_type>;
};

template <typename T>
concept Tuple = requires {
    typename std::tuple_size<T>::type;
    typename std::tuple_element<0, T>::type;
    requires !Pair<T>;
};

template <typename T>
concept Tupleable = requires(T obj) {
    { obj.makeTuple() } -> Tuple;
};

template <typename T>
concept Enum = std::is_enum_v<T>;

} // namespace Concepts

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Common
