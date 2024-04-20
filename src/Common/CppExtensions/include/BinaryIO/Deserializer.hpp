#pragma once

#include "Common/CppExtensions/BinaryIO/Common.hpp"

namespace LunarDB::Common::CppExtensions::BinaryIO::Deserializer {

namespace Internal {

template <typename T>
void deserialize(std::istream& is, T& obj) = delete;

template <typename T>
    requires Common::Concepts::Enum<T>
void deserializeEnum(std::istream& is, T& obj);

template <typename First, typename Second>
void deserializePair(std::istream& is, std::pair<First, Second>& pair);

template <std::size_t Index, typename... Args>
void deserializeTuple(std::istream& is, std::tuple<Args...>& tuple);

template <typename T>
    requires Common::Concepts::Container<T>
void deserializeContainer(std::istream& is, T& container);

template <typename T>
concept Deserializable = requires(std::istream& is, T obj) {
    { Internal::deserialize<T>(is, obj) } -> std::same_as<void>;
};

} // namespace Internal

template <typename T>
concept Deserializable =
    std::is_enum_v<T> || Internal::Deserializable<T> || Common::Concepts::Pair<T> ||
    Common::Concepts::Tuple<T> || Common::Concepts::Tupleable<T> || Common::Concepts::Container<T>;

template <typename T>
    requires Deserializer::Deserializable<T>
void deserialize(std::istream& is, T& obj);

} // namespace LunarDB::Common::CppExtensions::BinaryIO::Deserializer

#include "Common/CppExtensions/private/BinaryIO/Deserializer.inl"
